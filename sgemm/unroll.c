
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

struct exo_win_2f32{
    float *data;
    int_fast32_t strides[2];
};
struct exo_win_1f32{
    float *data;
    int_fast32_t strides[1];
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


#include <stdio.h>
#include <stdlib.h>


#include <arm_neon.h>

// neon_microkernel_edge(
//     K : size,
//     A : [f32][64,K]  @DRAM,
//     B : [f32][K,32]  @DRAM,
//     C : [f32][64,32]  @DRAM
// )
void neon_microkernel_edge( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][8];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 8; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[8];
  for (int jo = 0; jo < 8; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 8; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 8; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
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
for (int io = 0; io < 1; io++) {
  for (int jo = 0; jo < ((N) / (32)); jo++) {
    neon_microkernel_edge(ctxt,K,(struct exo_win_2f32){ (float*)&A.data[(64 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (32 * jo) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(64 * io) * (C.strides[0]) + (32 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
for (int io = 0; io < 1; io++) {
  if (N % 32 > 0) {
    for (int ii = 0; ii < 64; ii++) {
      for (int ji = 0; ji < N % 32; ji++) {
        for (int k = 0; k < K; k++) {
          C.data[(64 * io + ii) * (C.strides[0]) + (ji + ((N) / (32)) * 32) * (C.strides[1])] += A.data[(64 * io + ii) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + ((N) / (32)) * 32) * (B.strides[1])];
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
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,N]  @DRAM,
//     C : [f32][64,N]  @DRAM
// )
void microkernel_edge_gebp_scheduled( c_code_str_Context *ctxt, int_fast32_t N, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(N >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
EXO_ASSUME(N < 32);
for (int i = 0; i < 64; i++) {
  for (int j = 0; j < N; j++) {
    for (int k = 0; k < 64; k++) {
      C.data[(i) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])];
    }
  }
}
}


/* relying on the following instruction...
neon_vst_4xf32(dst,src)
vst1q_f32(&{dst_data}, {src_data});
*/


/* relying on the following instruction...
neon_vfmadd_4xf32_4xf32(dst,lhs,rhs)
{dst_data} = vmlaq_f32({dst_data}, {lhs_data}, {rhs_data});
*/


/* relying on the following instruction...
neon_broadcast_4xf32(dst,src)
{dst_data} = vld1q_dup_f32(&{src_data});
*/


/* relying on the following instruction...
neon_vld_4xf32(dst,src)
{dst_data} = vld1q_f32(&{src_data});
*/

// neon_microkernel(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,32]  @DRAM,
//     C : [f32][64,32]  @DRAM
// )
void neon_microkernel( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][8];
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (0) * (C.strides[1])]);
  C_reg[i][1] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4) * (C.strides[1])]);
  C_reg[i][2] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (8) * (C.strides[1])]);
  C_reg[i][3] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (12) * (C.strides[1])]);
  C_reg[i][4] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (16) * (C.strides[1])]);
  C_reg[i][5] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (20) * (C.strides[1])]);
  C_reg[i][6] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (24) * (C.strides[1])]);
  C_reg[i][7] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (28) * (C.strides[1])]);
}
float32x4_t A_vec[64];
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (0) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (1) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (2) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (3) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (4) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (5) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (6) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (7) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (8) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (9) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (10) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (11) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (12) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (13) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (14) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (15) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (16) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (17) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (18) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (19) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (20) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (21) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (22) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (23) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (24) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (25) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (26) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (27) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (28) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (29) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (30) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (31) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (32) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (33) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (34) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (35) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (36) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (37) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (38) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (39) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (40) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (41) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (42) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (43) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (44) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (45) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (46) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (47) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (48) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (49) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (50) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (51) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (52) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (53) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (54) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (55) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (56) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (57) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (58) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (59) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (60) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (61) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (62) * (A.strides[1])]);
}
for (int i = 0; i < 64; i++) {
  A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (63) * (A.strides[1])]);
}
float32x4_t B_vec[8];
B_vec[0] = vld1q_f32(&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec[1] = vld1q_f32(&B.data[(0) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec[2] = vld1q_f32(&B.data[(0) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec[3] = vld1q_f32(&B.data[(0) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec[4] = vld1q_f32(&B.data[(0) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec[5] = vld1q_f32(&B.data[(0) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec[6] = vld1q_f32(&B.data[(0) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec[7] = vld1q_f32(&B.data[(0) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec[7]);
}
float32x4_t B_vec_1[8];
B_vec_1[0] = vld1q_f32(&B.data[(1) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_1[1] = vld1q_f32(&B.data[(1) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_1[2] = vld1q_f32(&B.data[(1) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_1[3] = vld1q_f32(&B.data[(1) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_1[4] = vld1q_f32(&B.data[(1) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_1[5] = vld1q_f32(&B.data[(1) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_1[6] = vld1q_f32(&B.data[(1) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_1[7] = vld1q_f32(&B.data[(1) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_1[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_1[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_1[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_1[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_1[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_1[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_1[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_1[7]);
}
float32x4_t B_vec_2[8];
B_vec_2[0] = vld1q_f32(&B.data[(2) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_2[1] = vld1q_f32(&B.data[(2) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_2[2] = vld1q_f32(&B.data[(2) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_2[3] = vld1q_f32(&B.data[(2) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_2[4] = vld1q_f32(&B.data[(2) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_2[5] = vld1q_f32(&B.data[(2) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_2[6] = vld1q_f32(&B.data[(2) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_2[7] = vld1q_f32(&B.data[(2) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_2[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_2[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_2[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_2[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_2[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_2[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_2[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_2[7]);
}
float32x4_t B_vec_3[8];
B_vec_3[0] = vld1q_f32(&B.data[(3) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_3[1] = vld1q_f32(&B.data[(3) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_3[2] = vld1q_f32(&B.data[(3) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_3[3] = vld1q_f32(&B.data[(3) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_3[4] = vld1q_f32(&B.data[(3) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_3[5] = vld1q_f32(&B.data[(3) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_3[6] = vld1q_f32(&B.data[(3) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_3[7] = vld1q_f32(&B.data[(3) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_3[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_3[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_3[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_3[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_3[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_3[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_3[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_3[7]);
}
float32x4_t B_vec_4[8];
B_vec_4[0] = vld1q_f32(&B.data[(4) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_4[1] = vld1q_f32(&B.data[(4) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_4[2] = vld1q_f32(&B.data[(4) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_4[3] = vld1q_f32(&B.data[(4) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_4[4] = vld1q_f32(&B.data[(4) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_4[5] = vld1q_f32(&B.data[(4) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_4[6] = vld1q_f32(&B.data[(4) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_4[7] = vld1q_f32(&B.data[(4) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_4[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_4[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_4[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_4[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_4[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_4[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_4[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_4[7]);
}
float32x4_t B_vec_5[8];
B_vec_5[0] = vld1q_f32(&B.data[(5) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_5[1] = vld1q_f32(&B.data[(5) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_5[2] = vld1q_f32(&B.data[(5) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_5[3] = vld1q_f32(&B.data[(5) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_5[4] = vld1q_f32(&B.data[(5) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_5[5] = vld1q_f32(&B.data[(5) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_5[6] = vld1q_f32(&B.data[(5) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_5[7] = vld1q_f32(&B.data[(5) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_5[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_5[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_5[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_5[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_5[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_5[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_5[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_5[7]);
}
float32x4_t B_vec_6[8];
B_vec_6[0] = vld1q_f32(&B.data[(6) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_6[1] = vld1q_f32(&B.data[(6) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_6[2] = vld1q_f32(&B.data[(6) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_6[3] = vld1q_f32(&B.data[(6) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_6[4] = vld1q_f32(&B.data[(6) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_6[5] = vld1q_f32(&B.data[(6) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_6[6] = vld1q_f32(&B.data[(6) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_6[7] = vld1q_f32(&B.data[(6) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_6[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_6[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_6[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_6[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_6[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_6[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_6[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_6[7]);
}
float32x4_t B_vec_7[8];
B_vec_7[0] = vld1q_f32(&B.data[(7) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_7[1] = vld1q_f32(&B.data[(7) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_7[2] = vld1q_f32(&B.data[(7) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_7[3] = vld1q_f32(&B.data[(7) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_7[4] = vld1q_f32(&B.data[(7) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_7[5] = vld1q_f32(&B.data[(7) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_7[6] = vld1q_f32(&B.data[(7) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_7[7] = vld1q_f32(&B.data[(7) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_7[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_7[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_7[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_7[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_7[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_7[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_7[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_7[7]);
}
float32x4_t B_vec_8[8];
B_vec_8[0] = vld1q_f32(&B.data[(8) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_8[1] = vld1q_f32(&B.data[(8) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_8[2] = vld1q_f32(&B.data[(8) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_8[3] = vld1q_f32(&B.data[(8) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_8[4] = vld1q_f32(&B.data[(8) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_8[5] = vld1q_f32(&B.data[(8) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_8[6] = vld1q_f32(&B.data[(8) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_8[7] = vld1q_f32(&B.data[(8) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_8[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_8[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_8[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_8[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_8[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_8[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_8[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_8[7]);
}
float32x4_t B_vec_9[8];
B_vec_9[0] = vld1q_f32(&B.data[(9) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_9[1] = vld1q_f32(&B.data[(9) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_9[2] = vld1q_f32(&B.data[(9) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_9[3] = vld1q_f32(&B.data[(9) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_9[4] = vld1q_f32(&B.data[(9) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_9[5] = vld1q_f32(&B.data[(9) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_9[6] = vld1q_f32(&B.data[(9) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_9[7] = vld1q_f32(&B.data[(9) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_9[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_9[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_9[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_9[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_9[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_9[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_9[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_9[7]);
}
float32x4_t B_vec_10[8];
B_vec_10[0] = vld1q_f32(&B.data[(10) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_10[1] = vld1q_f32(&B.data[(10) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_10[2] = vld1q_f32(&B.data[(10) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_10[3] = vld1q_f32(&B.data[(10) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_10[4] = vld1q_f32(&B.data[(10) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_10[5] = vld1q_f32(&B.data[(10) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_10[6] = vld1q_f32(&B.data[(10) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_10[7] = vld1q_f32(&B.data[(10) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_10[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_10[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_10[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_10[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_10[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_10[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_10[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_10[7]);
}
float32x4_t B_vec_11[8];
B_vec_11[0] = vld1q_f32(&B.data[(11) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_11[1] = vld1q_f32(&B.data[(11) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_11[2] = vld1q_f32(&B.data[(11) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_11[3] = vld1q_f32(&B.data[(11) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_11[4] = vld1q_f32(&B.data[(11) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_11[5] = vld1q_f32(&B.data[(11) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_11[6] = vld1q_f32(&B.data[(11) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_11[7] = vld1q_f32(&B.data[(11) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_11[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_11[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_11[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_11[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_11[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_11[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_11[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_11[7]);
}
float32x4_t B_vec_12[8];
B_vec_12[0] = vld1q_f32(&B.data[(12) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_12[1] = vld1q_f32(&B.data[(12) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_12[2] = vld1q_f32(&B.data[(12) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_12[3] = vld1q_f32(&B.data[(12) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_12[4] = vld1q_f32(&B.data[(12) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_12[5] = vld1q_f32(&B.data[(12) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_12[6] = vld1q_f32(&B.data[(12) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_12[7] = vld1q_f32(&B.data[(12) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_12[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_12[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_12[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_12[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_12[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_12[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_12[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_12[7]);
}
float32x4_t B_vec_13[8];
B_vec_13[0] = vld1q_f32(&B.data[(13) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_13[1] = vld1q_f32(&B.data[(13) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_13[2] = vld1q_f32(&B.data[(13) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_13[3] = vld1q_f32(&B.data[(13) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_13[4] = vld1q_f32(&B.data[(13) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_13[5] = vld1q_f32(&B.data[(13) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_13[6] = vld1q_f32(&B.data[(13) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_13[7] = vld1q_f32(&B.data[(13) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_13[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_13[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_13[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_13[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_13[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_13[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_13[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_13[7]);
}
float32x4_t B_vec_14[8];
B_vec_14[0] = vld1q_f32(&B.data[(14) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_14[1] = vld1q_f32(&B.data[(14) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_14[2] = vld1q_f32(&B.data[(14) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_14[3] = vld1q_f32(&B.data[(14) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_14[4] = vld1q_f32(&B.data[(14) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_14[5] = vld1q_f32(&B.data[(14) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_14[6] = vld1q_f32(&B.data[(14) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_14[7] = vld1q_f32(&B.data[(14) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_14[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_14[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_14[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_14[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_14[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_14[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_14[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_14[7]);
}
float32x4_t B_vec_15[8];
B_vec_15[0] = vld1q_f32(&B.data[(15) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_15[1] = vld1q_f32(&B.data[(15) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_15[2] = vld1q_f32(&B.data[(15) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_15[3] = vld1q_f32(&B.data[(15) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_15[4] = vld1q_f32(&B.data[(15) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_15[5] = vld1q_f32(&B.data[(15) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_15[6] = vld1q_f32(&B.data[(15) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_15[7] = vld1q_f32(&B.data[(15) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_15[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_15[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_15[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_15[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_15[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_15[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_15[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_15[7]);
}
float32x4_t B_vec_16[8];
B_vec_16[0] = vld1q_f32(&B.data[(16) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_16[1] = vld1q_f32(&B.data[(16) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_16[2] = vld1q_f32(&B.data[(16) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_16[3] = vld1q_f32(&B.data[(16) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_16[4] = vld1q_f32(&B.data[(16) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_16[5] = vld1q_f32(&B.data[(16) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_16[6] = vld1q_f32(&B.data[(16) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_16[7] = vld1q_f32(&B.data[(16) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_16[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_16[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_16[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_16[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_16[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_16[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_16[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_16[7]);
}
float32x4_t B_vec_17[8];
B_vec_17[0] = vld1q_f32(&B.data[(17) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_17[1] = vld1q_f32(&B.data[(17) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_17[2] = vld1q_f32(&B.data[(17) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_17[3] = vld1q_f32(&B.data[(17) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_17[4] = vld1q_f32(&B.data[(17) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_17[5] = vld1q_f32(&B.data[(17) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_17[6] = vld1q_f32(&B.data[(17) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_17[7] = vld1q_f32(&B.data[(17) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_17[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_17[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_17[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_17[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_17[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_17[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_17[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_17[7]);
}
float32x4_t B_vec_18[8];
B_vec_18[0] = vld1q_f32(&B.data[(18) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_18[1] = vld1q_f32(&B.data[(18) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_18[2] = vld1q_f32(&B.data[(18) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_18[3] = vld1q_f32(&B.data[(18) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_18[4] = vld1q_f32(&B.data[(18) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_18[5] = vld1q_f32(&B.data[(18) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_18[6] = vld1q_f32(&B.data[(18) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_18[7] = vld1q_f32(&B.data[(18) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_18[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_18[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_18[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_18[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_18[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_18[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_18[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_18[7]);
}
float32x4_t B_vec_19[8];
B_vec_19[0] = vld1q_f32(&B.data[(19) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_19[1] = vld1q_f32(&B.data[(19) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_19[2] = vld1q_f32(&B.data[(19) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_19[3] = vld1q_f32(&B.data[(19) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_19[4] = vld1q_f32(&B.data[(19) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_19[5] = vld1q_f32(&B.data[(19) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_19[6] = vld1q_f32(&B.data[(19) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_19[7] = vld1q_f32(&B.data[(19) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_19[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_19[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_19[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_19[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_19[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_19[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_19[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_19[7]);
}
float32x4_t B_vec_20[8];
B_vec_20[0] = vld1q_f32(&B.data[(20) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_20[1] = vld1q_f32(&B.data[(20) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_20[2] = vld1q_f32(&B.data[(20) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_20[3] = vld1q_f32(&B.data[(20) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_20[4] = vld1q_f32(&B.data[(20) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_20[5] = vld1q_f32(&B.data[(20) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_20[6] = vld1q_f32(&B.data[(20) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_20[7] = vld1q_f32(&B.data[(20) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_20[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_20[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_20[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_20[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_20[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_20[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_20[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_20[7]);
}
float32x4_t B_vec_21[8];
B_vec_21[0] = vld1q_f32(&B.data[(21) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_21[1] = vld1q_f32(&B.data[(21) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_21[2] = vld1q_f32(&B.data[(21) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_21[3] = vld1q_f32(&B.data[(21) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_21[4] = vld1q_f32(&B.data[(21) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_21[5] = vld1q_f32(&B.data[(21) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_21[6] = vld1q_f32(&B.data[(21) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_21[7] = vld1q_f32(&B.data[(21) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_21[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_21[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_21[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_21[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_21[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_21[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_21[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_21[7]);
}
float32x4_t B_vec_22[8];
B_vec_22[0] = vld1q_f32(&B.data[(22) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_22[1] = vld1q_f32(&B.data[(22) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_22[2] = vld1q_f32(&B.data[(22) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_22[3] = vld1q_f32(&B.data[(22) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_22[4] = vld1q_f32(&B.data[(22) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_22[5] = vld1q_f32(&B.data[(22) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_22[6] = vld1q_f32(&B.data[(22) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_22[7] = vld1q_f32(&B.data[(22) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_22[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_22[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_22[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_22[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_22[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_22[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_22[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_22[7]);
}
float32x4_t B_vec_23[8];
B_vec_23[0] = vld1q_f32(&B.data[(23) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_23[1] = vld1q_f32(&B.data[(23) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_23[2] = vld1q_f32(&B.data[(23) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_23[3] = vld1q_f32(&B.data[(23) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_23[4] = vld1q_f32(&B.data[(23) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_23[5] = vld1q_f32(&B.data[(23) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_23[6] = vld1q_f32(&B.data[(23) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_23[7] = vld1q_f32(&B.data[(23) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_23[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_23[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_23[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_23[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_23[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_23[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_23[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_23[7]);
}
float32x4_t B_vec_24[8];
B_vec_24[0] = vld1q_f32(&B.data[(24) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_24[1] = vld1q_f32(&B.data[(24) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_24[2] = vld1q_f32(&B.data[(24) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_24[3] = vld1q_f32(&B.data[(24) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_24[4] = vld1q_f32(&B.data[(24) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_24[5] = vld1q_f32(&B.data[(24) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_24[6] = vld1q_f32(&B.data[(24) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_24[7] = vld1q_f32(&B.data[(24) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_24[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_24[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_24[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_24[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_24[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_24[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_24[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_24[7]);
}
float32x4_t B_vec_25[8];
B_vec_25[0] = vld1q_f32(&B.data[(25) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_25[1] = vld1q_f32(&B.data[(25) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_25[2] = vld1q_f32(&B.data[(25) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_25[3] = vld1q_f32(&B.data[(25) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_25[4] = vld1q_f32(&B.data[(25) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_25[5] = vld1q_f32(&B.data[(25) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_25[6] = vld1q_f32(&B.data[(25) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_25[7] = vld1q_f32(&B.data[(25) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_25[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_25[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_25[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_25[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_25[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_25[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_25[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_25[7]);
}
float32x4_t B_vec_26[8];
B_vec_26[0] = vld1q_f32(&B.data[(26) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_26[1] = vld1q_f32(&B.data[(26) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_26[2] = vld1q_f32(&B.data[(26) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_26[3] = vld1q_f32(&B.data[(26) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_26[4] = vld1q_f32(&B.data[(26) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_26[5] = vld1q_f32(&B.data[(26) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_26[6] = vld1q_f32(&B.data[(26) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_26[7] = vld1q_f32(&B.data[(26) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_26[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_26[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_26[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_26[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_26[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_26[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_26[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_26[7]);
}
float32x4_t B_vec_27[8];
B_vec_27[0] = vld1q_f32(&B.data[(27) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_27[1] = vld1q_f32(&B.data[(27) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_27[2] = vld1q_f32(&B.data[(27) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_27[3] = vld1q_f32(&B.data[(27) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_27[4] = vld1q_f32(&B.data[(27) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_27[5] = vld1q_f32(&B.data[(27) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_27[6] = vld1q_f32(&B.data[(27) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_27[7] = vld1q_f32(&B.data[(27) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_27[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_27[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_27[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_27[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_27[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_27[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_27[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_27[7]);
}
float32x4_t B_vec_28[8];
B_vec_28[0] = vld1q_f32(&B.data[(28) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_28[1] = vld1q_f32(&B.data[(28) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_28[2] = vld1q_f32(&B.data[(28) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_28[3] = vld1q_f32(&B.data[(28) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_28[4] = vld1q_f32(&B.data[(28) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_28[5] = vld1q_f32(&B.data[(28) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_28[6] = vld1q_f32(&B.data[(28) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_28[7] = vld1q_f32(&B.data[(28) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_28[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_28[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_28[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_28[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_28[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_28[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_28[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_28[7]);
}
float32x4_t B_vec_29[8];
B_vec_29[0] = vld1q_f32(&B.data[(29) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_29[1] = vld1q_f32(&B.data[(29) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_29[2] = vld1q_f32(&B.data[(29) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_29[3] = vld1q_f32(&B.data[(29) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_29[4] = vld1q_f32(&B.data[(29) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_29[5] = vld1q_f32(&B.data[(29) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_29[6] = vld1q_f32(&B.data[(29) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_29[7] = vld1q_f32(&B.data[(29) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_29[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_29[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_29[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_29[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_29[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_29[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_29[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_29[7]);
}
float32x4_t B_vec_30[8];
B_vec_30[0] = vld1q_f32(&B.data[(30) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_30[1] = vld1q_f32(&B.data[(30) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_30[2] = vld1q_f32(&B.data[(30) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_30[3] = vld1q_f32(&B.data[(30) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_30[4] = vld1q_f32(&B.data[(30) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_30[5] = vld1q_f32(&B.data[(30) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_30[6] = vld1q_f32(&B.data[(30) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_30[7] = vld1q_f32(&B.data[(30) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_30[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_30[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_30[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_30[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_30[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_30[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_30[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_30[7]);
}
float32x4_t B_vec_31[8];
B_vec_31[0] = vld1q_f32(&B.data[(31) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_31[1] = vld1q_f32(&B.data[(31) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_31[2] = vld1q_f32(&B.data[(31) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_31[3] = vld1q_f32(&B.data[(31) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_31[4] = vld1q_f32(&B.data[(31) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_31[5] = vld1q_f32(&B.data[(31) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_31[6] = vld1q_f32(&B.data[(31) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_31[7] = vld1q_f32(&B.data[(31) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_31[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_31[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_31[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_31[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_31[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_31[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_31[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_31[7]);
}
float32x4_t B_vec_32[8];
B_vec_32[0] = vld1q_f32(&B.data[(32) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_32[1] = vld1q_f32(&B.data[(32) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_32[2] = vld1q_f32(&B.data[(32) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_32[3] = vld1q_f32(&B.data[(32) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_32[4] = vld1q_f32(&B.data[(32) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_32[5] = vld1q_f32(&B.data[(32) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_32[6] = vld1q_f32(&B.data[(32) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_32[7] = vld1q_f32(&B.data[(32) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_32[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_32[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_32[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_32[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_32[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_32[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_32[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_32[7]);
}
float32x4_t B_vec_33[8];
B_vec_33[0] = vld1q_f32(&B.data[(33) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_33[1] = vld1q_f32(&B.data[(33) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_33[2] = vld1q_f32(&B.data[(33) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_33[3] = vld1q_f32(&B.data[(33) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_33[4] = vld1q_f32(&B.data[(33) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_33[5] = vld1q_f32(&B.data[(33) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_33[6] = vld1q_f32(&B.data[(33) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_33[7] = vld1q_f32(&B.data[(33) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_33[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_33[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_33[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_33[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_33[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_33[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_33[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_33[7]);
}
float32x4_t B_vec_34[8];
B_vec_34[0] = vld1q_f32(&B.data[(34) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_34[1] = vld1q_f32(&B.data[(34) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_34[2] = vld1q_f32(&B.data[(34) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_34[3] = vld1q_f32(&B.data[(34) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_34[4] = vld1q_f32(&B.data[(34) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_34[5] = vld1q_f32(&B.data[(34) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_34[6] = vld1q_f32(&B.data[(34) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_34[7] = vld1q_f32(&B.data[(34) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_34[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_34[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_34[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_34[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_34[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_34[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_34[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_34[7]);
}
float32x4_t B_vec_35[8];
B_vec_35[0] = vld1q_f32(&B.data[(35) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_35[1] = vld1q_f32(&B.data[(35) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_35[2] = vld1q_f32(&B.data[(35) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_35[3] = vld1q_f32(&B.data[(35) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_35[4] = vld1q_f32(&B.data[(35) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_35[5] = vld1q_f32(&B.data[(35) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_35[6] = vld1q_f32(&B.data[(35) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_35[7] = vld1q_f32(&B.data[(35) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_35[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_35[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_35[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_35[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_35[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_35[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_35[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_35[7]);
}
float32x4_t B_vec_36[8];
B_vec_36[0] = vld1q_f32(&B.data[(36) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_36[1] = vld1q_f32(&B.data[(36) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_36[2] = vld1q_f32(&B.data[(36) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_36[3] = vld1q_f32(&B.data[(36) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_36[4] = vld1q_f32(&B.data[(36) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_36[5] = vld1q_f32(&B.data[(36) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_36[6] = vld1q_f32(&B.data[(36) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_36[7] = vld1q_f32(&B.data[(36) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_36[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_36[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_36[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_36[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_36[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_36[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_36[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_36[7]);
}
float32x4_t B_vec_37[8];
B_vec_37[0] = vld1q_f32(&B.data[(37) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_37[1] = vld1q_f32(&B.data[(37) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_37[2] = vld1q_f32(&B.data[(37) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_37[3] = vld1q_f32(&B.data[(37) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_37[4] = vld1q_f32(&B.data[(37) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_37[5] = vld1q_f32(&B.data[(37) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_37[6] = vld1q_f32(&B.data[(37) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_37[7] = vld1q_f32(&B.data[(37) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_37[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_37[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_37[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_37[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_37[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_37[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_37[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_37[7]);
}
float32x4_t B_vec_38[8];
B_vec_38[0] = vld1q_f32(&B.data[(38) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_38[1] = vld1q_f32(&B.data[(38) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_38[2] = vld1q_f32(&B.data[(38) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_38[3] = vld1q_f32(&B.data[(38) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_38[4] = vld1q_f32(&B.data[(38) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_38[5] = vld1q_f32(&B.data[(38) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_38[6] = vld1q_f32(&B.data[(38) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_38[7] = vld1q_f32(&B.data[(38) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_38[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_38[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_38[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_38[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_38[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_38[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_38[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_38[7]);
}
float32x4_t B_vec_39[8];
B_vec_39[0] = vld1q_f32(&B.data[(39) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_39[1] = vld1q_f32(&B.data[(39) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_39[2] = vld1q_f32(&B.data[(39) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_39[3] = vld1q_f32(&B.data[(39) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_39[4] = vld1q_f32(&B.data[(39) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_39[5] = vld1q_f32(&B.data[(39) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_39[6] = vld1q_f32(&B.data[(39) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_39[7] = vld1q_f32(&B.data[(39) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_39[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_39[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_39[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_39[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_39[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_39[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_39[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_39[7]);
}
float32x4_t B_vec_40[8];
B_vec_40[0] = vld1q_f32(&B.data[(40) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_40[1] = vld1q_f32(&B.data[(40) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_40[2] = vld1q_f32(&B.data[(40) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_40[3] = vld1q_f32(&B.data[(40) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_40[4] = vld1q_f32(&B.data[(40) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_40[5] = vld1q_f32(&B.data[(40) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_40[6] = vld1q_f32(&B.data[(40) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_40[7] = vld1q_f32(&B.data[(40) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_40[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_40[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_40[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_40[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_40[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_40[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_40[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_40[7]);
}
float32x4_t B_vec_41[8];
B_vec_41[0] = vld1q_f32(&B.data[(41) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_41[1] = vld1q_f32(&B.data[(41) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_41[2] = vld1q_f32(&B.data[(41) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_41[3] = vld1q_f32(&B.data[(41) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_41[4] = vld1q_f32(&B.data[(41) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_41[5] = vld1q_f32(&B.data[(41) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_41[6] = vld1q_f32(&B.data[(41) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_41[7] = vld1q_f32(&B.data[(41) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_41[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_41[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_41[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_41[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_41[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_41[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_41[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_41[7]);
}
float32x4_t B_vec_42[8];
B_vec_42[0] = vld1q_f32(&B.data[(42) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_42[1] = vld1q_f32(&B.data[(42) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_42[2] = vld1q_f32(&B.data[(42) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_42[3] = vld1q_f32(&B.data[(42) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_42[4] = vld1q_f32(&B.data[(42) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_42[5] = vld1q_f32(&B.data[(42) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_42[6] = vld1q_f32(&B.data[(42) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_42[7] = vld1q_f32(&B.data[(42) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_42[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_42[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_42[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_42[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_42[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_42[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_42[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_42[7]);
}
float32x4_t B_vec_43[8];
B_vec_43[0] = vld1q_f32(&B.data[(43) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_43[1] = vld1q_f32(&B.data[(43) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_43[2] = vld1q_f32(&B.data[(43) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_43[3] = vld1q_f32(&B.data[(43) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_43[4] = vld1q_f32(&B.data[(43) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_43[5] = vld1q_f32(&B.data[(43) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_43[6] = vld1q_f32(&B.data[(43) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_43[7] = vld1q_f32(&B.data[(43) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_43[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_43[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_43[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_43[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_43[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_43[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_43[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_43[7]);
}
float32x4_t B_vec_44[8];
B_vec_44[0] = vld1q_f32(&B.data[(44) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_44[1] = vld1q_f32(&B.data[(44) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_44[2] = vld1q_f32(&B.data[(44) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_44[3] = vld1q_f32(&B.data[(44) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_44[4] = vld1q_f32(&B.data[(44) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_44[5] = vld1q_f32(&B.data[(44) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_44[6] = vld1q_f32(&B.data[(44) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_44[7] = vld1q_f32(&B.data[(44) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_44[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_44[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_44[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_44[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_44[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_44[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_44[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_44[7]);
}
float32x4_t B_vec_45[8];
B_vec_45[0] = vld1q_f32(&B.data[(45) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_45[1] = vld1q_f32(&B.data[(45) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_45[2] = vld1q_f32(&B.data[(45) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_45[3] = vld1q_f32(&B.data[(45) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_45[4] = vld1q_f32(&B.data[(45) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_45[5] = vld1q_f32(&B.data[(45) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_45[6] = vld1q_f32(&B.data[(45) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_45[7] = vld1q_f32(&B.data[(45) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_45[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_45[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_45[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_45[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_45[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_45[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_45[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_45[7]);
}
float32x4_t B_vec_46[8];
B_vec_46[0] = vld1q_f32(&B.data[(46) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_46[1] = vld1q_f32(&B.data[(46) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_46[2] = vld1q_f32(&B.data[(46) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_46[3] = vld1q_f32(&B.data[(46) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_46[4] = vld1q_f32(&B.data[(46) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_46[5] = vld1q_f32(&B.data[(46) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_46[6] = vld1q_f32(&B.data[(46) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_46[7] = vld1q_f32(&B.data[(46) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_46[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_46[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_46[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_46[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_46[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_46[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_46[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_46[7]);
}
float32x4_t B_vec_47[8];
B_vec_47[0] = vld1q_f32(&B.data[(47) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_47[1] = vld1q_f32(&B.data[(47) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_47[2] = vld1q_f32(&B.data[(47) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_47[3] = vld1q_f32(&B.data[(47) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_47[4] = vld1q_f32(&B.data[(47) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_47[5] = vld1q_f32(&B.data[(47) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_47[6] = vld1q_f32(&B.data[(47) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_47[7] = vld1q_f32(&B.data[(47) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_47[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_47[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_47[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_47[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_47[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_47[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_47[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_47[7]);
}
float32x4_t B_vec_48[8];
B_vec_48[0] = vld1q_f32(&B.data[(48) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_48[1] = vld1q_f32(&B.data[(48) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_48[2] = vld1q_f32(&B.data[(48) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_48[3] = vld1q_f32(&B.data[(48) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_48[4] = vld1q_f32(&B.data[(48) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_48[5] = vld1q_f32(&B.data[(48) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_48[6] = vld1q_f32(&B.data[(48) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_48[7] = vld1q_f32(&B.data[(48) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_48[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_48[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_48[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_48[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_48[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_48[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_48[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_48[7]);
}
float32x4_t B_vec_49[8];
B_vec_49[0] = vld1q_f32(&B.data[(49) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_49[1] = vld1q_f32(&B.data[(49) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_49[2] = vld1q_f32(&B.data[(49) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_49[3] = vld1q_f32(&B.data[(49) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_49[4] = vld1q_f32(&B.data[(49) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_49[5] = vld1q_f32(&B.data[(49) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_49[6] = vld1q_f32(&B.data[(49) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_49[7] = vld1q_f32(&B.data[(49) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_49[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_49[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_49[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_49[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_49[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_49[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_49[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_49[7]);
}
float32x4_t B_vec_50[8];
B_vec_50[0] = vld1q_f32(&B.data[(50) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_50[1] = vld1q_f32(&B.data[(50) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_50[2] = vld1q_f32(&B.data[(50) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_50[3] = vld1q_f32(&B.data[(50) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_50[4] = vld1q_f32(&B.data[(50) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_50[5] = vld1q_f32(&B.data[(50) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_50[6] = vld1q_f32(&B.data[(50) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_50[7] = vld1q_f32(&B.data[(50) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_50[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_50[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_50[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_50[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_50[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_50[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_50[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_50[7]);
}
float32x4_t B_vec_51[8];
B_vec_51[0] = vld1q_f32(&B.data[(51) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_51[1] = vld1q_f32(&B.data[(51) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_51[2] = vld1q_f32(&B.data[(51) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_51[3] = vld1q_f32(&B.data[(51) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_51[4] = vld1q_f32(&B.data[(51) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_51[5] = vld1q_f32(&B.data[(51) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_51[6] = vld1q_f32(&B.data[(51) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_51[7] = vld1q_f32(&B.data[(51) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_51[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_51[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_51[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_51[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_51[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_51[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_51[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_51[7]);
}
float32x4_t B_vec_52[8];
B_vec_52[0] = vld1q_f32(&B.data[(52) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_52[1] = vld1q_f32(&B.data[(52) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_52[2] = vld1q_f32(&B.data[(52) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_52[3] = vld1q_f32(&B.data[(52) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_52[4] = vld1q_f32(&B.data[(52) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_52[5] = vld1q_f32(&B.data[(52) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_52[6] = vld1q_f32(&B.data[(52) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_52[7] = vld1q_f32(&B.data[(52) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_52[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_52[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_52[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_52[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_52[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_52[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_52[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_52[7]);
}
float32x4_t B_vec_53[8];
B_vec_53[0] = vld1q_f32(&B.data[(53) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_53[1] = vld1q_f32(&B.data[(53) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_53[2] = vld1q_f32(&B.data[(53) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_53[3] = vld1q_f32(&B.data[(53) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_53[4] = vld1q_f32(&B.data[(53) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_53[5] = vld1q_f32(&B.data[(53) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_53[6] = vld1q_f32(&B.data[(53) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_53[7] = vld1q_f32(&B.data[(53) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_53[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_53[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_53[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_53[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_53[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_53[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_53[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_53[7]);
}
float32x4_t B_vec_54[8];
B_vec_54[0] = vld1q_f32(&B.data[(54) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_54[1] = vld1q_f32(&B.data[(54) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_54[2] = vld1q_f32(&B.data[(54) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_54[3] = vld1q_f32(&B.data[(54) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_54[4] = vld1q_f32(&B.data[(54) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_54[5] = vld1q_f32(&B.data[(54) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_54[6] = vld1q_f32(&B.data[(54) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_54[7] = vld1q_f32(&B.data[(54) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_54[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_54[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_54[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_54[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_54[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_54[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_54[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_54[7]);
}
float32x4_t B_vec_55[8];
B_vec_55[0] = vld1q_f32(&B.data[(55) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_55[1] = vld1q_f32(&B.data[(55) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_55[2] = vld1q_f32(&B.data[(55) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_55[3] = vld1q_f32(&B.data[(55) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_55[4] = vld1q_f32(&B.data[(55) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_55[5] = vld1q_f32(&B.data[(55) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_55[6] = vld1q_f32(&B.data[(55) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_55[7] = vld1q_f32(&B.data[(55) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_55[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_55[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_55[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_55[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_55[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_55[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_55[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_55[7]);
}
float32x4_t B_vec_56[8];
B_vec_56[0] = vld1q_f32(&B.data[(56) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_56[1] = vld1q_f32(&B.data[(56) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_56[2] = vld1q_f32(&B.data[(56) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_56[3] = vld1q_f32(&B.data[(56) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_56[4] = vld1q_f32(&B.data[(56) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_56[5] = vld1q_f32(&B.data[(56) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_56[6] = vld1q_f32(&B.data[(56) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_56[7] = vld1q_f32(&B.data[(56) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_56[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_56[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_56[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_56[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_56[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_56[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_56[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_56[7]);
}
float32x4_t B_vec_57[8];
B_vec_57[0] = vld1q_f32(&B.data[(57) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_57[1] = vld1q_f32(&B.data[(57) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_57[2] = vld1q_f32(&B.data[(57) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_57[3] = vld1q_f32(&B.data[(57) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_57[4] = vld1q_f32(&B.data[(57) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_57[5] = vld1q_f32(&B.data[(57) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_57[6] = vld1q_f32(&B.data[(57) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_57[7] = vld1q_f32(&B.data[(57) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_57[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_57[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_57[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_57[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_57[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_57[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_57[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_57[7]);
}
float32x4_t B_vec_58[8];
B_vec_58[0] = vld1q_f32(&B.data[(58) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_58[1] = vld1q_f32(&B.data[(58) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_58[2] = vld1q_f32(&B.data[(58) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_58[3] = vld1q_f32(&B.data[(58) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_58[4] = vld1q_f32(&B.data[(58) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_58[5] = vld1q_f32(&B.data[(58) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_58[6] = vld1q_f32(&B.data[(58) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_58[7] = vld1q_f32(&B.data[(58) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_58[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_58[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_58[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_58[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_58[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_58[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_58[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_58[7]);
}
float32x4_t B_vec_59[8];
B_vec_59[0] = vld1q_f32(&B.data[(59) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_59[1] = vld1q_f32(&B.data[(59) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_59[2] = vld1q_f32(&B.data[(59) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_59[3] = vld1q_f32(&B.data[(59) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_59[4] = vld1q_f32(&B.data[(59) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_59[5] = vld1q_f32(&B.data[(59) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_59[6] = vld1q_f32(&B.data[(59) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_59[7] = vld1q_f32(&B.data[(59) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_59[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_59[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_59[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_59[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_59[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_59[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_59[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_59[7]);
}
float32x4_t B_vec_60[8];
B_vec_60[0] = vld1q_f32(&B.data[(60) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_60[1] = vld1q_f32(&B.data[(60) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_60[2] = vld1q_f32(&B.data[(60) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_60[3] = vld1q_f32(&B.data[(60) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_60[4] = vld1q_f32(&B.data[(60) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_60[5] = vld1q_f32(&B.data[(60) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_60[6] = vld1q_f32(&B.data[(60) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_60[7] = vld1q_f32(&B.data[(60) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_60[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_60[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_60[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_60[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_60[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_60[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_60[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_60[7]);
}
float32x4_t B_vec_61[8];
B_vec_61[0] = vld1q_f32(&B.data[(61) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_61[1] = vld1q_f32(&B.data[(61) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_61[2] = vld1q_f32(&B.data[(61) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_61[3] = vld1q_f32(&B.data[(61) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_61[4] = vld1q_f32(&B.data[(61) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_61[5] = vld1q_f32(&B.data[(61) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_61[6] = vld1q_f32(&B.data[(61) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_61[7] = vld1q_f32(&B.data[(61) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_61[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_61[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_61[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_61[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_61[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_61[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_61[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_61[7]);
}
float32x4_t B_vec_62[8];
B_vec_62[0] = vld1q_f32(&B.data[(62) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_62[1] = vld1q_f32(&B.data[(62) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_62[2] = vld1q_f32(&B.data[(62) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_62[3] = vld1q_f32(&B.data[(62) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_62[4] = vld1q_f32(&B.data[(62) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_62[5] = vld1q_f32(&B.data[(62) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_62[6] = vld1q_f32(&B.data[(62) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_62[7] = vld1q_f32(&B.data[(62) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_62[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_62[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_62[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_62[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_62[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_62[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_62[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_62[7]);
}
float32x4_t B_vec_63[8];
B_vec_63[0] = vld1q_f32(&B.data[(63) * (B.strides[0]) + (0) * (B.strides[1])]);
B_vec_63[1] = vld1q_f32(&B.data[(63) * (B.strides[0]) + (4) * (B.strides[1])]);
B_vec_63[2] = vld1q_f32(&B.data[(63) * (B.strides[0]) + (8) * (B.strides[1])]);
B_vec_63[3] = vld1q_f32(&B.data[(63) * (B.strides[0]) + (12) * (B.strides[1])]);
B_vec_63[4] = vld1q_f32(&B.data[(63) * (B.strides[0]) + (16) * (B.strides[1])]);
B_vec_63[5] = vld1q_f32(&B.data[(63) * (B.strides[0]) + (20) * (B.strides[1])]);
B_vec_63[6] = vld1q_f32(&B.data[(63) * (B.strides[0]) + (24) * (B.strides[1])]);
B_vec_63[7] = vld1q_f32(&B.data[(63) * (B.strides[0]) + (28) * (B.strides[1])]);
for (int i = 0; i < 64; i++) {
  C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec_63[0]);
  C_reg[i][1] = vmlaq_f32(C_reg[i][1], A_vec[i], B_vec_63[1]);
  C_reg[i][2] = vmlaq_f32(C_reg[i][2], A_vec[i], B_vec_63[2]);
  C_reg[i][3] = vmlaq_f32(C_reg[i][3], A_vec[i], B_vec_63[3]);
  C_reg[i][4] = vmlaq_f32(C_reg[i][4], A_vec[i], B_vec_63[4]);
  C_reg[i][5] = vmlaq_f32(C_reg[i][5], A_vec[i], B_vec_63[5]);
  C_reg[i][6] = vmlaq_f32(C_reg[i][6], A_vec[i], B_vec_63[6]);
  C_reg[i][7] = vmlaq_f32(C_reg[i][7], A_vec[i], B_vec_63[7]);
}
for (int i = 0; i < 64; i++) {
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (0) * (C.strides[1])], C_reg[i][0]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (4) * (C.strides[1])], C_reg[i][1]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (8) * (C.strides[1])], C_reg[i][2]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (12) * (C.strides[1])], C_reg[i][3]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (16) * (C.strides[1])], C_reg[i][4]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (20) * (C.strides[1])], C_reg[i][5]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (24) * (C.strides[1])], C_reg[i][6]);
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (28) * (C.strides[1])], C_reg[i][7]);
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
for (int io = 0; io < 1; io++) {
  for (int jo = 0; jo < ((N) / (32)); jo++) {
    neon_microkernel(ctxt,(struct exo_win_2f32){ (float*)&A.data[(64 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (32 * jo) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(64 * io) * (C.strides[0]) + (32 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
for (int io = 0; io < 1; io++) {
  if (N % 32 > 0) {
    microkernel_edge_gebp_scheduled(ctxt,N % 32,(struct exo_win_2f32){ (float*)&A.data[(64 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (32 * ((N) / (32))) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(64 * io) * (C.strides[0]) + (32 * ((N) / (32))) * (C.strides[1])], { C.strides[0], C.strides[1] } });
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
  static float A_panel[256 * 64];
  for (int i0 = 0; i0 < M - 0; i0++) {
    for (int i1 = 0; i1 < 64 * ki + 64 - 64 * ki; i1++) {
      A_panel[(i0) * (64) + (i1) * (1)] = A[(0 + i0) * (K) + (64 * ki + i1) * (1)];
    }
  }
  static float B_panel[64 * 256];
  for (int i0 = 0; i0 < 64 * ki + 64 - 64 * ki; i0++) {
    for (int i1 = 0; i1 < N - 0; i1++) {
      B_panel[(i0) * (256) + (i1) * (1)] = B[(64 * ki + i0) * (N) + (0 + i1) * (1)];
    }
  }
  GEPP(ctxt,M,N,(struct exo_win_2f32){ (float*)&A_panel[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&B_panel[(0) * (256) + (0) * (1)], { 256, 1 } },(struct exo_win_2f32){ (float*)&C[(0) * (N) + (0) * (1)], { N, 1 } });
}
if (K % 64 > 0) {
  GEPP_edge(ctxt,M,N,K % 64,(struct exo_win_2f32){ (float*)&A[(0) * (K) + (64 * ((K) / (64))) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B[(64 * ((K) / (64))) * (N) + (0) * (1)], { N, 1 } },(struct exo_win_2f32){ (float*)&C[(0) * (N) + (0) * (1)], { N, 1 } });
}
}
