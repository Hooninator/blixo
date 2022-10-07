def bottom_gebp_kc(N: size, A: [f32][1, 64] @ DRAM, B: [f32][64, N] @ DRAM,
                   C: [f32][1, N] @ DRAM):
    assert 1 >= 1
    assert N >= 1
    assert 64 >= 1
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    C_reg: R[1, N / 4 + 1, 4] @ Neon4f
    C_reg_1: R[1, N % 4 + 1] @ Neon4f
    for i in par(0, 1):
        for jo in par(0, N / 4):
            neon_vld_4xf32(C_reg[i + 0, jo + 0, 0:4], C[i + 0,
                                                        4 * jo + 0:4 * jo + 4])
    for i in par(0, 1):
        for jo in par(0, N / 4):
            for ji in par(0, 4):
                for k in seq(0, 64):
                    C_reg[i, jo, ji] += A[i, k] * B[k, 4 * jo + ji]
    for i in par(0, 1):
        for jo in par(0, N / 4):
            neon_vst_4xf32(C[i + 0, 4 * jo + 0:4 * jo + 4], C_reg[i + 0,
                                                                  jo + 0, 0:4])
        if N % 4 > 0:
            for ji in par(0, N % 4):
                for k in seq(0, 64):
                    C_reg_1[i, ji] = C[i, ji + N / 4 * 4]
                    C_reg_1[i, ji] += A[i, k] * B[k, ji + N / 4 * 4]
                    C[i, ji + N / 4 * 4] = C_reg_1[i, ji]