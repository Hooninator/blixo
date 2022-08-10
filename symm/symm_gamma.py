from __future__ import annotations
from cmath import log
import sys
from concurrent.futures import process
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.syntax import *
#import modular_sgemm

file = open("symm.c", 'w+')

#microkernel sizes
M_r = 4
N_r = 4 #NOTE: This must be divisible by 4, fix that at some point
#block sizes
M_c = 4
K_c = 4
#Matrix sizes
M=16
N=16
K=16

#The limited nature of exo loops is really a problem here
@proc
def SYMM(M: size, N: size, K: size, A: f32[M, K], B: f32[K, N], C: f32[M, N]):
    assert M >= 1
    assert N >= 1
    assert K >= 1
    assert K > K_c
    assert M==K==N
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1

    for j in par(0, N):
        for i in par(0, M):
            for k in par(0, M - ((M - 1 - i) + 1)):
                C[(k + ((M - 1 - i) + 1)), j] += B[(M - 1 - i), j] * A[(k + ((M - 1 - i) + 1)), (M - 1 - i)]
                C[(M - 1 - i), j] += A[j, (M - 1 - i)] * B[j, (k + ((M - 1 - i) + 1))]
            C[(M - 1 - i), j] += B[(M - 1 - i), j] * A[(M - 1 - i), (M - 1 - i)]

#Now, scheduling
exo_symm = (SYMM
            .rename("exo_symm")
            .)
