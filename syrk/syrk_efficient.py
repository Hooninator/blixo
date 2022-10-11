# This is the version you should be looking at

from __future__ import annotations
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.platforms.neon import Neon4f
from exo.syntax import *

file = open("syrk_final.c", 'w+')

#microkernel sizes
M_r = 4
N_r = 32 #NOTE: This must be divisible by 4
#block sizes
M_c = 64 
K_c = 64
#Matrix sizes
M=255
N=255
K=255

# A_t should be the A treated as if it was transposed, but when you pass the argument it should be a copy of A
@proc
def SYRK(M: size, K: size, N: size, A: f32[M, K], A_t: f32[K, N], C: f32[M, N]):
    assert M >= 1
    assert K >= 1
    assert N >= M
    assert stride(A, 1) == 1
    assert stride(A_t, 1) == 1
    assert stride(C, 1) == 1

    for i in par(0, M):
        for j in par(0, i+1):
            for k in par(0, K):
                C[i, j] += A[i, k]*A_t[k, j]

syrk_window = (SYRK
                .rename('syrk_win')
                .set_window('A', True)
                .set_window('A_t', True)
                .set_window('C', True))


# Microkernel
@proc
def microkernel_gemv(M: size, K: size, N: size, A: [f32][M, K] @ DRAM, A_t: [f32][K, N] @ DRAM,
                C: [f32][M, N] @ DRAM):
    assert stride(A, 1) == 1
    assert stride(A_t, 1) == 1
    assert stride(C, 1) == 1
    for j in par(0, N):
        for k in par(0, K):
            C[0, j] += A[0, k] * A_t[k, j]
print(microkernel_gemv)

# Generate scheduled microkernel_gemv
microkernel_gemv_inter = microkernel_gemv.rename("microkernel_gemv_inter").partial_eval(K=K_c).partial_eval(N=N_r).partial_eval(M=M_r).simplify()
microkernel_gemv_scheduled = (microkernel_gemv_inter.rename(f"neon_microkernel_gemv")
                        .reorder('j','k')
                        .split('j', 4, ['jo','ji'], perfect=True)
                        .par_to_seq('for k in _: _')
                        .stage_assn('C_reg', 'C[_] += _')
                        .set_memory('C_reg', Neon4f)
                        .lift_alloc('C_reg : _', n_lifts=2)
                        .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=3)
                        .replace(neon_vld_4xf32, 'for ji in _: _ #0')
                        .replace(neon_vst_4xf32, 'for ji in _: _ #1')
                        .stage_expr('A_vec', 'A[_,_]', memory=Neon4f)
                        .stage_expr('A_t_vec', 'A_t[_,_]', memory=Neon4f)
                        .replace_all(neon_vld_4xf32)
                        .replace_all(neon_broadcast_4xf32)
                        .replace_all(neon_vfmadd_4xf32_4xf32)
                        .lift_alloc('A_vec : _', n_lifts=1)
                        .fission_after('neon_broadcast_4xf32(_)', n_lifts=1)
                        #.lift_alloc('A_t_vec : _', n_lifts=1)
                        #.fission_after('neon_vld_4xf32(_) #1', n_lifts=1)
                        .unroll('jo')
                        .simplify())

# GEBP Kernel Generation
GEBP_intermediate = (microkernel_gemv.partial_eval(M=M_c)
        .partial_eval(K=K_c)
        .rename(f'GEBP_{M_c}x{K_c}')
        .simplify()
)

print(GEBP_intermediate)

GEBP_scheduled = (GEBP_intermediate
                    .rename("GEBP_scheduled")
                    .split('j', N_r, ['jo', 'ji'], tail='cut')
                    .fission_after('for ji in _:_ #1', n_lifts=1)
                    .replace_all(microkernel_gemv_inter)
                    .call_eqv(microkernel_gemv_scheduled, 'microkernel_gemv_inter(_)')
                    .simplify()
)

print(GEBP_scheduled)

# Handle GEBP Edge Case
edge_amt = ((N%N_r)//4) * 4
print(edge_amt)
if edge_amt:

    # Generate properly sized microkernel
    microkernel_gemv_inter_gebp = microkernel_gemv.rename("microkernel_gebp_inter").partial_eval(K=K_c).partial_eval(N=edge_amt).partial_eval(M=M_r).simplify()
    microkernel_gemv_gebp_edge = (microkernel_gemv_inter_gebp.rename(f"microkernel_gemv_gebp_edge")
                            .reorder('j','k')
                            .split('j', 4, ['jo','ji'], perfect=True)
                            .par_to_seq('for k in _: _')
                            .stage_assn('C_reg', 'C[_] += _')
                            .set_memory('C_reg', Neon4f)
                            .lift_alloc('C_reg : _', n_lifts=2)
                            .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=3)
                            .replace(neon_vld_4xf32, 'for ji in _: _ #0')
                            .replace(neon_vst_4xf32, 'for ji in _: _ #1')
                            .stage_expr('A_vec', 'A[_,_]', memory=Neon4f)
                            .stage_expr('A_t_vec', 'A_t[_,_]', memory=Neon4f)
                            .replace_all(neon_vld_4xf32)
                            .replace_all(neon_broadcast_4xf32)
                            .replace_all(neon_vfmadd_4xf32_4xf32)
                            .lift_alloc('A_vec : _', n_lifts=1)
                            .fission_after('neon_broadcast_4xf32(_)', n_lifts=1)
                            #.lift_alloc('A_t_vec : _', n_lifts=1)
                            #.fission_after('neon_vld_4xf32(_) #1', n_lifts=1)
                            .unroll('jo')
                            .simplify())
    
    # Substitute microkernel into GEBP
    GEBP_scheduled = (GEBP_scheduled
                        .split('ji', edge_amt, ['joo', 'jii'], tail='cut')
                        .fission_after('for jii in _:_ #1', n_lifts=1)
                        .replace_all(microkernel_gemv_inter_gebp)
                        .call_eqv(microkernel_gemv_gebp_edge, 'microkernel_gebp_inter(_)')
                        .simplify())

# GEPP Kernel Generation
GEPP_syrk_intermediate = (syrk_window
            .rename("GEPP_syrk_intermediate")
            .partial_eval(K=K_c)
            .simplify()
)


GEPP_syrk = (GEPP_syrk_intermediate
            .rename("GEPP_syrk")
            .split('j #0', M_c, ['jo', 'ji'], tail='cut')
            .fission_after('for ji in _:_ #1', n_lifts=1)
            .replace_all(GEBP_intermediate)
            .repeat(Procedure.call_eqv, GEBP_scheduled, f'GEBP_{M_c}x{K_c}(_)')
            .simplify()
            )
print(GEPP_syrk)
print(GEBP_intermediate)


# Schedule GEPP
exo_syrk = (SYRK
            .rename("exo_syrk")
            .reorder('j', 'k')
            .reorder('i', 'k')
            .split('k', K_c, ['ki', 'ko'], tail='cut_and_guard')
            .fission_after('for ko in _: _ ', n_lifts=2)
            .reorder('ko', 'i')
            .reorder('ko', 'j')
            .replace_all(GEPP_syrk_intermediate)
            .call_eqv(GEPP_syrk, 'GEPP_syrk_intermediate(_)')
            .simplify())

print(exo_syrk)
file.write(exo_syrk.c_code_str())
file.close()