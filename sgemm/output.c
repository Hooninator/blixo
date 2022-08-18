
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

#include <arm_neon.h>

#include <stdio.h>
#include <stdlib.h>


#include <stdio.h>
#include <stdlib.h>


// neon_microkernel_edge(
//     K : size,
//     A : [f32][8,K]  @DRAM,
//     B : [f32][K,64]  @DRAM,
//     C : [f32][8,64]  @DRAM
// )
void neon_microkernel_edge( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[8][16];
for (int i = 0; i < 8; i++) {
  C_reg[i][0] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (0) * (C.strides[1])]);
  C_reg[i][1] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4) * (C.strides[1])]);
  C_reg[i][2] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (8) * (C.strides[1])]);
  C_reg[i][3] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (12) * (C.strides[1])]);
  C_reg[i][4] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (16) * (C.strides[1])]);
  C_reg[i][5] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (20) * (C.strides[1])]);
  C_reg[i][6] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (24) * (C.strides[1])]);
  C_reg[i][7] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (28) * (C.strides[1])]);
  C_reg[i][8] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (32) * (C.strides[1])]);
  C_reg[i][9] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (36) * (C.strides[1])]);
  C_reg[i][10] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (40) * (C.strides[1])]);
  C_reg[i][11] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (44) * (C.strides[1])]);
  C_reg[i][12] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (48) * (C.strides[1])]);
  C_reg[i][13] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (52) * (C.strides[1])]);
  C_reg[i][14] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (56) * (C.strides[1])]);
  C_reg[i][15] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (60) * (C.strides[1])]);
}
for (int k = 0; k < K; k++) {
  float32x4_t A_vec[8];
  for (int i = 0; i < 8; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[16];
  B_vec[0] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (0) * (B.strides[1])]);
  B_vec[1] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4) * (B.strides[1])]);
  B_vec[2] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (8) * (B.strides[1])]);
  B_vec[3] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (12) * (B.strides[1])]);
  B_vec[4] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (16) * (B.strides[1])]);
  B_vec[5] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (20) * (B.strides[1])]);
  B_vec[6] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (24) * (B.strides[1])]);
  B_vec[7] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (28) * (B.strides[1])]);
  B_vec[8] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (32) * (B.strides[1])]);
  B_vec[9] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (36) * (B.strides[1])]);
  B_vec[10] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (40) * (B.strides[1])]);
  B_vec[11] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (44) * (B.strides[1])]);
  B_vec[12] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (48) * (B.strides[1])]);
  B_vec[13] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (52) * (B.strides[1])]);
  B_vec[14] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (56) * (B.strides[1])]);
  B_vec[15] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (60) * (B.strides[1])]);
  for (int i = 0; i < 8; i++) {
    C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec[0]);
    C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec[1]);
    C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec[2]);
    C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec[3]);
    C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec[4]);
    C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec[5]);
    C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec[6]);
    C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec[7]);
    C_reg[i][8] = vmlaq_f32(C_reg[i][8], A_vec[i], B_vec[8]);
    C_reg[i][9] = vmlaq_f32(C_reg[i][9], A_vec[i], B_vec[9]);
    C_reg[i][10] = vmlaq_f32(C_reg[i][10], A_vec[i], B_vec[10]);
    C_reg[i][11] = vmlaq_f32(C_reg[i][11], A_vec[i], B_vec[11]);
    C_reg[i][12] = vmlaq_f32(C_reg[i][12], A_vec[i], B_vec[12]);
    C_reg[i][13] = vmlaq_f32(C_reg[i][13], A_vec[i], B_vec[13]);
    C_reg[i][14] = vmlaq_f32(C_reg[i][14], A_vec[i], B_vec[14]);
    C_reg[i][15] = vmlaq_f32(C_reg[i][15], A_vec[i], B_vec[15]);
  }
}
for (int i = 0; i < 8; i++) {
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (0) * (C.strides[1])], C_reg[i][0]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (4) * (C.strides[1])], C_reg[i][1]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (8) * (C.strides[1])], C_reg[i][2]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (12) * (C.strides[1])], C_reg[i][3]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (16) * (C.strides[1])], C_reg[i][4]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (20) * (C.strides[1])], C_reg[i][5]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (24) * (C.strides[1])], C_reg[i][6]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (28) * (C.strides[1])], C_reg[i][7]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (32) * (C.strides[1])], C_reg[i][8]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (36) * (C.strides[1])], C_reg[i][9]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (40) * (C.strides[1])], C_reg[i][10]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (44) * (C.strides[1])], C_reg[i][11]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (48) * (C.strides[1])], C_reg[i][12]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (52) * (C.strides[1])], C_reg[i][13]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (56) * (C.strides[1])], C_reg[i][14]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (60) * (C.strides[1])], C_reg[i][15]);
}
}

