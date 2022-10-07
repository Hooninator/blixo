def neon_microkernel_edge_gebp(N: size, A: [f32][64, 64] @ DRAM,
                               B: [f32][64, N] @ DRAM, C: [f32][64, N] @ DRAM):
    assert N >= 1
    assert stride(A, 1) == 1
    assert stride(B, 1) == 1
    assert stride(C, 1) == 1
    assert N < 12
    C_reg: R[64, N / 4 + 1, 4] @ Neon4f
    C_reg_1: R[64, N % 4 + 1] @ Neon4f
    for i in par(0, 64):
        for jo in par(0, N / 4):
            neon_vld_4xf32(C_reg[i, jo, 0:4], C[i, 4 * jo:4 * jo + 4])
    for k in seq(0, 64):
        A_vec: R[64, 4] @ Neon4f
        for i in par(0, 64):
            neon_broadcast_4xf32(A_vec[i, 0:4], A[i, k:k + 1])
        B_vec: R[N / 4 + 1, 4] @ Neon4f
        for jo in par(0, N / 4):
            neon_vld_4xf32(B_vec[jo, 0:4], B[k, 4 * jo:4 * jo + 4])
        for i in par(0, 64):
            for jo in par(0, N / 4):
                neon_vfmadd_4xf32_4xf32(C_reg[i, jo, 0:4], A_vec[i, 0:4],
                                        B_vec[jo, 0:4])
    for k in seq(0, 64):
        for i in par(0, 64):
            for jo in par(0, N / 4):
                neon_vst_4xf32(C[i, 4 * jo:4 * jo + 4], C_reg[i, jo, 0:4])
            if N % 4 > 0:
                for ji in par(0, N % 4):
                    C_reg_1[i, ji] = C[i, ji + N / 4 * 4]
                    C_reg_1[i, ji] += A[i, k] * B[k, ji + N / 4 * 4]
                    C[i, ji + N / 4 * 4] = C_reg_1[i, ji]

"""
Traceback (most recent call last):
  File "/home/ubuntu/julian_working/modular_sgemm.py", line 201, in <module>
    print(neon_microkernel_edge_gebp.c_code_str())
  File "/home/ubuntu/exo/src/exo/API.py", line 255, in c_code_str
    decls, defns = compile_to_strings("c_code_str", [self._loopir_proc])
  File "/home/ubuntu/exo/src/exo/LoopIR_compiler.py", line 335, in compile_to_strings
    comp = Compiler(p, ctxt_name)
  File "/home/ubuntu/exo/src/exo/LoopIR_compiler.py", line 432, in __init__
    self.comp_stmts(self.proc.body)
  File "/home/ubuntu/exo/src/exo/LoopIR_compiler.py", line 456, in comp_stmts
    self.comp_s(b)
  File "/home/ubuntu/exo/src/exo/LoopIR_compiler.py", line 652, in comp_s
    line = mem.alloc(name,
  File "/home/ubuntu/exo/src/exo/platforms/neon.py", line 31, in alloc
    raise MemGenError(f'{srcinfo}: Cannot allocate variable '
NameError: name 'MemGenError' is not defined. Did you mean: 'MemoryError'?
"""