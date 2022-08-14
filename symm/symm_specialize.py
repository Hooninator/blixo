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
M=16
N=16
K=16

@proc
def SYMM(M: size, N: size, K: size, A: f32[M, K], B: f32[K, N], C: f32[M, N], N_ITERS: size):
    assert M >= 1
    assert N >= 1
    assert K >= 1
    assert K > K_c
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1

    #A_panel : f32[M, K_c]
    
    #A_11 : f32[M_c, K_c]
    #A_10 : f32[M_c, K_c]
    #A_21 : f32[M_c*2, K_c]

    #Copy A_21 and A_11 in
    #for j in par(M_c, M_c+M_c):
    #    for j in par(0, K_c*2):


    #for n_iter in seq(0, N_ITERS):

        #modular_sgemm.GEPP(M, N, A[0:M, 0:8], B[0:8, 0:N], C[0:M, 0:N])
    for n_iter in seq(0, N_ITERS):
        for i in par(0, M):
            for j in par(0, N):
                for k in par(0, K_c):
                    C[i, j] += A[i, k] * B[k, j]
                        



#Block
SYMM_BLK = (SYMM
            .rename("SYMM_BLK")
            .set_window('A', True)
            .set_window('B', True)
            .set_window('C', True))

#Substitute GEPP
n_iters = (1+((N-2*M_c)//M_c)) + 1
print(f"n_iters: {n_iters}")


SYMM_BLK = (SYMM_BLK
            .partial_eval(N_ITERS = n_iters)
            #Set up A_panel
            .stage_expr('A_panel', 'A[_, _]', memory=DRAM_STATIC)
            .lift_alloc('A_panel : _', n_lifts=2)
            .fission_after('C[_] += _ ', n_lifts=2)
            
            #Somehow mess with the A_panel loop so it writes the proper indices 
            #NOTE: To make this work, you need to do the specialize thingy, but with n_iter and multipky first parititon K_c by each value in 0..n_iters
            #NOTE: Would really be nice if I could somehow refer to the loop variable n_iter in the first partition_loop
            .partial_eval(M=M)
            .partial_eval(K=K)
            .simplify()
            )
print(SYMM_BLK)
exo_symm = (SYMM_BLK
            .rename("exo_symm")
            .specialize("for i in _ : _ #0", [f"n_iter=={i}" for i in range(0, n_iters)])
            .simplify()
            )
print(exo_symm)

@proc
def exo_symm(N: size, K: size, A: [f32][16, K] @ DRAM, B: [f32][K, N] @ DRAM,
             C: [f32][16, N] @ DRAM):
    assert 16 >= 1
    assert N >= 1
    assert K >= 1
    assert K > 4
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    for n_iter in seq(0, 4):
        A_panel: R[16 + 1, 4] @ DRAM_STATIC
        if n_iter == 0:
            for i in par(0, 16):
                for k in par(0, 4):
                    A_panel[i, k] = A[i, k]
        else:
            if n_iter == 1:
                for i in par(0, 16):
                    for k in par(0, 4):
                        A_panel[i, k] = A[i, k]
            else:
                if n_iter == 2:
                    for i in par(0, 16):
                        for k in par(0, 4):
                            A_panel[i, k] = A[i, k]
                else:
                    if n_iter == 3:
                        for i in par(0, 16):
                            for k in par(0, 4):
                                A_panel[i, k] = A[i, k]
                    else:
                        for i in par(0, 16):
                            for k in par(0, 4):
                                A_panel[i, k] = A[i, k]
        for i in par(0, 16):
            for j in par(0, N):
                for k in par(0, 4):
                    C[i, j] += A_panel[i, k] * B[k, j]

@proc
def partition_A(A_panel: R[M+1, K_c] @ DRAM_STATIC, A: [f32][M, K] @ DRAM):
    for i in par(0, 16):
        for k in par(0, 4):
            A_panel[i, k] = A[i, k]

symm_kernels = {}
scheduled_symm_kernels = {}
for i in range(0, n_iters):
    symm_kernels[i] = (partition_A
                        .rename(f"partition_A_{i}")

                        .simplify())
    try:
        exo_symm = (exo_symm.replace(symm_kernels[i], f'for i in _ : _ #{0}'))
    except:
        print(i)
        continue

print(exo_symm)

for i in range(0, n_iters):
    scheduled_symm_kernels[i] = (symm_kernels[i])
    scheduled_symm_kernels[i] = scheduled_symm_kernels[i].partition_loop(f'i #0', i*K_c).partition_loop(f'i #1', M_c).simplify()
    scheduled_symm_kernels[i] = scheduled_symm_kernels[i].stage_mem(f'A[{i}*{K_c}:{M},' f'0]',
                                                                        'A_ppanel', 'for i in _:_ #1')
    print(scheduled_symm_kernels[i])
for i in range(0, n_iters):
    try:
        exo_symm = exo_symm.call_eqv(scheduled_symm_kernels[i], f'partition_A_{i}(_) #{0}')
    except:
        print(i)
        continue
print(exo_symm)
"""
Traceback (most recent call last):
  File "/home/ubuntu/julian_working/symm/symm_specialize.py", line 95, in <module>
    .partition_loop(f'i #0', i*K_c)
  File "/home/ubuntu/exo/src/exo/API.py", line 811, in partition_loop
    loopir  = Schedules.DoPartitionLoop(p._loopir_proc, s, num).result()
  File "/home/ubuntu/exo/src/exo/LoopIR_scheduling.py", line 112, in __init__
    super().__init__(proc)
  File "/home/ubuntu/exo/src/exo/LoopIR.py", line 485, in __init__
    body = self.map_stmts(self.orig_proc.body)
  File "/home/ubuntu/exo/src/exo/LoopIR.py", line 504, in map_stmts
    return [ s for b in stmts
  File "/home/ubuntu/exo/src/exo/LoopIR.py", line 505, in <listcomp>
    for s in self.map_s(b) ]
  File "/home/ubuntu/exo/src/exo/LoopIR_scheduling.py", line 144, in map_s
    return super().map_s(s)
  File "/home/ubuntu/exo/src/exo/LoopIR.py", line 529, in map_s
    self.map_stmts(s.body),
  File "/home/ubuntu/exo/src/exo/LoopIR.py", line 504, in map_stmts
    return [ s for b in stmts
  File "/home/ubuntu/exo/src/exo/LoopIR.py", line 505, in <listcomp>
    for s in self.map_s(b) ]
  File "/home/ubuntu/exo/src/exo/LoopIR_scheduling.py", line 121, in map_s
    raise SchedulingError("expected loop bound to be constant")
exo.new_eff.SchedulingError: partition_loop: expected loop bound to be constant
"""



def partition_A_0(A_panel: R[17, 4] @ DRAM_STATIC, A: [f32][16, 16] @ DRAM):
    for i in par(0, 4):
        for k in par(0, 4):
            A_panel[i, k] = A[i, k]
    for i in par(0, 12):
        for k in par(0, 4):
            A_panel[i + 4, k] = A[i + 4, k]

def partition_A_1(A_panel: R[17, 4] @ DRAM_STATIC, A: [f32][16, 16] @ DRAM):
    for i in par(0, 4):
        for k in par(0, 4):
            A_panel[i, k] = A[i, k]
    for i in par(0, 4):
        for k in par(0, 4):
            A_panel[i + 4, k] = A[i + 4, k]
    for i in par(0, 8):
        for k in par(0, 4):
            A_panel[i + 8, k] = A[i + 8, k]

def partition_A_2(A_panel: R[17, 4] @ DRAM_STATIC, A: [f32][16, 16] @ DRAM):
    for i in par(0, 8):
        for k in par(0, 4):
            A_panel[i, k] = A[i, k]
    for i in par(0, 4):
        for k in par(0, 4):
            A_panel[i + 8, k] = A[i + 8, k]
    for i in par(0, 4):
        for k in par(0, 4):
            A_panel[i + 12, k] = A[i + 12, k]

def exo_symm(N: size, K: size, A: [f32][16, K] @ DRAM, B: [f32][K, N] @ DRAM,
             C: [f32][16, N] @ DRAM):
    assert 16 >= 1
    assert N >= 1
    assert K >= 1
    assert K > 4
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    for n_iter in seq(0, 4):
        A_panel: R[16 + 1, 4] @ DRAM_STATIC
        if n_iter == 0:
            partition_A_0(A_panel, A[0:16, 0:16])
        else:
            if n_iter == 1:
                partition_A_1(A_panel, A[0:16, 0:16])
            else:
                if n_iter == 2:
                    partition_A_2(A_panel, A[0:16, 0:16])
                else:
                    if n_iter == 3:
                        partition_A_3(A_panel, A[0:16, 0:16])
                    else:
                        for i in par(0, 16):
                            for k in par(0, 4):
                                A_panel[i, k] = A[i, k]
        for i in par(0, 16):
            for j in par(0, N):
                for k in par(0, 4):
                    C[i, j] += A_panel[i, k] * B[k, j]