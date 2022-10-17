"""
EXO_SGEMM
Author: Julian Bellavita, UC Berkeley
"""

from __future__ import annotations
from concurrent.futures import process
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.syntax import *
import time

stime = time.time()
file = open("small.c", 'w+')


def generate_microkernel(kernel, n_dim):
        if n_dim%4:
                raise Exception(f"Error: n_dim must be a multiple of 4, got {n_dim}")
        return (kernel
                .rename(f"gebp_edge_neon_microkernel_1x{n_dim}")
                .reorder('j','k')
                .reorder('i','k')
                .split('j', 4, ['jo','ji'], perfect=True)
                .par_to_seq('for k in _: _')
                .stage_assn('C_reg', 'C[_] += _')
                .lift_alloc('C_reg : _', n_lifts=4)
                .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
                .replace(neon_vld_4xf32, 'for ji in _: _ #0')
                .replace(neon_vst_4xf32, 'for ji in _: _ #1')
                .set_memory('C_reg', Neon4f)
                .stage_expr('A_vec', 'A[_,_]', memory=Neon4f)
                .stage_expr('B_vec', 'B[_,_]', memory=Neon4f)
                .replace_all(neon_vld_4xf32)
                .replace_all(neon_broadcast_4xf32)
                .replace_all(neon_vfmadd_4xf32_4xf32)
                .lift_alloc('A_vec : _', n_lifts=2)
                .fission_after('neon_broadcast_4xf32(_)', n_lifts=2)
                .lift_alloc('B_vec : _', n_lifts=2)
                .fission_after('neon_vld_4xf32(_) #1', n_lifts=2)
                .simplify())

@proc
def SGEMM(M: size, N: size, K: size, A: f32[M, K], B: f32[K, N], C: f32[M, N]):
    assert M >= 1
    assert N >= 1
    assert K >= 1
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1

    for i in par(0, M):
        for j in par(0, N):
            for k in par(0, K):
                C[i, j] += A[i, k] * B[k, j]

sgemm_window = (SGEMM
                .rename('sgemm_win')
                .set_window('A', True)
                .set_window('B', True)
                .set_window('C', True))

#microkernel sizes
M_r = 4 #4
N_r = 16 #16
#block sizes
M_c = 64 #64
K_c = 128 #128
#Matrix sizes
M=1023
N=1023
K=1023


#Microkernels

#Standard microkenel
microkernel = (sgemm_window
                .rename('microkernel')
                .partial_eval(M_r,N_r)
                .simplify())
#file.write(microkernel.c_code_str())

neon_microkernel = (microkernel
                    .rename('neon_microkernel')
                    .reorder('j','k')
                    .reorder('i','k')
                    #.reorder('i','j')
                    #Somehow, using this split command resizes C 
                    .split('j', 4, ['jo','ji'], perfect=True)
                    .par_to_seq('for k in _: _')
                    .stage_assn('C_reg', 'C[_] += _')
                    .set_memory('C_reg', Neon4f)
                    .lift_alloc('C_reg : _', n_lifts=3)
                    #double fission lifts both statements out and copies the loops they're wrapped in
                    .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
                    .replace(neon_vld_4xf32, 'for ji in _: _ #0')
                    .replace(neon_vst_4xf32, 'for ji in _: _ #1')
                    )
#print(neon_microkernel)

neon_microkernel = (neon_microkernel
                    .stage_expr('A_vec', 'A[_,_]', memory=Neon4f)
                    .stage_expr('B_vec', 'B[_,_]', memory=Neon4f)
                    #.replace(neon_vld_4xf32, 'for ji in _: _ #0')
                    #.replace(neon_vst_4xf32, 'for ii in _:_ #3')
                    .replace_all(neon_vld_4xf32)
                    .replace_all(neon_broadcast_4xf32)
                    .replace_all(neon_vfmadd_4xf32_4xf32)
                    #.lift_alloc('B_vec: _')
                    #.fission_after('neon_broadcast_4xf32(_)')
                    #lift_alloc and fission_after are used to split up bodies of loops
                    .lift_alloc('A_vec : _', n_lifts=2)
                    .fission_after('neon_broadcast_4xf32(_)', n_lifts=2)
                    .lift_alloc('B_vec : _', n_lifts=2)
                    .fission_after('neon_vld_4xf32(_) #1', n_lifts=2)
                    .simplify())
#print(neon_microkernel)

sgemm_exo = (SGEMM
              .rename('sgemm_exo')
              #reorder and split loops so we can match with microkernel
              .reorder('i', 'j')
              .split('j', N_r, ['ji', 'jo'], tail='cut')
              .fission_after('for jo in _: _ ', n_lifts=2)
              .reorder('jo', 'i')
              .split('i', M_r, ['ii', 'io'], tail='cut')
              .fission_after('for io in _: _ ', n_lifts=2)

              #.reorder('jo', 'ii')
              #do the replacement
              .replace_all(microkernel)
              .call_eqv(neon_microkernel, 'microkernel(_)')
              .stage_mem(f'B[0:K,'
                   f'{N_r}*ji:{N_r}*ji+{N_r}]',
                   'B_strip', 'for ii in _:_ #0')
              #.replace_all(microkenel_edge)  
              .simplify()
              )
