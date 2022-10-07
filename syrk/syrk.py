from __future__ import annotations
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.syntax import *
import time
#import modular_sgemm

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
K=16

#A_t should be the A treated as if it was transposed, but when you pass the argument it should be a copy of A
@proc
def SYRK(M: size, K: size, A: f32[M, K], A_t: f32[M, K], C: f32[M, M]):
    assert M >= 1
    assert K >= 1
    assert stride(A, 1) == 1
    assert stride(A_t, 1) == 1
    assert stride(C, 1) == 1

    for i in par(0, M):
        for j in par(0, i+1):
            for k in par(0, K):
                C[i, j] += A[i, k]*A_t[j, k]

#file.write(SYRK.c_code_str())
syrk_window = (SYRK
                .rename('syrk_win')
                .set_window('A', True)
                .set_window('A_t', True)
                .set_window('C', True))

#print(syrk_window.rename("GEPP_example").partial_eval(K=K_c).split('i', M_c, ['io', 'ii'], tail='cut_and_guard').simplify().split('j', K_c, ['jo', 'ji'], tail='cut_and_guard').fission_after('for ji in _:_', n_lifts=2))

@proc
def SGEMM(M: size, N: size, K: size, A: f32[M, K], B: f32[K, N], C: f32[M, N]):
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


#Changing this doesnt work because 
@proc
def SGEMM3(M: size, N: size, K: size, A: f32[M, K], A_t: f32[N, K], C: f32[M, N]):
    assert M >= 1
    assert N >= 1
    assert K >= 1
    #assert K==M
    assert stride(A, 1) == 1
    assert stride(A_t, 1) == 1
    assert stride(C, 1) == 1

    for i in par(0, M):
        for j in par(0, N):
            for k in par(0, K):
                C[i, j] += A[i, k]*A_t[j, k]

sgemm_window = (SGEMM
                .rename('sgemm_win')
                .set_window('A', True)
                .set_window('A_t', True)
                .set_window('C', True))
sgemm_window2 = (SGEMM3
                .rename('sgemm_win2')
                .set_window('A', True)
                .set_window('A_t', True)
                .set_window('C', True))
#print(sgemm_window2.rename("GEBP_example").partial_eval(K=K_c).partial_eval(M=M_c).partial_eval(N=4).simplify())

#Microkernels

#Standard microkenel
microkernel = (sgemm_window2
                .rename('microkernel')
                .partial_eval(M_r,N_r)
                .partial_eval(K=K_c)
                .simplify())
#file.write(microkernel.c_code_str())
print(microkernel)
neon_microkernel = (microkernel
                    .rename('neon_microkernel')
                    .reorder('j','k')
                    .reorder('i','k')
                    #.reorder('i','j')
                    #Somehow, using this split command resizes C 
                    .split('j', 4, ['jo','ji'], perfect=True)
                    .par_to_seq('for k in _: _')
                    .stage_assn('C_reg', 'C[_] += _')
                    .set_memory('C_reg', Neon4f)
                    .lift_alloc('C_reg : _', n_lifts=3)
                    #double fission lifts both statements out and copies the loops they're wrapped in
                    .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
                    .replace(neon_vld_4xf32, 'for ji in _: _ #0')
                    .replace(neon_vst_4xf32, 'for ji in _: _ #1')
                    )
print(neon_microkernel)

neon_microkernel = (neon_microkernel
                    .stage_expr('A_vec', 'A[_,_]', memory=Neon4f)
                    .stage_expr('A_t_vec', 'A_t[_,_]', memory=Neon4f)
                    #.replace(neon_vld_4xf32, 'for ji in _: _ #0')
                    #.replace(neon_vst_4xf32, 'for ii in _:_ #3')
                    .replace_all(neon_vld_4xf32)
                    .replace_all(neon_broadcast_4xf32)
                    .replace_all(neon_vfmadd_4xf32_4xf32)
                    #.lift_alloc('B_vec: _')
                    #.fission_after('neon_broadcast_4xf32(_)')
                    #lift_alloc and fission_after are used to split up bodies of loops
                    .lift_alloc('A_vec : _', n_lifts=2)
                    .fission_after('neon_broadcast_4xf32(_)', n_lifts=2)
                    .lift_alloc('A_t_vec : _', n_lifts=2)
                    .fission_after('neon_vld_4xf32(_) #1', n_lifts=2)
                    #.unroll('i') #NOTE: For some reason, trying to unroll i causes a recursion depth exception
                    #.unroll('k') NOTE: This leads to no performance improvement, and it also makes generation take a long time
                    .unroll('jo')
                    .simplify())
print(neon_microkernel)



