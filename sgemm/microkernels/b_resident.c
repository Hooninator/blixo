

#include <stdint.h>
#include <stdbool.h>

// Compiler feature macros adapted from Hedley (public domain)
// https://github.com/nemequ/hedley

#if defined(__has_builtin)
#  define EXO_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
#  define EXO_HAS_BUILTIN(builtin) (0)
#endif

#if EXO_HAS_BUILTIN(__builtin_assume)
#  define EXO_ASSUME(expr) __builtin_assume(expr)
#elif EXO_HAS_BUILTIN(__builtin_unreachable)
#  define EXO_ASSUME(expr) \
      ((void)((expr) ? 1 : (__builtin_unreachable(), 1)))
#else
#  define EXO_ASSUME(expr) ((void)(expr))
#endif

struct exo_win_1f32{
    float *data;
    int_fast32_t strides[1];
};
struct exo_win_2f32{
    float *data;
    int_fast32_t strides[2];
};
typedef struct c_code_str_Context { 

} c_code_str_Context;


// sgemm_exo(
//     M : size,
//     N : size,
//     K : size,
//     A : f32[M,K]  @DRAM,
//     B : f32[K,N]  @DRAM,
//     C : f32[M,N]  @DRAM
// )
void sgemm_exo( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, int_fast32_t K, float* A, float* B, float* C );


static int _floor_div(int num, int quot) {
  int off = (num>=0)? 0 : quot-1;
  return (num-off)/quot;
}

static int8_t _clamp_32to8(int32_t x) {
  return (x < -128)? -128 : ((x > 127)? 127 : x);
}

#include <stdio.h>
#include <stdlib.h>


#include <arm_neon.h>

#include <stdio.h>
#include <stdlib.h>


void neon_microkernel( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[8][16];
for (int j = 0; j < 8; j++) {
  C_reg[j][0] = vld1q_f32(&C.data[(0) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][1] = vld1q_f32(&C.data[(4) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][2] = vld1q_f32(&C.data[(8) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][3] = vld1q_f32(&C.data[(12) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][4] = vld1q_f32(&C.data[(16) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][5] = vld1q_f32(&C.data[(20) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][6] = vld1q_f32(&C.data[(24) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][7] = vld1q_f32(&C.data[(28) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][8] = vld1q_f32(&C.data[(32) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][9] = vld1q_f32(&C.data[(36) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][10] = vld1q_f32(&C.data[(40) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][11] = vld1q_f32(&C.data[(44) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][12] = vld1q_f32(&C.data[(48) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][13] = vld1q_f32(&C.data[(52) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][14] = vld1q_f32(&C.data[(56) * (C.strides[0]) + (j) * (C.strides[1])]);
  C_reg[j][15] = vld1q_f32(&C.data[(60) * (C.strides[0]) + (j) * (C.strides[1])]);
}
for (int k = 0; k < 256; k++) {
  for (int j = 0; j < 8; j++) {
    float32x4_t B_vec;
    float32x4_t A_vec;
    A_vec = vld1q_f32(&A.data[(0) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][0] = vmlaq_f32(C_reg[j][0], A_vec, B_vec);
    float32x4_t A_vec_1;
    A_vec_1 = vld1q_f32(&A.data[(4) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][1] = vmlaq_f32(C_reg[j][1], A_vec_1, B_vec);
    float32x4_t A_vec_2;
    A_vec_2 = vld1q_f32(&A.data[(8) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][2] = vmlaq_f32(C_reg[j][2], A_vec_2, B_vec);
    float32x4_t A_vec_3;
    A_vec_3 = vld1q_f32(&A.data[(12) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][3] = vmlaq_f32(C_reg[j][3], A_vec_3, B_vec);
    float32x4_t A_vec_4;
    A_vec_4 = vld1q_f32(&A.data[(16) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][4] = vmlaq_f32(C_reg[j][4], A_vec_4, B_vec);
    float32x4_t A_vec_5;
    A_vec_5 = vld1q_f32(&A.data[(20) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][5] = vmlaq_f32(C_reg[j][5], A_vec_5, B_vec);
    float32x4_t A_vec_6;
    A_vec_6 = vld1q_f32(&A.data[(24) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][6] = vmlaq_f32(C_reg[j][6], A_vec_6, B_vec);
    float32x4_t A_vec_7;
    A_vec_7 = vld1q_f32(&A.data[(28) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][7] = vmlaq_f32(C_reg[j][7], A_vec_7, B_vec);
    float32x4_t A_vec_8;
    A_vec_8 = vld1q_f32(&A.data[(32) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][8] = vmlaq_f32(C_reg[j][8], A_vec_8, B_vec);
    float32x4_t A_vec_9;
    A_vec_9 = vld1q_f32(&A.data[(36) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][9] = vmlaq_f32(C_reg[j][9], A_vec_9, B_vec);
    float32x4_t A_vec_10;
    A_vec_10 = vld1q_f32(&A.data[(40) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][10] = vmlaq_f32(C_reg[j][10], A_vec_10, B_vec);
    float32x4_t A_vec_11;
    A_vec_11 = vld1q_f32(&A.data[(44) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][11] = vmlaq_f32(C_reg[j][11], A_vec_11, B_vec);
    float32x4_t A_vec_12;
    A_vec_12 = vld1q_f32(&A.data[(48) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][12] = vmlaq_f32(C_reg[j][12], A_vec_12, B_vec);
    float32x4_t A_vec_13;
    A_vec_13 = vld1q_f32(&A.data[(52) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][13] = vmlaq_f32(C_reg[j][13], A_vec_13, B_vec);
    float32x4_t A_vec_14;
    A_vec_14 = vld1q_f32(&A.data[(56) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][14] = vmlaq_f32(C_reg[j][14], A_vec_14, B_vec);
    float32x4_t A_vec_15;
    A_vec_15 = vld1q_f32(&A.data[(60) * (A.strides[0]) + (k) * (A.strides[1])]);
    B_vec = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
    C_reg[j][15] = vmlaq_f32(C_reg[j][15], A_vec_15, B_vec);
  }
}
for (int j = 0; j < 8; j++) {
  vst1q_f32(&C.data[(0) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][0]);
  vst1q_f32(&C.data[(4) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][1]);
  vst1q_f32(&C.data[(8) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][2]);
  vst1q_f32(&C.data[(12) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][3]);
  vst1q_f32(&C.data[(16) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][4]);
  vst1q_f32(&C.data[(20) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][5]);
  vst1q_f32(&C.data[(24) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][6]);
  vst1q_f32(&C.data[(28) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][7]);
  vst1q_f32(&C.data[(32) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][8]);
  vst1q_f32(&C.data[(36) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][9]);
  vst1q_f32(&C.data[(40) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][10]);
  vst1q_f32(&C.data[(44) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][11]);
  vst1q_f32(&C.data[(48) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][12]);
  vst1q_f32(&C.data[(52) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][13]);
  vst1q_f32(&C.data[(56) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][14]);
  vst1q_f32(&C.data[(60) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[j][15]);
}
}