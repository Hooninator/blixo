from __future__ import annotations
from cmath import log
import sys
from concurrent.futures import process
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.syntax import *
import modular_sgemm

file = open("symm.c", 'w+')
@proc
def SYMM(M: size, N: size, K: size, A: f32[M, K], B: f32[K, N], C: f32[M, N]):
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

#microkernel sizes
M_r = 4
N_r = 4 #NOTE: This must be divisible by 4, fix that at some point
#block sizes
M_c = 8
K_c = 8
#Matrix sizes
M=512
N=512
K=512

#Block
SYMM_BLK = (SYMM
            .rename("SYMM_BLK")
            .set_window('A', True)
            .set_window('B', True)
            .set_window('C', True))

#Substitute GEPP
n_iters = int(log(M, M_c).real)
print(f"n_iters: {n_iters}")

#TODO: Refactor this into a "stage_gepp" function
SYMM_BLK = (SYMM_BLK
            .reorder('j', 'k')
            .reorder('i', 'k')
            .split('k', K_c, ['n_iters', 'k'], tail='cut_and_guard')
            .fission_after('for k in _: _ ', n_lifts=2)
            .reorder('k', 'i')
            .reorder('k', 'j')
            .simplify()
            .replace_all(modular_sgemm.GEPP_MKc)
            .call_eqv(modular_sgemm.GEPP, 'GEPP_MKc(_)')
            .partial_eval(K=K_c*n_iters)
            .simplify()
            )

print(SYMM_BLK)

#Partition B and C into B_t, B_b and C_t, C_b, the dividing line will be at row THRESHOLD
#This will have to be done at the end, since the new buffer needs to be instantly fed into a procedure
def partition_B_and_C(procedure, threshold):
    return (procedure
            .split('k', threshold, ['ki', 'ko'], tail='cut_and_guard')
            .simplify()
            #.stage_window('B_b', 'B[_] #0', DRAM_STATIC)
            #.bound_alloc('B_b', [f'{threshold}', f'{N}'])
            #.stage_mem(f'B[ki*{threshold} : ki*{threshold}+{threshold},'
             #          f'               0 : {N-1}]', 
              #         'B_t', 'for ko in _:_')
            #  .stage_mem('B[0:256, 0:256]', 'b_blk', 'for ko in _:_')
            )


file.write(SYMM_BLK.c_code_str())



"""
This does not work. The reason why is although the splitting sets up the loops just fine,
it resizes the matrices away from their original sizes. I see no option other than
editing the base procedure. 

In fact, you can't call partial eval since that resizes, and you can't call split
because you can't split appropriately in this scheme.
"""