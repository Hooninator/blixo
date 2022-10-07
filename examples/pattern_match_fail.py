def bottom_gebp_kc(N: size, A: [f32][1, 64] @ DRAM, B: [f32][64, N] @ DRAM,
                   C: [f32][1, N] @ DRAM):
    assert 1 >= 1
    assert N >= 1
    assert 64 >= 1
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    for i in par(0, 1): #NOTE: I called .partial_eval(M=(M%64)) to create this
        for j in par(0, N):
            for k in par(0, 64):
                C[i, j] += A[i, k] * B[k, j]

def GEPP(M: size, N: size, A: [f32][M, 64] @ DRAM, B: [f32][64, N] @ DRAM,
         C: [f32][M, N] @ DRAM):
    assert M >= 1
    assert N >= 1
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    for io in par(0, M / 64):
        GEBP(N, A[64 * io:64 * io + 64, 0:64], B[0:64, 0:N],
             C[64 * io:64 * io + 64, 0:N])
    if M % 64 > 0:
        #I want to replace these loops with bottom_gebp_kc()
        for ii in par(0, M % 64): #NOTE: M%64=1
            for j in par(0, N):
                for k in par(0, 64):
                    C[ii + M / 64 * 64, j] += A[ii + M / 64 * 64, k] * B[k, j]



#???????? This matches fine if j upper bound is N
def microkernel_edge_gebp_simple(A: [f32][16, 32] @ DRAM,
                                 B: [f32][32, 1] @ DRAM,
                                 C: [f32][16, 1] @ DRAM):
    assert 16 >= 1
    assert 1 >= 1
    assert 32 >= 1
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    assert 1 < 16
    for i in par(0, 16):
        for j in par(0, 1):
            for k in par(0, 32):
                C[i, j] += A[i, k] * B[k, j]

def GEBP(A: [f32][64, 32] @ DRAM, B: [f32][32, 257] @ DRAM,
         C: [f32][64, 257] @ DRAM):
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    for io in par(0, 4):
        for jo in par(0, 16):
            neon_microkernel(A[16 * io:16 * io + 16,
                               0:32], B[0:32, 16 * jo:16 * jo + 16],
                             C[16 * io:16 * io + 16, 16 * jo:16 * jo + 16])
    for io in par(0, 4):
        for ii in par(0, 16):
            for ji in par(0, 1):
                for k in par(0, 32):
                    C[16 * io + ii,
                      ji + 256] += A[16 * io + ii, k] * B[k, ji + 256]