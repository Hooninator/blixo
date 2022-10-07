
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
//     A : [f32][4,K]  @DRAM,
//     B : [f32][K,16]  @DRAM,
//     C : [f32][4,16]  @DRAM
// )
void neon_microkernel_edge( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[4][4];
for (int i = 0; i < 4; i++) {
  C_reg[i][0] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (0) * (C.strides[1])]);
  C_reg[i][1] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4) * (C.strides[1])]);
  C_reg[i][2] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (8) * (C.strides[1])]);
  C_reg[i][3] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (12) * (C.strides[1])]);
}
for (int k = 0; k < K; k++) {
  float32x4_t A_vec[4];
  for (int i = 0; i < 4; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[4];
  B_vec[0] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (0) * (B.strides[1])]);
  B_vec[1] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4) * (B.strides[1])]);
  B_vec[2] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (8) * (B.strides[1])]);
  B_vec[3] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (12) * (B.strides[1])]);
  for (int i = 0; i < 4; i++) {
    C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec[0]);
    C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec[1]);
    C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec[2]);
    C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec[3]);
  }
}
for (int i = 0; i < 4; i++) {
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (0) * (C.strides[1])], C_reg[i][0]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (4) * (C.strides[1])], C_reg[i][1]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (8) * (C.strides[1])], C_reg[i][2]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (12) * (C.strides[1])], C_reg[i][3]);
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
for (int io = 0; io < 16; io++) {
  for (int jo = 0; jo < ((N) / (16)); jo++) {
    neon_microkernel_edge(ctxt,K,(struct exo_win_2f32){ (float*)&A.data[(4 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (16 * jo) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(4 * io) * (C.strides[0]) + (16 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
for (int io = 0; io < 16; io++) {
  if (N % 16 > 0) {
    for (int ii = 0; ii < 4; ii++) {
      for (int ji = 0; ji < N % 16; ji++) {
        for (int k = 0; k < K; k++) {
          C.data[(4 * io + ii) * (C.strides[0]) + (ji + ((N) / (16)) * 16) * (C.strides[1])] += A.data[(4 * io + ii) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + ((N) / (16)) * 16) * (B.strides[1])];
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
//     A : [f32][4,64]  @DRAM,
//     B : [f32][64,16]  @DRAM,
//     C : [f32][4,16]  @DRAM
// )
void neon_microkernel( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[4][4];
for (int i = 0; i < 4; i++) {
  for (int jo = 0; jo < 4; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[4];
  for (int i = 0; i < 4; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[4];
  for (int jo = 0; jo < 4; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 4; i++) {
    for (int jo = 0; jo < 4; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 4; i++) {
  for (int jo = 0; jo < 4; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// GEBP(
//     N : size,
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,N]  @DRAM,
//     C : [f32][64,N]  @DRAM
// )
void GEBP( c_code_str_Context *ctxt, int_fast32_t N, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(N >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
for (int jo = 0; jo < ((N) / (16)); jo++) {
  float *B_strip = malloc(64 * 16 * sizeof(*B_strip));
  for (int i0 = 0; i0 < 64; i0++) {
    for (int i1 = 0; i1 < 16; i1++) {
      B_strip[(i0) * (16) + (i1) * (1)] = B.data[(i0) * (B.strides[0]) + (i1 + 16 * jo) * (B.strides[1])];
    }
  }
  for (int io = 0; io < 16; io++) {
    neon_microkernel(ctxt,(struct exo_win_2f32){ (float*)&A.data[(4 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B_strip[(0) * (16) + (0) * (1)], { 16, 1 } },(struct exo_win_2f32){ (float*)&C.data[(4 * io) * (C.strides[0]) + (16 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
  free(B_strip);
}
for (int io = 0; io < 16; io++) {
  for (int ii = 0; ii < 4; ii++) {
    if (N % 16 > 0) {
      for (int ji = 0; ji < N % 16; ji++) {
        for (int k = 0; k < 64; k++) {
          C.data[(4 * io + ii) * (C.strides[0]) + (ji + ((N) / (16)) * 16) * (C.strides[1])] += A.data[(4 * io + ii) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + ((N) / (16)) * 16) * (B.strides[1])];
        }
      }
    }
  }
}
}

// GEPP(
//     M : size,
//     N : size,
//     A : [f32][M,64]  @DRAM,
//     B : [f32][64,N]  @DRAM,
//     C : [f32][M,N]  @DRAM
// )
void GEPP( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(N >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
for (int io = 0; io < ((M) / (64)); io++) {
  static float A_blk[64 * 64];
  for (int i0 = 0; i0 < 64; i0++) {
    for (int i1 = 0; i1 < 64; i1++) {
      A_blk[(i0) * (64) + (i1) * (1)] = A.data[(i0 + 64 * io) * (A.strides[0]) + (i1) * (A.strides[1])];
    }
  }
  GEBP(ctxt,N,(struct exo_win_2f32){ (float*)&A_blk[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(64 * io) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
}
if (M % 64 > 0) {
  for (int ii = 0; ii < M % 64; ii++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < 64; k++) {
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
for (int ki = 0; ki < ((K) / (64)); ki++) {
  float *A_panel = malloc(M * 64 * sizeof(*A_panel));
  for (int i0 = 0; i0 < M - 0; i0++) {
    for (int i1 = 0; i1 < 64 * ki + 64 - 64 * ki; i1++) {
      A_panel[(i0) * (64) + (i1) * (1)] = A[(0 + i0) * (K) + (64 * ki + i1) * (1)];
    }
  }
  float *B_panel = malloc(64 * N * sizeof(*B_panel));
  for (int i0 = 0; i0 < 64 * ki + 64 - 64 * ki; i0++) {
    for (int i1 = 0; i1 < N - 0; i1++) {
      B_panel[(i0) * (N) + (i1) * (1)] = B[(64 * ki + i0) * (N) + (0 + i1) * (1)];
    }
  }
  GEPP(ctxt,M,N,(struct exo_win_2f32){ (float*)&A_panel[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&B_panel[(0) * (N) + (0) * (1)], { N, 1 } },(struct exo_win_2f32){ (float*)&C[(0) * (N) + (0) * (1)], { N, 1 } });
  free(A_panel);
  free(B_panel);
}
if (K % 64 > 0) {
  GEPP_edge(ctxt,M,N,K % 64,(struct exo_win_2f32){ (float*)&A[(0) * (K) + (64 * ((K) / (64))) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B[(64 * ((K) / (64))) * (N) + (0) * (1)], { N, 1 } },(struct exo_win_2f32){ (float*)&C[(0) * (N) + (0) * (1)], { N, 1 } });
}
}
