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
N_r = 4 #NOTE: This must be divisible by 4
#block sizes
M_c = 8 
K_c = 8
#Matrix sizes
M=256
N=256
K=256

#A_t should be the A treated as if it was transposed, but when you pass the argument it should be a copy of A
@proc
def SYRK(M: size, K: size, A: f32[M, K], A_t: f32[K, M], C: f32[M, M]):
    assert M >= 1
    assert K >= 1
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
def microkernel_gemv(M: size, K: size, A: [f32][M, K] @ DRAM, A_t: [f32][K, M] @ DRAM,
                C: [f32][M, M] @ DRAM):
    assert stride(A, 1) == 1
    assert stride(A_t, 1) == 1
    assert stride(C, 1) == 1
    for j in par(0, M):
        for k in par(0, K):
            C[0, j] += A[0, k] * A_t[k, j]


# Generate microkernel_gemv
def generate_gemv_microkernel(M_dim, kernel):
    return (kernel.rename(f"neon_microkernel_gemv_{M_dim}")
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
                        .simplify()
                        )

microkernel_gemv_inter = microkernel_gemv.partial_eval(K=K_c).partial_eval(M=N_r).simplify()
microkernel_gemv_scheduled = generate_gemv_microkernel(N_r, microkernel_gemv_inter)
print(microkernel_gemv)

# GEBP Kernel Generation
GEBP_intermediate = (microkernel_gemv.partial_eval(M=M_c)
        .partial_eval(K=K_c)
        .rename(f'GEBP_{M_c}x{K_c}')
        .simplify()
)

print(GEBP_intermediate)

GEBP_scheduled = (GEBP_intermediate
                    .rename("GEBP_scheduled")
                    .split('j', N_r, ['jo', 'ji'], tail='cut_and_guard')
                    .replace_all(microkernel_gemv)
                    .repeat(Procedure.call_eqv, microkernel_gemv_scheduled, 'microkernel_gemv(_)')
                    .simplify()
)

print(GEBP_scheduled)

# GEPP Kernel Generation
GEPP_syrk_intermediate = (syrk_window
            .rename("GEPP_syrk_intermediate")
            .partial_eval(K=K_c)
            .simplify()
)


GEPP_syrk = (GEPP_syrk_intermediate
            .rename("GEPP_syrk")
            .split('j #0', K_c, ['jo', 'ji'], tail='cut')
            .fission_after('for ji in _:_ #1', n_lifts=2)
            .replace_all(GEBP_intermediate)
            .call_eqv(GEBP_scheduled, f'GEBP_{M_c}x{K_c}(_)')
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
