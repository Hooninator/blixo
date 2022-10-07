from __future__ import annotations
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.platforms.neon import Neon4f
from exo.syntax import *

file = open("trmm.c", 'w+')
#microkernel sizes
M_r = 6
N_r = 4 #NOTE: This must be divisible by 4
#block sizes
M_c = 4 
K_c = 8
#Matrix sizes
M=16
N=16
K=16
#Thing to mention in slides: have to rewrite kernels for each operation because indexing not the same

@proc
def TRMM(M: size, N: size, A: f32[M, M], B: f32[M, N]):
    for j in seq(0, N):
        for k in seq(0, M):
            for i in seq(0, k):
                B[i, j] += B[k, j]*A[i, k]
            B[k, j] = A[k, k]*B[k, j]



trmm_window = (TRMM
                .rename("trmm_window")
                .set_window('A', True)
                .set_window('B', True))


GEPP_trmm_intermediate = (trmm_window
                .rename("GEPP_trmm_intermediate")
                .partial_eval(M=K_c)
                .reorder('j', 'k')
                .simplify())

file.write(GEPP_trmm_intermediate.c_code_str())

exo_trmm = (TRMM
            .rename("exo_trmm")
            .reorder('j', 'k')
            .split('k', K_c, ['ki', 'ko'], tail='cut_and_guard')
            .fission_after('for ko in _: _ ', n_lifts=2)
            #.reorder('ko', 'j')
            .specialize('for ko in _:_ #0', [f'ki=={i}' for i in range(M//K_c)])
            .simplify()
            #.replace_all(GEPP_trmm_intermediate)
            )

file.write(exo_trmm.c_code_str())

for i in range(M//K_c):
    exo_trmm = exo_trmm.replace(GEPP_trmm_intermediate, 'for ko in _:_ #0')

print(exo_trmm)
#Fundamental problem is the fact that the loop var you split by also happens to be the triangular thing -- that SUCKS
#Need some alternate way to index this thing that does not have a loop bound determined by the same loop that indexes the rows of B and olumns of A
#Is that possible? Maybe -- maybe not?
#OR if there's a way to increase the k loop bound so it has a +(a*K_c) integer added to it then you could totally do this 
#You could do that manually obviously, but that's a non-starter for obvious reasons so need a way to generate it. 
#Like it should be possible? Since theoretically it's just a larger k looop upper bound. I tried calling partial_eval(K=K_c*2) but that didnt work
#even though the upper bound of the k loops are the same in that case. So I think it NEEDS the +8 -- yeah it needs that bc offset is 8 not loop bound 16.
#The only thing I know that could do that is stage_mem? What would that even look like? well no the problem is that the buffer is indexed starting at 8
#Stage mem sure it can create a buffer that is indexed, but then exo will be like "oh well THAT Buffer will again be offset by 8" so its not equiv.
#Even if you moved away from GEPP and GEBP it still would fail because you have to block based on the i loop at some point, which is the reaon
#GEPP is impossible. 
file.write(TRMM.c_code_str())
file.close()