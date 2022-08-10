def SYMM_BLK(M: size, N: size, K: size, A: [f32][M, K] @ DRAM,
             B: [f32][K, N] @ DRAM, C: [f32][M, N] @ DRAM):
    assert M >= 1
    assert N >= 1
    assert K >= 1
    assert K > 8
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    for n_iter in seq(0, 3):
        A_panel: R[M + 1, 8] @ DRAM_STATIC
        for i in par(0, M):
            for k in par(0, 8):
                A_panel[i, k] = A[i, k]
        GEPP_MKc(M, N, A_panel[0:M, 0:8], B[0:8, 0:N], C[0:M, 0:N])


"""
This demonstrates the issues with writing to A_panel
We need to access more than 8 columns to write to A_panel (up to N-K_blk),
but the upper bound of K being 8 makes this impossible.
Unless... maybe I can use the sort of like "extra" i indices?? 
I mean, this loop does contain all the i,k pairs needed to write to 
A_panel... let me try that.
"""