print(sgemm_exo)
# Edge cases
edge_amt_1 = M % M_r 
if edge_amt_1:
    microkernel_edge_1 = (sgemm_window
                        .rename('microkernel_edge_1')
                        .partial_eval(edge_amt_1,N_r)
                        .simplify())
    neon_microkernel_edge_1 = (microkernel_edge_1
                            .rename('neon_microkernel_edge_1')
                            .reorder('j','k')
                            .reorder('i','k')
                            .split('j', 4, ['jo','ji'], perfect=True)
                            .par_to_seq('for k in _: _')
                            .stage_assn('C_reg', 'C[_] += _')
                            .lift_alloc('C_reg : _', n_lifts=4)
                            #double fission lifts both statements out and copies the loops they're wrapped in
                            .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
                            .replace(neon_vld_4xf32, 'for ji in _: _ #0')
                            .replace(neon_vst_4xf32, 'for ji in _: _ #1')
                            .set_memory('C_reg', Neon4f)
                            )
    
    neon_microkernel_edge_1 = (neon_microkernel_edge_1
                        .stage_expr('A_vec', 'A[_,_]', memory=Neon4f)
                        .stage_expr('B_vec', 'B[_,_]', memory=Neon4f)
                        .replace_all(neon_vld_4xf32)
                        .replace_all(neon_broadcast_4xf32)
                        .replace_all(neon_vfmadd_4xf32_4xf32)
                        #lift_alloc and fission_after are used to split up bodies of loops
                        .lift_alloc('A_vec : _', n_lifts=2)
                        .fission_after('neon_broadcast_4xf32(_)', n_lifts=2)
                        .lift_alloc('B_vec : _', n_lifts=2)
                        .fission_after('neon_vld_4xf32(_) #1', n_lifts=2)
                        .simplify())
    print(neon_microkernel_edge_1)
    sgemm_exo = (sgemm_exo
                    .split('io #0', edge_amt_1, ['iii', 'ioo'], tail='cut')
                    .replace(microkernel_edge_1, 'for ioo in _:_ #0')
                    .call_eqv(neon_microkernel_edge_1, 'microkernel_edge_1(_)')
                    .simplify())

edge_amt_2 = M % M_r % edge_amt_1
print(edge_amt_2)
if edge_amt_2:
    microkernel_edge_2 = (sgemm_window
                        .rename('microkernel_edge_2')
                        .partial_eval(edge_amt_2,N_r)
                        .simplify())
    print(microkernel_edge_2)
    neon_microkernel_edge_2 = (microkernel_edge_2
                            .rename('neon_microkernel_edge_2')
                            .reorder('j','k')
                            .reorder('i','k')
                            .split('j', 4, ['jo','ji'], perfect=True)
                            .par_to_seq('for k in _: _')
                            .stage_assn('C_reg', 'C[_] += _')
                            .lift_alloc('C_reg : _', n_lifts=4)
                            #double fission lifts both statements out and copies the loops they're wrapped in
                            .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
                            .replace(neon_vld_4xf32, 'for ji in _: _ #0')
                            .replace(neon_vst_4xf32, 'for ji in _: _ #1')
                            .set_memory('C_reg', Neon4f)
                            )
    
    neon_microkernel_edge_2 = (neon_microkernel_edge_2
                        .stage_expr('A_vec', 'A[_,_]', memory=Neon4f)
                        .stage_expr('B_vec', 'B[_,_]', memory=Neon4f)
                        .replace_all(neon_vld_4xf32)
                        .replace_all(neon_broadcast_4xf32)
                        .replace_all(neon_vfmadd_4xf32_4xf32)
                        #lift_alloc and fission_after are used to split up bodies of loops
                        .lift_alloc('A_vec : _', n_lifts=2)
                        .fission_after('neon_broadcast_4xf32(_)', n_lifts=2)
                        .lift_alloc('B_vec : _', n_lifts=2)
                        .fission_after('neon_vld_4xf32(_) #1', n_lifts=2)
                        .simplify())
    print(neon_microkernel_edge_2)
    sgemm_exo = (sgemm_exo
                    .split('ioo', edge_amt_2, ['iooo', 'iiii'], tail='cut')
                    .replace(microkernel_edge_2, 'for io in _:_ #0')
                    .call_eqv(neon_microkernel_edge_2, 'microkernel_edge_2(_)')
                    .simplify())