// GEBP_edge(
//     N : size,
//     K : size,
//     A : [f32][64,K]  @DRAM,
//     B : [f32][K,N]  @DRAM,
//     C : [f32][64,N]  @DRAM
// )
void GEBP_edge( c_code_str_Context *ctxt, int_fast32_t N, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(N >= 1);
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
for (int io = 0; io < 8; io++) {
  for (int jo = 0; jo < ((N) / (64)); jo++) {
    neon_microkernel_edge(ctxt,K,(struct exo_win_2f32){ (float*)&A.data[(8 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (64 * jo) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(8 * io) * (C.strides[0]) + (64 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
for (int io = 0; io < 8; io++) {
  if (N % 64 > 0) {
    for (int ii = 0; ii < 8; ii++) {
      for (int ji = 0; ji < N % 64; ji++) {
        for (int k = 0; k < K; k++) {
          C.data[(8 * io + ii) * (C.strides[0]) + (ji + ((N) / (64)) * 64) * (C.strides[1])] += A.data[(8 * io + ii) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + ((N) / (64)) * 64) * (B.strides[1])];
        }
      }
    }
  }
}
}

// GEPP_edge(
//     M : size,
//     N : size,
//     K : size,
//     A : [f32][M,K]  @DRAM,
//     B : [f32][K,N]  @DRAM,
//     C : [f32][M,N]  @DRAM
// )
void GEPP_edge( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(N >= 1);
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
for (int io = 0; io < ((M) / (64)); io++) {
  GEBP_edge(ctxt,N,K,(struct exo_win_2f32){ (float*)&A.data[(64 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(64 * io) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
}
if (M % 64 > 0) {
  for (int ii = 0; ii < M % 64; ii++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < K; k++) {
        C.data[(ii + ((M) / (64)) * 64) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(ii + ((M) / (64)) * 64) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])];
      }
    }
  }
}
}

// microkernel_edge_gebp_scheduled(
//     N : size,
//     A : [f32][8,256]  @DRAM,
//     B : [f32][256,N]  @DRAM,
//     C : [f32][8,N]  @DRAM
// )
void microkernel_edge_gebp_scheduled( c_code_str_Context *ctxt, int_fast32_t N, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(N >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
EXO_ASSUME(N < 64);
for (int i = 0; i < 8; i++) {
  for (int j = 0; j < N; j++) {
    for (int k = 0; k < 256; k++) {
      C.data[(i) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])];
    }
  }
}
}


/* relying on the following instruction...
neon_broadcast_4xf32(dst,src)
{dst_data} = vld1q_dup_f32(&{src_data});
*/


/* relying on the following instruction...
neon_vfmadd_4xf32_4xf32(dst,lhs,rhs)
{dst_data} = vmlaq_f32({dst_data}, {lhs_data}, {rhs_data});
*/


/* relying on the following instruction...
neon_vst_4xf32(dst,src)
vst1q_f32(&{dst_data}, {src_data});
*/


/* relying on the following instruction...
neon_vld_4xf32(dst,src)
{dst_data} = vld1q_f32(&{src_data});
*/

// neon_microkernel(
//     A : [f32][8,256]  @DRAM,
//     B : [f32][256,64]  @DRAM,
//     C : [f32][8,64]  @DRAM
// )
void neon_microkernel( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[8][16];
for (int i = 0; i < 8; i++) {
  C_reg[i][0] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (0) * (C.strides[1])]);
  C_reg[i][1] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4) * (C.strides[1])]);
  C_reg[i][2] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (8) * (C.strides[1])]);
  C_reg[i][3] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (12) * (C.strides[1])]);
  C_reg[i][4] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (16) * (C.strides[1])]);
  C_reg[i][5] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (20) * (C.strides[1])]);
  C_reg[i][6] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (24) * (C.strides[1])]);
  C_reg[i][7] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (28) * (C.strides[1])]);
  C_reg[i][8] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (32) * (C.strides[1])]);
  C_reg[i][9] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (36) * (C.strides[1])]);
  C_reg[i][10] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (40) * (C.strides[1])]);
  C_reg[i][11] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (44) * (C.strides[1])]);
  C_reg[i][12] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (48) * (C.strides[1])]);
  C_reg[i][13] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (52) * (C.strides[1])]);
  C_reg[i][14] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (56) * (C.strides[1])]);
  C_reg[i][15] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (60) * (C.strides[1])]);
}
for (int k = 0; k < 256; k++) {
  float32x4_t A_vec[8];
  for (int i = 0; i < 8; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[16];
  B_vec[0] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (0) * (B.strides[1])]);
  B_vec[1] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4) * (B.strides[1])]);
  B_vec[2] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (8) * (B.strides[1])]);
  B_vec[3] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (12) * (B.strides[1])]);
  B_vec[4] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (16) * (B.strides[1])]);
  B_vec[5] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (20) * (B.strides[1])]);
  B_vec[6] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (24) * (B.strides[1])]);
  B_vec[7] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (28) * (B.strides[1])]);
  B_vec[8] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (32) * (B.strides[1])]);
  B_vec[9] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (36) * (B.strides[1])]);
  B_vec[10] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (40) * (B.strides[1])]);
  B_vec[11] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (44) * (B.strides[1])]);
  B_vec[12] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (48) * (B.strides[1])]);
  B_vec[13] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (52) * (B.strides[1])]);
  B_vec[14] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (56) * (B.strides[1])]);
  B_vec[15] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (60) * (B.strides[1])]);
  for (int i = 0; i < 8; i++) {
    C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec[0]);
    C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec[1]);
    C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec[2]);
    C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec[3]);
    C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec[4]);
    C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec[5]);
    C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec[6]);
    C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec[7]);
    C_reg[i][8] = vmlaq_f32(C_reg[i][8], A_vec[i], B_vec[8]);
    C_reg[i][9] = vmlaq_f32(C_reg[i][9], A_vec[i], B_vec[9]);
    C_reg[i][10] = vmlaq_f32(C_reg[i][10], A_vec[i], B_vec[10]);
    C_reg[i][11] = vmlaq_f32(C_reg[i][11], A_vec[i], B_vec[11]);
    C_reg[i][12] = vmlaq_f32(C_reg[i][12], A_vec[i], B_vec[12]);
    C_reg[i][13] = vmlaq_f32(C_reg[i][13], A_vec[i], B_vec[13]);
    C_reg[i][14] = vmlaq_f32(C_reg[i][14], A_vec[i], B_vec[14]);
    C_reg[i][15] = vmlaq_f32(C_reg[i][15], A_vec[i], B_vec[15]);
  }
}
for (int i = 0; i < 8; i++) {
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (0) * (C.strides[1])], C_reg[i][0]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (4) * (C.strides[1])], C_reg[i][1]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (8) * (C.strides[1])], C_reg[i][2]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (12) * (C.strides[1])], C_reg[i][3]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (16) * (C.strides[1])], C_reg[i][4]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (20) * (C.strides[1])], C_reg[i][5]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (24) * (C.strides[1])], C_reg[i][6]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (28) * (C.strides[1])], C_reg[i][7]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (32) * (C.strides[1])], C_reg[i][8]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (36) * (C.strides[1])], C_reg[i][9]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (40) * (C.strides[1])], C_reg[i][10]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (44) * (C.strides[1])], C_reg[i][11]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (48) * (C.strides[1])], C_reg[i][12]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (52) * (C.strides[1])], C_reg[i][13]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (56) * (C.strides[1])], C_reg[i][14]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (60) * (C.strides[1])], C_reg[i][15]);
}
}

