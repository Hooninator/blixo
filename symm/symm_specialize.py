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
            #.partial_eval(M=M)
            .partial_eval(K=K)
            .simplify()
            )
print(SYMM_BLK)
exo_symm = (SYMM_BLK
            .rename("exo_symm")
            .specialize("for i in _ : _ #0", [f"n_iter=={i}" for i in range(0, n_iters)])
            .simplify()
            .partial_eval(N=N) #Do this otherwise DRAM_STATIC complains'
            .stage_expr('B_panel', 'B[_, _]', memory=DRAM_STATIC)
            .lift_alloc('B_panel : _', n_lifts=2)
            .fission_after('C[_] += _ ', n_lifts=2)
            .rearrange_dim('B_panel : _', [1, 0])
            .specialize("for j in _ : _ #0", [f"n_iter=={i}" for i in range(0, n_iters)])
            .replace_all(modular_sgemm.GEPP_MKc)
            .call_eqv(modular_sgemm.GEPP, "GEPP_MKc(_)")
            .partial_eval(M=M) #You have to do this in order to split the loops
            .simplify()
            )
print(exo_symm)

#Insane partitioning nonsense for A
for i in range(0, n_iters):
    exo_symm = (exo_symm.partition_loop(f'i #{3*i}', i*K_c)) # Partition for A_10
    if i < n_iters-1:
        exo_symm = (exo_symm.partition_loop(f'i #{3*i + 1}', M_c)) # Partition for A_11, remaining loop handles A_20
        exo_symm = (exo_symm.stage_mem(f'A[{i*M_c}:{i*M_c+M_c},' f'0:{i*K_c}]',
                        'A_10', f'for i in _:_ #{3*i}') # Write to A_10
                        .rearrange_dim('A_10 : _', [1, 0]) # Transpose 
                        .stage_mem(f'A[n_iter*{K_c}:n_iter*{K_c}+{M_c},' f'n_iter*{K_c}:n_iter*{K_c}+{K_c}]',
                        'A_11', f'for i in _:_ #{3*i + 1}') # Write to A_11
                        .stage_mem(f'A[{i*K_c+M_c}:{M},' f'{i*K_c+K_c}:{K}]',
                        'A_20', f'for i in _:_ #{3*i + 2}')) # Write to A_20
    else: # Seperate case for the last iteration, since there's no loop that writes to A_20
        exo_symm = (exo_symm.stage_mem(f'A[{i*M_c}:{i*M_c+M_c},' f'0:{i*K_c}]',
                        'A_10', f'for i in _:_ #{3*i}')
                        .rearrange_dim('A_10 : _', [1, 0]) 
                        .stage_mem(f'A[{i*K_c}:{i*K_c+M_c},' f'{i*K_c}:{i*K_c+K_c}]',
                        'A_11', f'for i in _:_ #{3*i + 1}'))
    print(exo_symm)
exo_symm = exo_symm.simplify()

for i in range(0, n_iters):
    continue
    #exo_symm = (exo_symm
    #            .stage_mem(f'B[{K_c * i}:{K_c * i + K_c},' f'0:{N}]',
    #                        'B_1', f'for j in _:_ #{i}'))
    #print(exo_symm)
file.write(exo_symm.c_code_str())

def exo_symm(A: [f32][16, 16] @ DRAM, B: [f32][16, 16] @ DRAM,
             C: [f32][16, 16] @ DRAM):
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    for n_iter in seq(0, 4):
        A_panel: R[17, 4] @ DRAM_STATIC
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
    ...