from __future__ import annotations
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.platforms.neon import Neon4f
from exo.syntax import *

file = open("syrk_mk.c", 'w+')
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
#SWAP THE DIMENSIONS OF
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
#file.write(SYRK.c_code_str())
#file.close()
#raise Exception

@proc
def SGEMM3(M: size, N: size, K: size, A: f32[M, K], A_t: f32[N, K], C: f32[M, N]):
    assert M >= 1
    assert N >= 1
    assert K >= 1
    assert stride(A, 1) == 1
    assert stride(A_t, 1) == 1
    assert stride(C, 1) == 1

    for i in par(0, M):
        for j in par(0, N):
            for k in par(0, K):
                C[i, j] += A[i, k]*A_t[j, k]

sgemm_window2 = (SGEMM3
                .rename('sgemm_win2')
                .set_window('A', True)
                .set_window('A_t', True)
                .set_window('C', True))

#Microkernels
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

@proc
def microkernel_three(M: size, K: size, A: [f32][M, K] @ DRAM, A_t: [f32][K, M] @ DRAM,
                C: [f32][M, M] @ DRAM):
    assert stride(A, 1) == 1
    assert stride(A_t, 1) == 1
    assert stride(C, 1) == 1
    for j in par(0, M):
        for k in par(0, K):
            C[0, j] += A[0, k] * A_t[k, j]

##TODO: MAKE MICROKERNELS THAT ARE ACTUALLY APPROPRIATE REGISTER LENGTHS AND PUT THOSE IN GEBP


#generate microkernel_twos
def generate_microkernel_two(M_dim, kernel):
    return (kernel.rename(f"neon_microkernel_two_{M_dim}")
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

simple_microkernels = {}
scheduled_microkernels = {}
for i in range(M_c, M, M_c):
    simple_microkernels[i//M_c] = microkernel_three.partial_eval(K=K_c).partial_eval(M=i).simplify()
    scheduled_microkernels[i//M_c] = generate_microkernel_two(i, simple_microkernels[i//M_c])
    print(scheduled_microkernels[i//M_c])
#file.write(simple_microkernels[1].c_code_str())
#file.write(scheduled_microkernels[1].c_code_str())
#file.close()
#raise Exception
#GEBP Kernel Generation
def generate_GEBP_kernels(M_dim):
    simple_gebp_kernels = {}
    scheduled_gebp_kernels = {}

    for i in range(M_c, M_dim, M_c):
        simple_gebp_kernels[i//M_c] = (microkernel_three
        .partial_eval(M=i)
        .partial_eval(K=K_c)
        #.partial_eval(N=i)
        .rename(f'GEBP_{i}x{K_c}')
        #.specialize('for j in _:_ #0', [f'i=={i}' for i in range(M_c)])
        .simplify())

        scheduled_gebp_kernels[i//M_c] = (simple_gebp_kernels[i//M_c]
                                            .rename("GEBP_scheduled")
                                            .split('j', N_r, ['jo', 'ji'], tail='cut_and_guard')
                                            .replace_all(simple_microkernels[1])
                                            .repeat(Procedure.call_eqv, scheduled_microkernels[1], 'microkernel_three(_)')
                                            .simplify())
        print(scheduled_gebp_kernels[i//M_c])
    return (simple_gebp_kernels, scheduled_gebp_kernels)
#TODO: Figure out how to get GEBP into GEPP





# Generate GEPP
simple_gebp_kernels, scheduled_gebp_kernels = generate_GEBP_kernels(N)
GEPP_syrk_intermediate = (syrk_window
            .rename("GEPP_syrk_intermediate")
            .partial_eval(K=K_c)
            .simplify()
)


GEPP_syrk = (GEPP_syrk_intermediate
            .rename("GEPP_syrk")
            .specialize('for j in _ : _ #0', [f'i=={i}' for i in range(0, M)]) 
            .simplify()
            )

#partition into sgemm and diagonal kernel
partition = M_c
temp = 0
for i in range(M_c, 2*M-(M_c), 2*M_c):
    for j in range(0, 2*M_c, 2):
        GEPP_syrk = (GEPP_syrk.partition_loop(f'j #{i+j+temp}', partition).simplify())
    partition+=M_c

for i in range(M_c, M):
    GEPP_syrk = (GEPP_syrk.split(f'j #{i}', N_r, ['jo', 'ji'], tail='cut_and_guard').simplify())
    GEPP_syrk = GEPP_syrk.replace(simple_gebp_kernels[1], f'for ji in _:_ #0').simplify().call_eqv(scheduled_gebp_kernels[1], 'GEBP_4x4(_)').simplify()


print(GEPP_syrk)

# Sub in microkernels
#test_mkernel = 
#GEPP_syrk = (GEPP_syrk.replace(simple_microkernels[1], 'for j in _:_ #3').repeat(Procedure.call_eqv, scheduled_microkernels[1], 'microkernel_two(_)'))
for k in simple_microkernels.keys():
    break
    GEPP_syrk = (GEPP_syrk.replace_all(simple_microkernels[k]).repeat(Procedure.call_eqv, scheduled_microkernels[k], 'microkernel_three(_)'))

# schedule GEPP
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
