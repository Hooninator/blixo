from __future__ import annotations
from concurrent.futures import process
from exo import *
from exo.libs.memories import DRAM_STATIC
from exo.platforms.x86 import *
from exo.platforms.neon import *
from exo.syntax import *



@proc
def loop_example(M: size, A: f32[M]):
    for i in par(0, M):
        A[i] = 10.0

print(loop_example.split('i', 4, ['ii', 'io'], tail='cut_and_guard'))

@proc
def loop_example_split(M: size, A: f32[M] @ DRAM):
    for ii in par(0, M / 4):
        for io in par(0, 4):
            A[4 * ii + io] = 10.0
    if M % 4 > 0:
        for io in par(0, M % 4):
            A[io + M / 4 * 4] = 10.0

@proc
def loop_kernel_2(A: [f32][4] @ DRAM):
    for io in par(0, 4):
            A[io] = 10.0



@proc
def loop_kernel(A: f32[16] @ AVX512, B: f32[16] @ AVX512, C: f32[16] @ AVX512):
    assert stride(A, 0) == 1
    assert stride(B, 0) == 1
    assert stride(C, 0) == 1
    for j in par(0, 4):
        for i in par(0, 16):
                C[i] += A[i]*B[i]

print( loop_kernel.replace_all(mm512_fmadd_ps))

print( loop_kernel.replace_all(mm512_fmadd_ps).c_code_str() )

@proc
def loop_kernel(A: f32[16] @ AVX512, B: f32[16] @ AVX512, C: f32[16] @ AVX512):
    assert stride(A, 0) == 1
    assert stride(B, 0) == 1
    assert stride(C, 0) == 1
    for j in par(0, 4):
        mm512_fmadd_ps(A, B, C[0:16])

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


generate_sgemm_microkernel(kernel=SGEMM, N_reg=32, M_reg=4, K_blk=64)
    

#Generates a GEBP kernel 
def generate_GEBP(Kernel, M_blk, K_blk):
    GEBP = (Kernel
            #Set loop bounds to block sizes
            .partial_eval(M=M_c)
            .partial_eval(K=K_c)
            #Tile the block of A and the panel of B
            .split('i', M_r, ['io', 'ii'], tail='cut_and_guard')
            .split('j', N_r, ['jo', 'ji'], tail='cut_and_guard')
            #Handle edge case
            .fission_after('for jo in _: _', n_lifts=2)
            .fission_after('for io in _: _', n_lifts=2)
            #reorder so loop ordering is same as microkernel
            .reorder('ii','jo')
            #insert microkernel
            .replace_all(microkernel)
            .call_eqv(neon_microkernel, 'microkernel(_)')
            #Stage strip of B
            .reorder('io', 'jo')
            .stage_mem(f'B[0:{K_c},'
                    f'{N_r}*jo:{N_r}*jo+{N_r}]',
                    'B_strip', 'for io in _:_ #0')
            .simplify())
    return GEBP


# Load
@instr('{dst_data} = vld1q_f32(&{src_data});')
def neon_vld_4xf32(
        dst: [f32][4] @ Neon4f,
        src: [f32][4] @ DRAM
):
    assert stride(src, 0) == 1
    assert stride(dst, 0) == 1

    for i in par(0, 4):
        dst[i] = src[i]


# Store
@instr('vst1q_f32(&{dst_data}, {src_data});')
def neon_vst_4xf32(
        dst: [f32][4] @ DRAM,
        src: [f32][4] @ Neon4f
):
    assert stride(src, 0) == 1
    assert stride(dst, 0) == 1

    for i in par(0, 4):
        dst[i] = src[i]


# Broadcast
@instr('{dst_data} = vld1q_dup_f32(&{src_data});')
def neon_broadcast_4xf32(
        dst: [f32][4] @ Neon4f,
        src: [f32][1] @ DRAM
):
    assert stride(dst, 0) == 1

    for i in par(0, 4):
        dst[i] = src[0]


# FMA
@instr('{dst_data} = vmulq_f32({lhs_data}, {rhs_data});')
def neon_vmul_4xf32(
        dst: [f32][4] @ Neon4f,
        lhs: [f32][4] @ Neon4f,
        rhs: [f32][4] @ Neon4f
):
    assert stride(dst, 0) == 1
    assert stride(lhs, 0) == 1
    assert stride(rhs, 0) == 1

    for i in par(0, 4):
        dst[i] = lhs[i] * rhs[i]




def generate_microkernel(kernel, N_reg, M_reg, K_blk):
        if N_reg%4:
                raise Exception(f"Error: N_reg must be a multiple of 4, got {N_reg}")
        return (kernel
                .partial_eval(M_reg,N_reg)
                .partial_eval(K=K_blk)
                .reorder('j','k')
                .reorder('i','k')
                .split('j', 4, ['jo','ji'], perfect=True)
                .par_to_seq('for k in _: _')
                .stage_assn('C_reg', 'C[_] += _')
                .lift_alloc('C_reg : _', n_lifts=4)
                .double_fission('C_reg[_] = C[_]', 'C_reg[_] += _', n_lifts=4)
                .replace(neon_vld_4xf32, 'for ji in _: _ #0')
                .replace(neon_vst_4xf32, 'for ji in _: _ #1')
                .set_memory('C_reg', Neon4f)
                .stage_expr('A_vec', 'A[_,_]', memory=Neon4f)
                .stage_expr('B_vec', 'B[_,_]', memory=Neon4f)
                .replace_all(neon_vld_4xf32)
                .replace_all(neon_broadcast_4xf32)
                .replace_all(neon_vfmadd_4xf32_4xf32)
                .lift_alloc('A_vec : _', n_lifts=2)
                .fission_after('neon_broadcast_4xf32(_)', n_lifts=2)
                .lift_alloc('B_vec : _', n_lifts=2)
                .fission_after('neon_vld_4xf32(_) #1', n_lifts=2)
                .simplify())