###NEW MICROKERNELS
@proc
def microkernel_two(M: size, K: size, A: [f32][M, K] @ DRAM, A_t: [f32][M, K] @ DRAM,
                C: [f32][M, M] @ DRAM):
    assert stride(A, 1) == 1
    assert stride(A_t, 1) == 1
    assert stride(C, 1) == 1
    for j in par(0, M):
        for k in par(0, K):
            C[0, j] += A[0, k] * A_t[j, k]

"""

Basic idea
    - Generate GEBPs for all the partitioned loop bounds in GEPP
    - Generate GEPPs for all the possible values of i..j+1
    - Figure out diagonal kernel

We need to modify GEBP so it accepts and operates on progressively smaller panels of C.
This means calling partial_eval() for different values of N, and then packing B to be the appropriate size,
then calling the appropriate GEBP kernel

So now, what GEBP kernels do we need to generate?
We need one for each possible length of C_panel.
What are those possible lengths?
From 1 to N. Obviously the height of C_panel is just K_blk. Okay that should work.

So how do we have to modify GEPP?
It needs to iterate from 0 to N (M==N so j loop should work for this) and call the proper GEBP
for each iteration. BUT keep in mind the length of C_panel won't increase by 1 for each iteration.
It will instead increase by K_c at each iteration.
So, we just need to split the j loop by K_c, call specialize, and pattern match with each of the GEBP kernels.

Now, to figure out this diagonal nonsense. 
I think we could use partition_loop to partition one of the loops such that the first part handles GEBP and the second part does this diagonal thing.
What should the kernel do lol -- goto and van de geijn are like "oh its a SPECIAL kernel"
The kernel should accept a K_c*K_c block, and the upper half of this block will be all zeros. So it's just GEBP modified to only deal with the lower triangle of C.

def GEBP_MKc(N: size, A: [f32][4, 4] @ DRAM, B: [f32][4, N] @ DRAM,
             C: [f32][4, N] @ DRAM):
    assert 4 >= 1
    assert N >= 1
    assert 4 >= 1
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    for i in par(0, 4):
        for j in par(0, N):
            for k in par(0, 4):
                C[i, j] += A[i, k] * B[k, j]
"""
#generate microkernel_twos
def generate_microkernel_two(M_dim, kernel):
    return (kernel.rename(f"neon_microkernel_two_{M_dim}")
                        .reorder('j','k')
                        .split('j', 4, ['jo','ji'], perfect=True)
                        .par_to_seq('for k in _: _')
                        .stage_assn('C_reg', 'C[_] += _')
                        .set_memory('C_reg', Neon4f)
                        .lift_alloc('C_reg : _', n_lifts=2)
                        .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
                        .replace(neon_vld_4xf32, 'for ji in _: _ #0')
                        .replace(neon_vst_4xf32, 'for ji in _: _ #1')
                        .stage_expr('A_vec', 'A[_,_]', memory=Neon4f)
                        .stage_expr('A_t_vec', 'A_t[_,_]', memory=Neon4f)
                        .replace_all(neon_vld_4xf32)
                        .replace_all(neon_broadcast_4xf32)
                        .replace_all(neon_vfmadd_4xf32_4xf32)
                        .lift_alloc('A_vec : _', n_lifts=2)
                        .fission_after('neon_broadcast_4xf32(_)', n_lifts=2)
                        .lift_alloc('A_t_vec : _', n_lifts=2)
                        .fission_after('neon_vld_4xf32(_) #1', n_lifts=2)
                        .unroll('jo'))

