def neon_microkernel(A: [f32][32, 64] @ DRAM, B: [f32][64, 8] @ DRAM,
                     C: [f32][32, 8] @ DRAM):
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    C_reg: R[32, 2, 4] @ Neon4f
    for i in par(0, 32):
        for jo in par(0, 2):
            neon_vld_4xf32(C_reg[i, jo, 0:4], C[i, 4 * jo:4 * jo + 4])
    A_vec: R[32, 4] @ Neon4f
    for k in seq(0, 64):
        for i in par(0, 32):
            neon_broadcast_4xf32(A_vec[i, 0:4], A[i, k:k + 1])
    for k in seq(0, 64):
        B_vec: R[2, 4] @ Neon4f
        for jo in par(0, 2):
            neon_vld_4xf32(B_vec[jo, 0:4], B[k, 4 * jo:4 * jo + 4])
        for i in par(0, 32):
            for jo in par(0, 2):
                neon_vfmadd_4xf32_4xf32(C_reg[i, jo, 0:4], A_vec[i, 0:4],
                                        B_vec[jo, 0:4])
    for i in par(0, 32):
        for jo in par(0, 2):
            neon_vst_4xf32(C[i, 4 * jo:4 * jo + 4], C_reg[i, jo, 0:4])