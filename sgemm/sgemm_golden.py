from __future__ import annotations

from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.neon import *
from exo.syntax import *
from matmap.transforms import TilingTransform as ts

file = open("sgemm_alex.c", 'w+')

# noinspection PyPep8Naming
@proc
def SGEMM(M: size, N: size, K: size, A: f32[M, K], B: f32[K, N], C: f32[M, N]):
    assert M >= 1
    assert N >= 1
    assert K >= 1
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1

    for k in par(0, K):
        for i in par(0, M):
            for j in par(0, N):
                C[i, j] += A[i, k] * B[k, j]

SGEMM_WINDOW = (SGEMM.rename('SGEMM_WINDOW')
                .set_window('A', True)
                .set_window('B', True)
                .set_window('C', True))

# Constants for scheduling
VEC_W = 4

M_REG_BLK = 6
N_REG_BLK = (4 * VEC_W)

M_L1_FAC = 44
N_L1_FAC = 1

M_L1_BLK = M_REG_BLK * M_L1_FAC
N_L1_BLK = N_REG_BLK * N_L1_FAC
K_L1_BLK = 512

basic_kernel_Mx4 = {}
sgemm_kernel_avx512_Mx4 = {}
for M in range(1, M_REG_BLK + 1):
    basic_kernel_Mx4[M] = (
        SGEMM_WINDOW
            .rename(f'basic_kernel_{M}x4')
            .partial_eval(M, N_REG_BLK)
            .simplify()
    )
    sgemm_kernel_avx512_Mx4[M] = (
        basic_kernel_Mx4[M]
            .rename(f'sgemm_kernel_avx512_{M}x4')
            # Vectorize columns
            .split('j', VEC_W, ['jo', 'ji'], perfect=True)
            # Mark k as a reduction loop
            .par_to_seq('for k in _: _')
            # Stage C for reduction
            .stage_assn('C_reg', 'C[_] += _')
            .set_memory('C_reg', Neon4f)
            .lift_alloc('C_reg: _', n_lifts=4)
            .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
            # Stage A & B
            .stage_expr('A_vec', 'A[_, _]', memory=Neon4f)
            .stage_expr('B_vec', 'B[_, _]', memory=Neon4f)
            # Schedule ops
            .replace(neon_vld_4xf32, 'for ji in _: _ #0')
            .replace(neon_vst_4xf32, 'for ji in _: _ #3')
            .replace_all(neon_broadcast_4xf32)
            .replace_all(neon_vld_4xf32)
            .replace_all(neon_vfmadd_4xf32_4xf32)
            # LICM
            .lift_alloc('A_vec: _')
            .fission_after('neon_broadcast_4xf32(_)')
            # Clean up
            .simplify()
    )


sgemm_above_kernel = (
    SGEMM_WINDOW
        .rename('sgemm_above_kernel')
        # Split up into cases
        .split('j', N_REG_BLK, ['jo', 'ji'], tail='cut_and_guard')
        .split('i', M_REG_BLK, ['io', 'ii'], tail='cut_and_guard')
        .fission_after('for jo in _: _ #0', n_lifts=2)
        .reorder('ii #0', 'jo')
        .fission_after('for io in _: _')
        .reorder('k #0', 'io')
        .reorder('k #0', 'jo')
        .lift_if('if N % _ > 0: _ #0', n_lifts=3)
        .reorder('k', 'io')
        .lift_if('if M % _ > 0: _ #0')
        .fission_after('for jo in _: _ #1', n_lifts=2)
        .reorder('ii', 'jo')
        .reorder('k', 'jo')
        .lift_if('if N % _ > 0: _ #1', n_lifts=2)
        # Main block
        .replace_all(basic_kernel_Mx4[6])
        .call_eqv(sgemm_kernel_avx512_Mx4[6], 'basic_kernel_6x4(_)')
        
        # TODO: bottom-right tile
        .simplify()
)

