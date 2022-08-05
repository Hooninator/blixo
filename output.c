
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


#include <stdio.h>
#include <stdlib.h>


#include <arm_neon.h>

// neon_microkernel_edge(
//     K : size,
//     A : [f32][32,K]  @DRAM,
//     B : [f32][K,8]  @DRAM,
//     C : [f32][32,8]  @DRAM
// )
void neon_microkernel_edge( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[32][2];
for (int i = 0; i < 32; i++) {
  for (int jo = 0; jo < 2; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  float32x4_t A_vec[32];
  for (int i = 0; i < 32; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[2];
  for (int jo = 0; jo < 2; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 32; i++) {
    for (int jo = 0; jo < 2; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 32; i++) {
  for (int jo = 0; jo < 2; jo++) {
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
for (int io = 0; io < 2; io++) {
  for (int jo = 0; jo < ((N) / (8)); jo++) {
    neon_microkernel_edge(ctxt,K,(struct exo_win_2f32){ (float*)&A.data[(32 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (8 * jo) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(32 * io) * (C.strides[0]) + (8 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
for (int io = 0; io < 2; io++) {
  if (N % 8 > 0) {
    for (int ii = 0; ii < 32; ii++) {
      for (int ji = 0; ji < N % 8; ji++) {
        for (int k = 0; k < K; k++) {
          C.data[(32 * io + ii) * (C.strides[0]) + (ji + ((N) / (8)) * 8) * (C.strides[1])] += A.data[(32 * io + ii) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + ((N) / (8)) * 8) * (B.strides[1])];
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

// gebp_edge_neon_microkernel_1x6(
//     A : [f32][32,64]  @DRAM,
//     B : [f32][64,6]  @DRAM,
//     C : [f32][32,6]  @DRAM
// )
void gebp_edge_neon_microkernel_1x6( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 32; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 4) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 4) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x7(
//     A : [f32][32,64]  @DRAM,
//     B : [f32][64,7]  @DRAM,
//     C : [f32][32,7]  @DRAM
// )
void gebp_edge_neon_microkernel_1x7( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 32; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 4) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 4) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x5(
//     A : [f32][32,64]  @DRAM,
//     B : [f32][64,5]  @DRAM,
//     C : [f32][32,5]  @DRAM
// )
void gebp_edge_neon_microkernel_1x5( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 32; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 4) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 4) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x4(
//     A : [f32][32,64]  @DRAM,
//     B : [f32][64,4]  @DRAM,
//     C : [f32][32,4]  @DRAM
// )
void gebp_edge_neon_microkernel_1x4( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[32][1];
for (int i = 0; i < 32; i++) {
  for (int jo = 0; jo < 1; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[32];
  for (int i = 0; i < 32; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[1];
  for (int jo = 0; jo < 1; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 32; i++) {
    for (int jo = 0; jo < 1; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 32; i++) {
  for (int jo = 0; jo < 1; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// microkernel_edge_gebp_scheduled(
//     N : size,
//     A : [f32][32,64]  @DRAM,
//     B : [f32][64,N]  @DRAM,
//     C : [f32][32,N]  @DRAM
// )
void microkernel_edge_gebp_scheduled( c_code_str_Context *ctxt, int_fast32_t N, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(N >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
EXO_ASSUME(N < 8);
if (N == 1) {
  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 1; j++) {
      for (int k = 0; k < 64; k++) {
        C.data[(i) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])];
      }
    }
  }
} else {
  if (N == 2) {
    for (int i = 0; i < 32; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 64; k++) {
          C.data[(i) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])];
        }
      }
    }
  } else {
    if (N == 3) {
      for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 3; j++) {
          for (int k = 0; k < 64; k++) {
            C.data[(i) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])];
          }
        }
      }
    } else {
      if (N == 4) {
        gebp_edge_neon_microkernel_1x4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
      } else {
        if (N == 5) {
          gebp_edge_neon_microkernel_1x5(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
        } else {
          if (N == 6) {
            gebp_edge_neon_microkernel_1x6(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
          } else {
            if (N == 7) {
              gebp_edge_neon_microkernel_1x7(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
            } else {
              for (int i = 0; i < 32; i++) {
                for (int j = 0; j < N; j++) {
                  for (int k = 0; k < 64; k++) {
                    C.data[(i) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])];
                  }
                }
              }
            }
          }
        }
      }
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
//     A : [f32][32,64]  @DRAM,
//     B : [f32][64,8]  @DRAM,
//     C : [f32][32,8]  @DRAM
// )
void neon_microkernel( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[32][2];
for (int i = 0; i < 32; i++) {
  for (int jo = 0; jo < 2; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
float32x4_t A_vec[32];
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 32; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t B_vec[2];
  for (int jo = 0; jo < 2; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 32; i++) {
    for (int jo = 0; jo < 2; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 32; i++) {
  for (int jo = 0; jo < 2; jo++) {
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
for (int io = 0; io < 2; io++) {
  for (int jo = 0; jo < ((N) / (8)); jo++) {
    neon_microkernel(ctxt,(struct exo_win_2f32){ (float*)&A.data[(32 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (8 * jo) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(32 * io) * (C.strides[0]) + (8 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
for (int io = 0; io < 2; io++) {
  if (N % 8 > 0) {
    microkernel_edge_gebp_scheduled(ctxt,N % 8,(struct exo_win_2f32){ (float*)&A.data[(32 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (8 * ((N) / (8))) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(32 * io) * (C.strides[0]) + (8 * ((N) / (8))) * (C.strides[1])], { C.strides[0], C.strides[1] } });
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
  float *A_blk = malloc(64 * 64 * sizeof(*A_blk));
  for (int i0 = 0; i0 < 64; i0++) {
    for (int i1 = 0; i1 < 64; i1++) {
      A_blk[(i0) * (64) + (i1) * (1)] = A.data[(i0 + 64 * io) * (A.strides[0]) + (i1) * (A.strides[1])];
    }
  }
  GEBP(ctxt,N,(struct exo_win_2f32){ (float*)&A_blk[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(64 * io) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  free(A_blk);
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
  static float A_panel[257 * 64];
  for (int i0 = 0; i0 < M - 0; i0++) {
    for (int i1 = 0; i1 < 64 * ki + 64 - 64 * ki; i1++) {
      A_panel[(i0) * (64) + (i1) * (1)] = A[(0 + i0) * (K) + (64 * ki + i1) * (1)];
    }
  }
  static float B_panel[64 * 257];
  for (int i0 = 0; i0 < 64 * ki + 64 - 64 * ki; i0++) {
    for (int i1 = 0; i1 < N - 0; i1++) {
      B_panel[(i0) * (257) + (i1) * (1)] = B[(64 * ki + i0) * (N) + (0 + i1) * (1)];
    }
  }
  GEPP(ctxt,M,N,(struct exo_win_2f32){ (float*)&A_panel[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&B_panel[(0) * (257) + (0) * (1)], { 257, 1 } },(struct exo_win_2f32){ (float*)&C[(0) * (N) + (0) * (1)], { N, 1 } });
}
if (K % 64 > 0) {
  GEPP_edge(ctxt,M,N,K % 64,(struct exo_win_2f32){ (float*)&A[(0) * (K) + (64 * ((K) / (64))) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B[(64 * ((K) / (64))) * (N) + (0) * (1)], { N, 1 } },(struct exo_win_2f32){ (float*)&C[(0) * (N) + (0) * (1)], { N, 1 } });
}
}