// GEBP(
//     N : size,
//     A : [f32][64,256]  @DRAM,
//     B : [f32][256,N]  @DRAM,
//     C : [f32][64,N]  @DRAM
// )
void GEBP( c_code_str_Context *ctxt, int_fast32_t N, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(64 >= 1);
EXO_ASSUME(N >= 1);
EXO_ASSUME(256 >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
for (int io = 0; io < _floor_div(64, 8); io++) {
  for (int jo = 0; jo < ((N) / (64)); jo++) {
    neon_microkernel(ctxt,(struct exo_win_2f32){ (float*)&A.data[(8 * io + 0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (64 * jo + 0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(8 * io + 0) * (C.strides[0]) + (64 * jo + 0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
for (int io = 0; io < _floor_div(64, 8); io++) {
  if (N % 64 > 0) {
    microkernel_edge_gebp_scheduled(ctxt,N % 64 + 0,(struct exo_win_2f32){ (float*)&A.data[(8 * io + 0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (64 * ((N) / (64)) + 0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(8 * io + 0) * (C.strides[0]) + (64 * ((N) / (64)) + 0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
if (64 % 8 > 0) {
  for (int jo = 0; jo < ((N) / (64)); jo++) {
    for (int ii = 0; ii < 64 % 8; ii++) {
      for (int ji = 0; ji < 64; ji++) {
        for (int k = 0; k < 256; k++) {
          C.data[(ii + _floor_div(64, 8) * 8) * (C.strides[0]) + (64 * jo + ji) * (C.strides[1])] += A.data[(ii + _floor_div(64, 8) * 8) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (64 * jo + ji) * (B.strides[1])];
        }
      }
    }
  }
}
if (64 % 8 > 0) {
  if (N % 64 > 0) {
    for (int ii = 0; ii < 64 % 8; ii++) {
      for (int ji = 0; ji < N % 64; ji++) {
        for (int k = 0; k < 256; k++) {
          C.data[(ii + _floor_div(64, 8) * 8) * (C.strides[0]) + (ji + ((N) / (64)) * 64) * (C.strides[1])] += A.data[(ii + _floor_div(64, 8) * 8) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + ((N) / (64)) * 64) * (B.strides[1])];
        }
      }
    }
  }
}
}

// GEPP(
//     M : size,
//     N : size,
//     A : [f32][M,256]  @DRAM,
//     B : [f32][256,N]  @DRAM,
//     C : [f32][M,N]  @DRAM
// )
void GEPP( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(N >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
for (int io = 0; io < ((M) / (64)); io++) {
  static float A_blk[64 * 256];
  for (int i0 = 0; i0 < 64; i0++) {
    for (int i1 = 0; i1 < 256; i1++) {
      A_blk[(i0) * (256) + (i1) * (1)] = A.data[(i0 + 64 * io) * (A.strides[0]) + (i1) * (A.strides[1])];
    }
  }
  GEBP(ctxt,N,(struct exo_win_2f32){ (float*)&A_blk[(0) * (256) + (0) * (1)], { 256, 1 } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(64 * io) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
}
if (M % 64 > 0) {
  for (int ii = 0; ii < M % 64; ii++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < 256; k++) {
        C.data[(ii + ((M) / (64)) * 64) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(ii + ((M) / (64)) * 64) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])];
      }
    }
  }
}
}

// sgemm_exo(
//     M : size,
//     N : size,
//     K : size,
//     A : f32[M,K]  @DRAM,
//     B : f32[K,N]  @DRAM,
//     C : f32[M,N]  @DRAM
// )
void sgemm_exo( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, int_fast32_t K, float* A, float* B, float* C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(N >= 1);
EXO_ASSUME(K >= 1);
EXO_ASSUME(1 == 1);
EXO_ASSUME(1 == 1);
EXO_ASSUME(1 == 1);
for (int ki = 0; ki < ((K) / (256)); ki++) {
  float *A_panel = malloc(M * 256 * sizeof(*A_panel));
  for (int i0 = 0; i0 < M - 0; i0++) {
    for (int i1 = 0; i1 < 256 * ki + 256 - 256 * ki; i1++) {
      A_panel[(i0) * (256) + (i1) * (1)] = A[(0 + i0) * (K) + (256 * ki + i1) * (1)];
    }
  }
  float *B_panel = malloc(256 * N * sizeof(*B_panel));
  for (int i0 = 0; i0 < 256 * ki + 256 - 256 * ki; i0++) {
    for (int i1 = 0; i1 < N - 0; i1++) {
      B_panel[(i0) * (N) + (i1) * (1)] = B[(256 * ki + i0) * (N) + (0 + i1) * (1)];
    }
  }
  GEPP(ctxt,M,N,(struct exo_win_2f32){ (float*)&A_panel[(0) * (256) + (0) * (1)], { 256, 1 } },(struct exo_win_2f32){ (float*)&B_panel[(0) * (N) + (0) * (1)], { N, 1 } },(struct exo_win_2f32){ (float*)&C[(0) * (N) + (0) * (1)], { N, 1 } });
  free(A_panel);
  free(B_panel);
}
if (K % 256 > 0) {
  GEPP_edge(ctxt,M,N,K % 256,(struct exo_win_2f32){ (float*)&A[(0) * (K) + (256 * ((K) / (256))) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B[(256 * ((K) / (256))) * (N) + (0) * (1)], { N, 1 } },(struct exo_win_2f32){ (float*)&C[(0) * (N) + (0) * (1)], { N, 1 } });
}
}