simple_microkernels = {}
scheduled_microkernels = {}
for i in range(M_c, M, M_c):
    simple_microkernels[i//M_c] = microkernel_two.partial_eval(K=K_c).partial_eval(M=i).simplify()
    scheduled_microkernels[i//M_c] = generate_microkernel_two(i, simple_microkernels[i//M_c])

#GEBP Kernel Generation
def generate_GEBP_kernels(M_dim):
    simple_gebp_kernels = {}
    scheduled_gebp_kernels = {}

    for i in range(M_c, M_dim, M_c):
        simple_gebp_kernels[i//M_c] = (sgemm_window2
        .partial_eval(M=M_c)
        .partial_eval(K=K_c)
        .partial_eval(N=i)
        .rename(f'GEBP_{i}x{K_c}')
        #.reorder('i', 'j')
        #.add_assertion('')
        .specialize('for j in _:_ #0', [f'i=={i}' for i in range(M_c)])
        .simplify())

        print(simple_gebp_kernels[i//M_c])
        scheduled_gebp_kernels[i//M_c] = (simple_gebp_kernels[i//M_c]
                                            .replace_all(simple_microkernels[i//M_c])
                                            .repeat(Procedure.call_eqv, scheduled_microkernels[i//M_c], 'microkernel_two(_)')
                                            .simplify())
        
        print(scheduled_gebp_kernels[i//M_c])

        continue
        scheduled_gebp_kernels[i//M_c] = (simple_gebp_kernels[i//M_c]
                                    #.reorder('j', 'i')
                                    #Tile the block of A and the panel of B
                                    .split('i', N_r, ['io', 'ii'], tail='cut_and_guard')
                                    .split('j', M_r, ['jo', 'ji'], tail='cut_and_guard')
                                    #Handle edge case
                                    .fission_after('for jo in _: _', n_lifts=2)
                                    .fission_after('for io in _: _', n_lifts=2)
                                    #reorder so loop ordering is same as microkernel
                                    .reorder('ii','jo')
                                    .simplify()
                                    .replace_all(microkernel_two)
                                    #.replace(microkernel, 'for ii in _:_ #0')
                                    #.call_eqv(neon_microkernel, 'microkernel(_)')
                                    #.replace_all(microkernel_edge_gebp) TODO: Handle edge cases later
                                    #.replace_all(microkernel_edge_gebp_simple)
                                    #.call_eqv(microkernel_edge_gebp_scheduled, 'microkernel_edge_gebp(_)')
                                    .simplify()
                                    )
        print(scheduled_gebp_kernels[i//M_c])
    return (simple_gebp_kernels, scheduled_gebp_kernels)






# Generate GEPP
simple_gebp_kernels, scheduled_gebp_kernels = generate_GEBP_kernels(N)
GEPP_syrk_intermediate = (syrk_window
            .rename("GEPP_syrk_intermediate")
            .partial_eval(K=K_c)
            .simplify()
)

print(GEPP_syrk_intermediate)

GEPP_syrk = (GEPP_syrk_intermediate
            .rename("GEPP_syrk")
            #.split('j', K_c, ['jo', 'ji'], tail='cut_and_guard')
            #.fission_after('for ji in _:_ #1', n_lifts=2)
            #.split('i', M_c, ['io', 'ii'], tail='cut_and_guard')
            #.fission_after('for ii in _:_ #1', n_lifts=2)
            .specialize('for j in _ : _ #0', [f'i=={i}' for i in range(0, M)]) #ORIGINALLY M//M_c
            #.repeat(Procedure.specialize, 'for j in _ : _ #0', [f'ii=={i}' for i in range(0, M_c)])
            #.specialize('for j in _:_ #1', [f'ii=={i}' for i in range(0, M_c)])
            #.simplify()
            #.partition_loop('j #1', K_c)
            #.simplify()
            #.fission_after('for k in _:_ #2', n_lifts=1)
            #.simplify()
            #.replace_all(simple_gebp_kernels[1])
            .simplify()
            )
#print(GEPP_syrk)
#remove variables in the loop bounds
for i in range(0, M+M_c, M_c+1):
    break
    GEPP_syrk = (GEPP_syrk.specialize(f'for j in _:_ #{i}', [f'ii=={j}' for j in range(0, M_c)]).simplify())
print(GEPP_syrk)

#partition into sgemm and diagonal kernel
temp = 0
partition = M_c
for i in range(M_c, 2*M-(M_c), 2*M_c):
    for j in range(0, 2*M_c, 2):
        print(i+j+temp)
        GEPP_syrk = (GEPP_syrk.partition_loop(f'j #{i+j+temp}', partition).simplify())
    #temp+=1
    partition+=M_c
print(GEPP_syrk)
GEPP_syrk = (GEPP_syrk.replace_all(simple_microkernels[1]).repeat(Procedure.call_eqv, scheduled_microkernels[1], 'microkernel_two(_)'))
GEPP_syrk = (GEPP_syrk.replace_all(simple_microkernels[2]).repeat(Procedure.call_eqv, scheduled_microkernels[2], 'microkernel_two(_)'))
GEPP_syrk = (GEPP_syrk.replace_all(simple_microkernels[3]).repeat(Procedure.call_eqv, scheduled_microkernels[3], 'microkernel_two(_)'))
print(GEPP_syrk)
"""
Fundamental problem: we can't use specialize because the loop with the variables is nested, and it MUST be nested to move triangularly thru the matrix.
We need to figure out a way to generate a GEBP kernel that can pattern match with a variable upper bound for loop i
"""
"""
# Partition each loop
temp = 1
for i in range(1, (K_c*2)-1, 2):
    GEPP_syrk = (GEPP_syrk.partition_loop(f'i #{i}', temp*K_c))
    temp+=1

# Substitute GEBP Kernels 
for i in range(1, N//K_c):
    GEPP_syrk = GEPP_syrk.replace(simple_gebp_kernels[i], f'for i in _:_ #{i}')
    GEPP_syrk = GEPP_syrk.call_eqv(scheduled_gebp_kernels[i], f"GEBP_{K_c}x{i*K_c}(_)")

print(GEPP_syrk)
"""

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
            #.partial_eval(N=N)
            .simplify())
print(exo_syrk)
file.write(exo_syrk.c_code_str())
file.close()