sgemm_exo = (
    SGEMM
        .rename("sgemm_exo")
        # Split all loops
        .split('k', K_L1_BLK, ['ko', 'ki'], tail='cut_and_guard')
        .split('i', M_L1_BLK, ['io', 'ii'], tail='cut_and_guard')
        .split('j', N_L1_BLK, ['jo', 'ji'], tail='cut_and_guard')
        # Explode into 8 cases
        .fission_after('for io in _: _', n_lifts=2)
        .fission_after('for jo in _: _', n_lifts=4)
        # Case 1:
        .reorder('ki', 'io')
        .reorder('ii', 'jo')
        .reorder('ki', 'jo')
        .replace(SGEMM_WINDOW, 'for ki in _: _ #0')
        # Case 2:
        .lift_if('if N % _ > 0: _ #0', n_lifts=4)
        .replace(SGEMM_WINDOW, 'for ki in _: _ #0')
        # Case 3:
        .lift_if('if M % _ > 0: _ #0', n_lifts=2)
        .reorder('ki', 'jo')
        .replace(SGEMM_WINDOW, 'for ki in _: _ #0')
        # Case 4:
        .lift_if('if M % _ > 0: _ #1', n_lifts=2)
        .lift_if('if N % _ > 0: _ #1', n_lifts=3)
        .replace(SGEMM_WINDOW, 'for ki in _: _ #0')
        # Case 5:
        .replace(SGEMM_WINDOW, 'for ki in _: _ #0')
        # Case 6:
        .lift_if('if N % _ > 0: _ #2', n_lifts=3)
        .replace(SGEMM_WINDOW, 'for ki in _: _ #0')
        # Case 7:
        .lift_if('if M % _ > 0: _ #2')
        .reorder('ki', 'jo')
        .replace(SGEMM_WINDOW, 'for ki in _: _ #0')
        # Case 8:
        .lift_if('if M % _ > 0: _ #3')
        .lift_if('if N % _ > 0: _ #3', n_lifts=2)
        .replace(SGEMM_WINDOW, 'for ki in _: _ #0')
        ## Case 1 memory staging
        .stage_window('A1_cache', 'A[_] #0', DRAM_STATIC)
        .stage_window('B1_cache', 'B[_] #0', DRAM_STATIC)
        .par_to_seq('for ko in _: _ #0')
        .par_to_seq('for io in _: _ #0')
        .par_to_seq('for jo in _: _ #0')
        .lift_alloc('A1_cache: _', n_lifts=3)
        .lift_alloc('B1_cache: _', n_lifts=3)
        .fission_after('for i0 in _: _ #0')
        ## Case 2 memory staging
        .stage_window('B2_cache', 'B[_] #1', DRAM_STATIC)
        .bound_alloc('B2_cache: _', [None, f'{N_L1_BLK}'])
        .lift_alloc('B2_cache: _')
        .fission_after('for i0 in _: _ #2')
        ## Case 3 memory staging
        .stage_window('B3_cache', 'B[_] #2', DRAM_STATIC)
        ## Case 4 memory staging
        .stage_window('B4_cache', 'B[_] #3', DRAM_STATIC)
        .bound_alloc('B4_cache: _', [None, f'{N_L1_BLK}'])
        ## Case 5 memory staging
        .stage_window('B5_cache', 'B[_] #4', DRAM_STATIC)
        .bound_alloc('B5_cache: _', [f'{K_L1_BLK}', None])
        ## Case 6 memory staging
        .stage_window('B6_cache', 'B[_] #5', DRAM_STATIC)
        .bound_alloc('B6_cache: _', [f'{K_L1_BLK}', f'{N_L1_BLK}'])
        # .lift_alloc('B6_cache: _')
        # .fission_after('for i0 in _: _ #6')
        ## Case 7 memory staging
        .stage_window('B7_cache', 'B[_] #6', DRAM_STATIC)
        .bound_alloc('B7_cache: _', [f'{K_L1_BLK}', None])
        ## Case 8 memory staging
        .stage_window('B8_cache', 'B[_] #7', DRAM_STATIC)
        .bound_alloc('B8_cache: _', [f'{K_L1_BLK}', f'{N_L1_BLK}'])
        ## Replace SGEMM_WINDOW with optimized form
        # These must come AFTER bound_alloc since the internal check-effects
        # is a whole program analysis that is VERY expensive
        .repeat(Procedure.call_eqv, sgemm_above_kernel, 'SGEMM_WINDOW(_)')
        # Clean up
        .simplify()
)

__all__ = ['sgemm_exo']

file.write(sgemm_exo.c_code_str())
file.close()