edge_amt_3 = (N % N_r // 4) * 4
if edge_amt_3:
    microkernel_edge_3 = (sgemm_window
                        .rename('microkernel_edge_3')
                        .partial_eval(M_r,edge_amt_3)
                        .simplify())
    neon_microkernel_edge_3 = (microkernel_edge_3
                            .rename('neon_microkernel_edge_3')
                            .reorder('j','k')
                            .reorder('i','k')
                            .split('j', 4, ['jo','ji'], perfect=True)
                            .par_to_seq('for k in _: _')
                            .stage_assn('C_reg', 'C[_] += _')
                            .lift_alloc('C_reg : _', n_lifts=4)
                            #double fission lifts both statements out and copies the loops they're wrapped in
                            .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
                            .replace(neon_vld_4xf32, 'for ji in _: _ #0')
                            .replace(neon_vst_4xf32, 'for ji in _: _ #1')
                            .set_memory('C_reg', Neon4f)
                            )
    
    neon_microkernel_edge_3 = (neon_microkernel_edge_3
                        .stage_expr('A_vec', 'A[_,_]', memory=Neon4f)
                        .stage_expr('B_vec', 'B[_,_]', memory=Neon4f)
                        .replace_all(neon_vld_4xf32)
                        .replace_all(neon_broadcast_4xf32)
                        .replace_all(neon_vfmadd_4xf32_4xf32)
                        #lift_alloc and fission_after are used to split up bodies of loops
                        .lift_alloc('A_vec : _', n_lifts=2)
                        .fission_after('neon_broadcast_4xf32(_)', n_lifts=2)
                        .lift_alloc('B_vec : _', n_lifts=2)
                        .fission_after('neon_vld_4xf32(_) #1', n_lifts=2)
                        .simplify())
    print(neon_microkernel_edge_3)
    sgemm_exo = (sgemm_exo
                    .reorder('io #0', 'jo')
                    .split('jo #1', edge_amt_3, ['jii', 'joo'], tail='cut')
                    .reorder('joo', 'io')
                    .replace(microkernel_edge_3, 'for io in _:_ #0')
                    .call_eqv(neon_microkernel_edge_3, 'microkernel_edge_3(_)')
                    .simplify())

edge_amt_4 = N % N_r % edge_amt_3
edge_k = (K // 4) * 4
if edge_amt_4:
    microkernel_edge_4 = (sgemm_window
                        .rename('microkernel_edge_4')
                        .partial_eval(M_r,edge_amt_4)
                        .partial_eval(K=edge_k)
                        .reorder('i', 'j')
                        .simplify())
    print(microkernel_edge_4)
    neon_microkernel_edge_4 = (microkernel_edge_4
                            .rename('neon_microkernel_edge_4')
                            .reorder('i', 'k')
                            .split('i', 4, ['io','ii'], perfect=True)
                            .par_to_seq('for j in _: _')
                            .stage_assn('C_reg', 'C[_] += _')
                            .lift_alloc('C_reg : _', n_lifts=4)
                            #double fission lifts both statements out and copies the loops they're wrapped in
                            .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
                            .replace(neon_vld_4xf32, 'for ii in _: _ #0')
                            .replace(neon_vst_4xf32, 'for ii in _: _ #1')
                            .set_memory('C_reg', Neon4f)
                            )
    print(neon_microkernel_edge_4)
    neon_microkernel_edge_4 = (neon_microkernel_edge_4
                        .stage_expr('A_vec', 'A[_,_]', memory=Neon4f)
                        .stage_expr('B_vec', 'B[_,_]', memory=Neon4f)
                        .replace_all(neon_vld_4xf32)
                        .replace_all(neon_broadcast_4xf32)
                        .replace_all(neon_vfmadd_4xf32_4xf32)
                        #lift_alloc and fission_after are used to split up bodies of loops
                        .lift_alloc('A_vec : _', n_lifts=2)
                        #.fission_after('neon_broadcast_4xf32(_)', n_lifts=2)
                        .lift_alloc('B_vec : _', n_lifts=2)
                        #.fission_after('neon_vld_4xf32(_) #1', n_lifts=2)
                        .simplify())
    print(neon_microkernel_edge_4)
    sgemm_exo = (sgemm_exo
                    .reorder('io', 'joo')
                    .reorder('io', 'k')
                    .reorder('joo', 'k')
                    .split('k #1', edge_k, ['ko', 'ki'], tail='cut')
                    .reorder('ki', 'joo')
                    .reorder('ki', 'io')
                    .split('joo', edge_amt_4, ['jiii', 'jooo'], tail='cut')
                    .replace(microkernel_edge_4, 'for jooo in _:_ #0')
                    .call_eqv(neon_microkernel_edge_4, 'microkernel_edge_4(_)')
                    .simplify())

print(sgemm_exo)
print(f"Total execution time: {time.time()-stime}s") 
file.write(sgemm_exo.c_code_str())