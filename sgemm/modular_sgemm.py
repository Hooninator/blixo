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
file = open("output.c", 'w+')
file2 = open("mkernel.c", 'w')
python_file = open("output.py", 'w')


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
                #double fission lifts both statements out and copies the loops they're wrapped in
                .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
                .replace(neon_vld_4xf32, 'for ji in _: _ #0')
                .replace(neon_vst_4xf32, 'for ji in _: _ #1')
                .set_memory('C_reg', Neon4f)
                #.set_memory('C_reg_1', DRAM_STATIC)
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
                .unroll('jo')
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
M_r = 16
N_r = 16 #NOTE: This must be at least 4, otherwise the vector instructions will not work
#block sizes
M_c = 64 
K_c = 32
#Matrix sizes
M=1024
N=1024


#Microkernels

#Standard microkenel
microkernel = (sgemm_window
                .rename('microkernel')
                .partial_eval(M_r,N_r)
                .partial_eval(K=K_c)
                .simplify())
#file.write(microkernel.c_code_str())

neon_microkernel = (microkernel
                    .rename('neon_microkernel')
                    .reorder('j','k')
                    .reorder('i','k')
                    #Somehow, using this split command resizes C 
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

neon_microkernel = (neon_microkernel
                    .stage_expr('A_vec', 'A[_,_]', memory=Neon4f)
                    .stage_expr('B_vec', 'B[_,_]', memory=Neon4f)
                    .replace_all(neon_vld_4xf32)
                    .replace_all(neon_broadcast_4xf32)
                    .replace_all(neon_vfmadd_4xf32_4xf32)
                    .lift_alloc('A_vec: _')
                    .fission_after('neon_broadcast_4xf32(_)')
                    #lift_alloc and fission_after are used to split up bodies of loops
                    .lift_alloc('A_vec : _', n_lifts=2)
                    .fission_after('neon_broadcast_4xf32(_)', n_lifts=2)
                    .lift_alloc('B_vec : _', n_lifts=2)
                    .fission_after('neon_vld_4xf32(_) #1', n_lifts=2)
                    #.unroll('i') NOTE: For some reason, trying to unroll i causes a recursion depth exception
                    #.unroll('k') NOTE: This leads to no performance improvement, and it also makes generation take a long time
                    .unroll('jo')
                    .simplify())
#print(neon_microkernel)

#Microkernel for standard edge case
microkernel_edge = (sgemm_window
                .rename('microkernel_edge')
                .partial_eval(M_r,N_r)
                .simplify())

neon_microkernel_edge = (microkernel_edge
                    .rename('neon_microkernel_edge')
                    .reorder('j','k')
                    .reorder('i','k')
                    #Somehow, using this split command resizes C 
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

neon_microkernel_edge = (neon_microkernel_edge
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
                    .unroll('jo')
                    .simplify())

#file.write(neon_microkernel.c_code_str())


#TODO: GEPP microkernel


#GEBP edge case microkernels
microkernel_edge_gebp_simple = (sgemm_window
                                .rename("microkernel_edge_gebp_simple")
                                .partial_eval(K=K_c)
                                .partial_eval(N=N%N_r)
                                )


#Pattern matching purposes
microkernel_edge_gebp = (sgemm_window
                        .rename("microkernel_edge_gebp")
                        .partial_eval(M=M_r)
                        .partial_eval(K=K_c)
                        .add_assertion(f'N < {N_r}')
                        .simplify())

#Generate microkernels for all of the potential values of (N%N_r)

gebp_edge_microkernels = {}
gebp_edge_neon_microkernels = {}
if N%N_r:
        for N_e in range(4, N_r):
                gebp_edge_microkernels[N_e] = (
                        sgemm_window
                                .rename(f'gebp_edge_microkernel_1x{N_e}')
                                .partial_eval(M=M_r)
                                .partial_eval(K=K_c)
                                .partial_eval(N=N_e)
                )
                print(f"Generating microkernel {N_e}")
                #N_e does not evenly divide 4, so do the weird microkernel insertion thing
                if N_e%4:
                        #print(N_e)
                        N_dim = (N_e//4)*4
                        gebp_edge_neon_microkernels[N_e] = (
                                gebp_edge_microkernels[N_e]
                                        .rename(f"gebp_edge_neon_microkernel_1x{N_e}")
                                        .reorder('j','k')
                                        .reorder('i','k')
                                        .split('j', 4, ['jo','ji'], tail='cut_and_guard')
                                        .fission_after('for ji in _:_ #1', n_lifts=2)
                                        .simplify()
                                        .replace(gebp_edge_microkernels[N_dim]
                                                .reorder('j','k')
                                                .reorder('i','k')
                                                .split('j', 4, ['jo','ji'], perfect=True),
                                                "for k in _: _ #0")
                                        .call_eqv(gebp_edge_neon_microkernels[N_dim], f'gebp_edge_microkernel_1x{N_dim}(_)')
                        )
                        #print(gebp_edge_neon_microkernels[N_e])
                else:
                        gebp_edge_neon_microkernels[N_e] = (
                                generate_microkernel(gebp_edge_microkernels[N_e], N_e)
                        )
                #print(gebp_edge_microkernels[N_e])
                #print(gebp_edge_neon_microkernels[N_e])
                #print(gebp_edge_neon_microkernels[N_e].c_code_str())

        #Now, insert each microkernel
        microkernel_edge_gebp_scheduled = (
                microkernel_edge_gebp
                        .rename("microkernel_edge_gebp_scheduled")
                        .specialize('for i in _:_ #0',
                                [f"N=={i}" for i in range(1, N_r)])
                        .simplify()
        )
        for i in range(4, N_r):
                print(f"Inserting scheduled microkernel {i}")
                microkernel_edge_gebp_scheduled = (
                        microkernel_edge_gebp_scheduled
                                .replace_all(gebp_edge_microkernels[i])
                                .call_eqv(gebp_edge_neon_microkernels[i], f"gebp_edge_microkernel_1x{i}(_)")
                )
else:
      microkernel_edge_gebp_scheduled = (
                microkernel_edge_gebp
                        .rename("microkernel_edge_gebp_scheduled"))   

#This I think can mirror the gebp approach, just with the bound being different
#microkernel_edge_gepp = (sgemm_window
                         #.rename('microkernel_edge_gepp')
                         #.partial_eval(K=K_c))
#print(microkernel_edge_gebp_scheduled)
#file2.write(microkernel_edge_gebp_scheduled.c_code_str())

#neon_microkernel_edge_gepp = (microkernel_edge_gepp
 #                               .rename("neon_microkernel_edge_gepp")

  #                              .simplify()
#)
bottom_gebp_kc = (sgemm_window
                        .rename("bottom_gebp_kc")
                        .partial_eval(M=(M%M_c))
                        .partial_eval(K=K_c))

#print(bottom_gebp_kc)







GEBP_MKc = (sgemm_window
        .rename("GEBP_MKc")
        .partial_eval(M=M_c)
        .partial_eval(K=K_c)
        #.partial_eval(N=N)
        )

GEBP_edge_Kc = (sgemm_window
                .rename("GEBP_edge_Kc")
                .partial_eval(M=M_c))

#file.write(GEBP_MKc.c_code_str())

#Multiply a M_c*K_c block of A and a K_c*N panel of B. Calls the microkernel for each strip of B
GEBP = (GEBP_MKc
        .rename("GEBP")
        #Tile the block of A and the panel of B
        .split('i', M_r, ['io', 'ii'], tail='cut_and_guard')
        .split('j', N_r, ['jo', 'ji'], tail='cut_and_guard')
        #Handle edge case
        .fission_after('for jo in _: _', n_lifts=2)
        #reorder so loop ordering is same as microkernel
        .reorder('ii','jo')
        .lift_if(f'if N % _ > 0: _ #0')
        .lift_if(f'if N % _ > 0: _ #1')
        #outer loop must be A[0], middle loop must be B[1], inner loop must be total size of C
        .replace_all(microkernel)
        .call_eqv(neon_microkernel, 'microkernel(_)')
        .replace_all(microkernel_edge_gebp)
        #.replace_all(microkernel_edge_gebp_simple)
        .call_eqv(microkernel_edge_gebp_scheduled, 'microkernel_edge_gebp(_)')
        #Tiling the panels of B or A leads to a small performance decrease :( 
        .simplify()
        #.reorder('io', 'jo')
        #.stage_mem(f'B[0:{K_c},'
        #           f'{N_r}*jo:{N_r}*jo+{N_r}]',
        #           'B_strip', 'for io in _:_ #0')
        #.stage_mem(f'A[io*{M_r}:io*{M_r}+{M_r},'
         #          f'0:{K_c}]', 'A_strip', 'for jo in _:_ #0')
        #.simplify()
        #.set_memory('A_strip', DRAM_STATIC)
)
print(GEBP)
GEBP_edge = (GEBP_edge_Kc
        .rename("GEBP_edge")
        #Tile the block of A and the panel of B
        .split('i', M_r, ['io', 'ii'], tail='cut_and_guard')
        .split('j', N_r, ['jo', 'ji'], tail='cut_and_guard')
        #Handle edge case
        .fission_after('for jo in _: _', n_lifts=2)
        #reorder so loop ordering is same as microkernel
        .reorder('ii','jo')
        .lift_if("if N % _ > 0: _ #0")
        .lift_if('if N % _ > 0: _ #1')
        #outer loop must be A[0], middle loop must be B[1], inner loop must be total size of C
        .replace_all(microkernel_edge)
        .call_eqv(neon_microkernel_edge, 'microkernel_edge(_)')
        .simplify()

)










#file.write(GEBP.c_code_str())

#Multiply a M*K_c panel of A with a K_c*N panel of B 
#MKc is the intermediate procedure used for replacing parts of other procedures with GEPP
GEPP_MKc = (sgemm_window
             .rename("GEPP_MKc")
             .partial_eval(K=K_c)
             #.partial_eval(N=N)
             )
#file.write(GEPP_MKc.c_code_str())

GEPP_edge_Kc = (sgemm_window
                .rename("GEPP_edge_Kc"))

GEPP = (GEPP_MKc
        .rename("GEPP")
        .split('i', M_c, ['io', 'ii'], tail='cut_and_guard')
        .stage_mem(f'A[{M_c}*io : {M_c}*io + {M_c},'
                   f'0:{K_c}]',
                   'A_blk', 'for ii in _:_ #0')
        .set_memory('A_blk', DRAM_STATIC)
        .replace_all(GEBP_MKc)
        .call_eqv(GEBP, 'GEBP_MKc(_)')
        .simplify()
        .replace_all(bottom_gebp_kc)
        .simplify()
        #Transpose A_blk
        #NOTE: rearrange dim is super jank and made me waste 4 hours debugging. Fun times were had.
        #.rearrange_dim('A_blk: _', [1, 0])
        )
print(GEPP)
GEPP_edge = (GEPP_edge_Kc
             .rename("GEPP_edge")
             .split('i', M_c, ['io', 'ii'], tail='cut_and_guard')
             .replace_all(GEBP_edge_Kc)
             .call_eqv(GEBP_edge, "GEBP_edge_Kc(_)")
             .simplify())
#file.write(GEPP.c_code_str())
#file.write(GEPP_edge.c_code_str())#










sgemm_exo = (SGEMM
              .rename("sgemm_exo")
              #reorder and split loops so we can match with GEPP
              .reorder('j', 'k')
              .reorder('i', 'k')
              .split('k', K_c, ['ki', 'ko'], tail='cut_and_guard')
              .fission_after('for ko in _: _ ', n_lifts=2)
              .reorder('ko', 'i')
              .reorder('ko', 'j')
              #.partial_eval(N=N)
              #do the replacement
              .replace_all(GEPP_MKc)
              .replace(GEPP_edge_Kc, "for i in _: _ #0")
              .call_eqv(GEPP, "GEPP_MKc(_)")
              .call_eqv(GEPP_edge, "GEPP_edge_Kc(_)")
              .simplify()
              #Blocking
              .stage_window('A_panel', 'A[_] #0', DRAM_STATIC)
              .bound_alloc('A_panel: _', [f'{M}', f'{K_c}'])
              .stage_window('B_panel', 'B[_] #0', DRAM_STATIC)
              .bound_alloc('B_panel: _', [f'{K_c}', f'{N}'])
              )
print(f"Total execution time: {time.time()-stime}s") 
file.write(sgemm_exo.c_code_str())