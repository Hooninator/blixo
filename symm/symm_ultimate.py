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

file = open("symm_2.c", 'w+')

#microkernel sizes
M_r = 4
N_r = 4 #NOTE: This must be divisible by 4, fix that at some point
#block sizes
M_c = 4
K_c = 4
#Matrix sizes
M=32
N=32
K=32


#Substitute GEPP
n_iters = 1+((N-2*M_c)//M_c)
print(f"n_iters: {n_iters}")

@proc
def __SYMM_BLK(K: size, A: f32[M, K] @ DRAM, B: f32[K, N] @ DRAM,
              C: f32[M, N] @ DRAM):
    assert N >= 1
    assert K >= 1
    assert K > 4
    assert K % K_c == 0
    assert M % M_c == 0
    assert K >= K_c*(n_iters+1)
    assert M >= M_c*(n_iters+1)
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    
    for n_iter in seq(0, n_iters+1):
        A_panel: R[M, K_c] @ DRAM_STATIC
        
        #This loop handles the transposed A_10 block
        for i in par(0, (n_iter * K_c)):
            for k in par(0, M_c):
                A_panel[i, k] = A[(k + n_iter * M_c), i]
        
        #This loop handles the A_11 block 
        for i in par(0, M_c):
            for k in par(0, K_c):
                A_panel[(n_iter * K_c + i), k] = A[(i + n_iter * M_c), (k + n_iter * K_c)]
        
        #This loop handles the A_21 block
        for i in par(0, (M - M_c - (n_iter * M_c))):
            for k in par(0, K_c):
                A_panel[(M_c + n_iter * M_c + i), k] = A[(i + M_c * n_iter + M_c), (k + n_iter * K_c)]

        #This loop creates the B panel
        B_panel: R[K_c, N] @ DRAM_STATIC
        for j in par(0, N):
            for k in par(0, K_c):
                B_panel[k, j] = B[(k + (K_c * n_iter)), j]

        #Call GEPP
        modular_sgemm.GEPP(M, N, A_panel[0:M, 0:K_c], B_panel[0:K_c, 0:N], C[0:M, 0:N])

print(__SYMM_BLK)

file.write(__SYMM_BLK.c_code_str())