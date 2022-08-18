from __future__ import annotations
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.syntax import *
import time
import modular_sgemm

stime = time.time()
file = open("syrk.c", 'w+')

#microkernel sizes
M_r = 4
N_r = 4 #NOTE: This must be divisible by 4
#block sizes
M_c = 4 
K_c = 4
#Matrix sizes
M=16
N=16

@proc
def SYRK(M: size, K: size, A: f32[M, K], C: f32[M, K]):
    assert M >= 1
    assert K >= 1
    assert K==M
    assert stride(A, 1) == 1
    assert stride(C, 1) == 1

    for j in par(0, M):
        for i in par(0, j+1):
            for k in par(0, K):
                C[i, j] += A[k, i]*A[k, j]
"""
We're gonna need separate GEPP routines for 
"""
exo_syrk = (SYRK
            .rename("exo_syrk")
            
            .simplify())

file.write(SYRK.c_code_str())
file.close()