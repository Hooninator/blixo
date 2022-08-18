
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
//     A : [f32][64,K]  @DRAM,
//     B : [f32][K,64]  @DRAM,
//     C : [f32][64,64]  @DRAM
// )
void neon_microkernel_edge( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][16];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 16; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[16];
  for (int jo = 0; jo < 16; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 16; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 16; jo++) {
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
  for (int jo = 0; jo < ((N) / (64)); jo++) {
    neon_microkernel_edge(ctxt,K,(struct exo_win_2f32){ (float*)&A.data[(64 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (64 * jo) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(64 * io) * (C.strides[0]) + (64 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
for (int io = 0; io < 1; io++) {
  if (N % 64 > 0) {
    for (int ii = 0; ii < 64; ii++) {
      for (int ji = 0; ji < N % 64; ji++) {
        for (int k = 0; k < K; k++) {
          C.data[(64 * io + ii) * (C.strides[0]) + (ji + ((N) / (64)) * 64) * (C.strides[1])] += A.data[(64 * io + ii) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + ((N) / (64)) * 64) * (B.strides[1])];
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

// gebp_edge_neon_microkernel_1x37(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,37]  @DRAM,
//     C : [f32][64,37]  @DRAM
// )
void gebp_edge_neon_microkernel_1x37( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x36(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 36) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 36) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x27(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,27]  @DRAM,
//     C : [f32][64,27]  @DRAM
// )
void gebp_edge_neon_microkernel_1x27( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x24(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 24) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 24) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x23(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,23]  @DRAM,
//     C : [f32][64,23]  @DRAM
// )
void gebp_edge_neon_microkernel_1x23( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x20(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 20) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 20) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x15(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,15]  @DRAM,
//     C : [f32][64,15]  @DRAM
// )
void gebp_edge_neon_microkernel_1x15( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x12(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 12) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 12) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x59(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,59]  @DRAM,
//     C : [f32][64,59]  @DRAM
// )
void gebp_edge_neon_microkernel_1x59( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x56(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 56) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 56) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x57(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,57]  @DRAM,
//     C : [f32][64,57]  @DRAM
// )
void gebp_edge_neon_microkernel_1x57( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x56(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 56) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 56) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x39(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,39]  @DRAM,
//     C : [f32][64,39]  @DRAM
// )
void gebp_edge_neon_microkernel_1x39( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x36(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 36) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 36) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x29(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,29]  @DRAM,
//     C : [f32][64,29]  @DRAM
// )
void gebp_edge_neon_microkernel_1x29( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x28(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 28) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 28) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x26(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,26]  @DRAM,
//     C : [f32][64,26]  @DRAM
// )
void gebp_edge_neon_microkernel_1x26( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x24(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 24) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 24) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x61(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,61]  @DRAM,
//     C : [f32][64,61]  @DRAM
// )
void gebp_edge_neon_microkernel_1x61( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x60(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 60) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 60) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x58(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,58]  @DRAM,
//     C : [f32][64,58]  @DRAM
// )
void gebp_edge_neon_microkernel_1x58( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x56(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 56) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 56) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x47(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,47]  @DRAM,
//     C : [f32][64,47]  @DRAM
// )
void gebp_edge_neon_microkernel_1x47( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x44(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 44) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 44) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x25(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,25]  @DRAM,
//     C : [f32][64,25]  @DRAM
// )
void gebp_edge_neon_microkernel_1x25( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x24(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 24) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 24) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x19(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,19]  @DRAM,
//     C : [f32][64,19]  @DRAM
// )
void gebp_edge_neon_microkernel_1x19( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x16(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 16) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 16) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x10(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,10]  @DRAM,
//     C : [f32][64,10]  @DRAM
// )
void gebp_edge_neon_microkernel_1x10( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x8(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 8) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 8) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x9(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,9]  @DRAM,
//     C : [f32][64,9]  @DRAM
// )
void gebp_edge_neon_microkernel_1x9( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x8(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 8) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 8) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x6(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,6]  @DRAM,
//     C : [f32][64,6]  @DRAM
// )
void gebp_edge_neon_microkernel_1x6( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 4) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 4) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x56(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,56]  @DRAM,
//     C : [f32][64,56]  @DRAM
// )
void gebp_edge_neon_microkernel_1x56( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][14];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 14; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[14];
  for (int jo = 0; jo < 14; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 14; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 14; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x50(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,50]  @DRAM,
//     C : [f32][64,50]  @DRAM
// )
void gebp_edge_neon_microkernel_1x50( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x48(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 48) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 48) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x34(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,34]  @DRAM,
//     C : [f32][64,34]  @DRAM
// )
void gebp_edge_neon_microkernel_1x34( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x32(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 32) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 32) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x33(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,33]  @DRAM,
//     C : [f32][64,33]  @DRAM
// )
void gebp_edge_neon_microkernel_1x33( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x32(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 32) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 32) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x31(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,31]  @DRAM,
//     C : [f32][64,31]  @DRAM
// )
void gebp_edge_neon_microkernel_1x31( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x28(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 28) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 28) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x24(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,24]  @DRAM,
//     C : [f32][64,24]  @DRAM
// )
void gebp_edge_neon_microkernel_1x24( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][6];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 6; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[6];
  for (int jo = 0; jo < 6; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 6; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 6; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x62(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,62]  @DRAM,
//     C : [f32][64,62]  @DRAM
// )
void gebp_edge_neon_microkernel_1x62( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x60(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 60) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 60) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x42(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,42]  @DRAM,
//     C : [f32][64,42]  @DRAM
// )
void gebp_edge_neon_microkernel_1x42( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x40(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 40) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 40) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x21(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,21]  @DRAM,
//     C : [f32][64,21]  @DRAM
// )
void gebp_edge_neon_microkernel_1x21( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x20(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 20) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 20) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x14(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,14]  @DRAM,
//     C : [f32][64,14]  @DRAM
// )
void gebp_edge_neon_microkernel_1x14( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x12(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 12) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 12) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x7(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,7]  @DRAM,
//     C : [f32][64,7]  @DRAM
// )
void gebp_edge_neon_microkernel_1x7( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 4) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 4) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x20(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,20]  @DRAM,
//     C : [f32][64,20]  @DRAM
// )
void gebp_edge_neon_microkernel_1x20( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][5];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 5; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[5];
  for (int jo = 0; jo < 5; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 5; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 5; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x22(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,22]  @DRAM,
//     C : [f32][64,22]  @DRAM
// )
void gebp_edge_neon_microkernel_1x22( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x20(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 20) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 20) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x63(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,63]  @DRAM,
//     C : [f32][64,63]  @DRAM
// )
void gebp_edge_neon_microkernel_1x63( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x60(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 60) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 60) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x55(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,55]  @DRAM,
//     C : [f32][64,55]  @DRAM
// )
void gebp_edge_neon_microkernel_1x55( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x52(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 52) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 52) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x54(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,54]  @DRAM,
//     C : [f32][64,54]  @DRAM
// )
void gebp_edge_neon_microkernel_1x54( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x52(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 52) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 52) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x49(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,49]  @DRAM,
//     C : [f32][64,49]  @DRAM
// )
void gebp_edge_neon_microkernel_1x49( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x48(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 48) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 48) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x32(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,32]  @DRAM,
//     C : [f32][64,32]  @DRAM
// )
void gebp_edge_neon_microkernel_1x32( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][8];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 8; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
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

// gebp_edge_neon_microkernel_1x35(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,35]  @DRAM,
//     C : [f32][64,35]  @DRAM
// )
void gebp_edge_neon_microkernel_1x35( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x32(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 32) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 32) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x18(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,18]  @DRAM,
//     C : [f32][64,18]  @DRAM
// )
void gebp_edge_neon_microkernel_1x18( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x16(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 16) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 16) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x17(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,17]  @DRAM,
//     C : [f32][64,17]  @DRAM
// )
void gebp_edge_neon_microkernel_1x17( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x16(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 16) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 16) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x16(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,16]  @DRAM,
//     C : [f32][64,16]  @DRAM
// )
void gebp_edge_neon_microkernel_1x16( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][4];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 4; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[4];
  for (int jo = 0; jo < 4; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 4; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 4; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x45(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,45]  @DRAM,
//     C : [f32][64,45]  @DRAM
// )
void gebp_edge_neon_microkernel_1x45( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x44(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 44) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 44) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x41(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,41]  @DRAM,
//     C : [f32][64,41]  @DRAM
// )
void gebp_edge_neon_microkernel_1x41( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x40(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 40) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 40) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x36(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,36]  @DRAM,
//     C : [f32][64,36]  @DRAM
// )
void gebp_edge_neon_microkernel_1x36( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][9];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 9; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[9];
  for (int jo = 0; jo < 9; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 9; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 9; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x38(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,38]  @DRAM,
//     C : [f32][64,38]  @DRAM
// )
void gebp_edge_neon_microkernel_1x38( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x36(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 36) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 36) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x30(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,30]  @DRAM,
//     C : [f32][64,30]  @DRAM
// )
void gebp_edge_neon_microkernel_1x30( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x28(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 28) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 28) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x11(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,11]  @DRAM,
//     C : [f32][64,11]  @DRAM
// )
void gebp_edge_neon_microkernel_1x11( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x8(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 8) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 8) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x8(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,8]  @DRAM,
//     C : [f32][64,8]  @DRAM
// )
void gebp_edge_neon_microkernel_1x8( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][2];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 2; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[2];
  for (int jo = 0; jo < 2; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 2; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 2; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x60(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,60]  @DRAM,
//     C : [f32][64,60]  @DRAM
// )
void gebp_edge_neon_microkernel_1x60( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][15];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 15; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[15];
  for (int jo = 0; jo < 15; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 15; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 15; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x52(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,52]  @DRAM,
//     C : [f32][64,52]  @DRAM
// )
void gebp_edge_neon_microkernel_1x52( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][13];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 13; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[13];
  for (int jo = 0; jo < 13; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 13; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 13; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x53(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,53]  @DRAM,
//     C : [f32][64,53]  @DRAM
// )
void gebp_edge_neon_microkernel_1x53( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x52(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 52) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 52) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x48(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,48]  @DRAM,
//     C : [f32][64,48]  @DRAM
// )
void gebp_edge_neon_microkernel_1x48( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][12];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 12; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[12];
  for (int jo = 0; jo < 12; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 12; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 12; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x51(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,51]  @DRAM,
//     C : [f32][64,51]  @DRAM
// )
void gebp_edge_neon_microkernel_1x51( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x48(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 48) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 48) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x44(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,44]  @DRAM,
//     C : [f32][64,44]  @DRAM
// )
void gebp_edge_neon_microkernel_1x44( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][11];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 11; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[11];
  for (int jo = 0; jo < 11; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 11; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 11; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x46(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,46]  @DRAM,
//     C : [f32][64,46]  @DRAM
// )
void gebp_edge_neon_microkernel_1x46( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x44(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 2; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 44) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 44) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x40(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,40]  @DRAM,
//     C : [f32][64,40]  @DRAM
// )
void gebp_edge_neon_microkernel_1x40( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][10];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 10; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[10];
  for (int jo = 0; jo < 10; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 10; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 10; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x43(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,43]  @DRAM,
//     C : [f32][64,43]  @DRAM
// )
void gebp_edge_neon_microkernel_1x43( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x40(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 3; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 40) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 40) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x28(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,28]  @DRAM,
//     C : [f32][64,28]  @DRAM
// )
void gebp_edge_neon_microkernel_1x28( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][7];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 7; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[7];
  for (int jo = 0; jo < 7; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 7; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 7; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x12(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,12]  @DRAM,
//     C : [f32][64,12]  @DRAM
// )
void gebp_edge_neon_microkernel_1x12( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][3];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 3; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[3];
  for (int jo = 0; jo < 3; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 3; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 3; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x13(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,13]  @DRAM,
//     C : [f32][64,13]  @DRAM
// )
void gebp_edge_neon_microkernel_1x13( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x12(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 12) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 12) * (B.strides[1])];
    }
  }
}
}

// gebp_edge_neon_microkernel_1x4(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,4]  @DRAM,
//     C : [f32][64,4]  @DRAM
// )
void gebp_edge_neon_microkernel_1x4( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][1];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 1; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t A_vec[64];
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[1];
  for (int jo = 0; jo < 1; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 1; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 1; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// gebp_edge_neon_microkernel_1x5(
//     A : [f32][64,64]  @DRAM,
//     B : [f32][64,5]  @DRAM,
//     C : [f32][64,5]  @DRAM
// )
void gebp_edge_neon_microkernel_1x5( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
gebp_edge_neon_microkernel_1x4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    for (int ji = 0; ji < 1; ji++) {
      C.data[(i) * (C.strides[0]) + (ji + 4) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + 4) * (B.strides[1])];
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
EXO_ASSUME(N < 64);
if (N == 1) {
  for (int i = 0; i < 64; i++) {
    for (int j = 0; j < 1; j++) {
      for (int k = 0; k < 64; k++) {
        C.data[(i) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])];
      }
    }
  }
} else {
  if (N == 2) {
    for (int i = 0; i < 64; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 64; k++) {
          C.data[(i) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])];
        }
      }
    }
  } else {
    if (N == 3) {
      for (int i = 0; i < 64; i++) {
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
              if (N == 8) {
                gebp_edge_neon_microkernel_1x8(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
              } else {
                if (N == 9) {
                  gebp_edge_neon_microkernel_1x9(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                } else {
                  if (N == 10) {
                    gebp_edge_neon_microkernel_1x10(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                  } else {
                    if (N == 11) {
                      gebp_edge_neon_microkernel_1x11(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                    } else {
                      if (N == 12) {
                        gebp_edge_neon_microkernel_1x12(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                      } else {
                        if (N == 13) {
                          gebp_edge_neon_microkernel_1x13(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                        } else {
                          if (N == 14) {
                            gebp_edge_neon_microkernel_1x14(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                          } else {
                            if (N == 15) {
                              gebp_edge_neon_microkernel_1x15(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                            } else {
                              if (N == 16) {
                                gebp_edge_neon_microkernel_1x16(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                              } else {
                                if (N == 17) {
                                  gebp_edge_neon_microkernel_1x17(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                } else {
                                  if (N == 18) {
                                    gebp_edge_neon_microkernel_1x18(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                  } else {
                                    if (N == 19) {
                                      gebp_edge_neon_microkernel_1x19(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                    } else {
                                      if (N == 20) {
                                        gebp_edge_neon_microkernel_1x20(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                      } else {
                                        if (N == 21) {
                                          gebp_edge_neon_microkernel_1x21(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                        } else {
                                          if (N == 22) {
                                            gebp_edge_neon_microkernel_1x22(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                          } else {
                                            if (N == 23) {
                                              gebp_edge_neon_microkernel_1x23(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                            } else {
                                              if (N == 24) {
                                                gebp_edge_neon_microkernel_1x24(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                              } else {
                                                if (N == 25) {
                                                  gebp_edge_neon_microkernel_1x25(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                } else {
                                                  if (N == 26) {
                                                    gebp_edge_neon_microkernel_1x26(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                  } else {
                                                    if (N == 27) {
                                                      gebp_edge_neon_microkernel_1x27(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                    } else {
                                                      if (N == 28) {
                                                        gebp_edge_neon_microkernel_1x28(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                      } else {
                                                        if (N == 29) {
                                                          gebp_edge_neon_microkernel_1x29(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                        } else {
                                                          if (N == 30) {
                                                            gebp_edge_neon_microkernel_1x30(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                          } else {
                                                            if (N == 31) {
                                                              gebp_edge_neon_microkernel_1x31(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                            } else {
                                                              if (N == 32) {
                                                                gebp_edge_neon_microkernel_1x32(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                              } else {
                                                                if (N == 33) {
                                                                  gebp_edge_neon_microkernel_1x33(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                } else {
                                                                  if (N == 34) {
                                                                    gebp_edge_neon_microkernel_1x34(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                  } else {
                                                                    if (N == 35) {
                                                                      gebp_edge_neon_microkernel_1x35(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                    } else {
                                                                      if (N == 36) {
                                                                        gebp_edge_neon_microkernel_1x36(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                      } else {
                                                                        if (N == 37) {
                                                                          gebp_edge_neon_microkernel_1x37(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                        } else {
                                                                          if (N == 38) {
                                                                            gebp_edge_neon_microkernel_1x38(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                          } else {
                                                                            if (N == 39) {
                                                                              gebp_edge_neon_microkernel_1x39(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                            } else {
                                                                              if (N == 40) {
                                                                                gebp_edge_neon_microkernel_1x40(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                              } else {
                                                                                if (N == 41) {
                                                                                  gebp_edge_neon_microkernel_1x41(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                } else {
                                                                                  if (N == 42) {
                                                                                    gebp_edge_neon_microkernel_1x42(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                  } else {
                                                                                    if (N == 43) {
                                                                                      gebp_edge_neon_microkernel_1x43(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                    } else {
                                                                                      if (N == 44) {
                                                                                        gebp_edge_neon_microkernel_1x44(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                      } else {
                                                                                        if (N == 45) {
                                                                                          gebp_edge_neon_microkernel_1x45(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                        } else {
                                                                                          if (N == 46) {
                                                                                            gebp_edge_neon_microkernel_1x46(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                          } else {
                                                                                            if (N == 47) {
                                                                                              gebp_edge_neon_microkernel_1x47(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                            } else {
                                                                                              if (N == 48) {
                                                                                                gebp_edge_neon_microkernel_1x48(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                              } else {
                                                                                                if (N == 49) {
                                                                                                  gebp_edge_neon_microkernel_1x49(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                } else {
                                                                                                  if (N == 50) {
                                                                                                    gebp_edge_neon_microkernel_1x50(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                  } else {
                                                                                                    if (N == 51) {
                                                                                                      gebp_edge_neon_microkernel_1x51(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                    } else {
                                                                                                      if (N == 52) {
                                                                                                        gebp_edge_neon_microkernel_1x52(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                      } else {
                                                                                                        if (N == 53) {
                                                                                                          gebp_edge_neon_microkernel_1x53(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                        } else {
                                                                                                          if (N == 54) {
                                                                                                            gebp_edge_neon_microkernel_1x54(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                          } else {
                                                                                                            if (N == 55) {
                                                                                                              gebp_edge_neon_microkernel_1x55(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                            } else {
                                                                                                              if (N == 56) {
                                                                                                                gebp_edge_neon_microkernel_1x56(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                              } else {
                                                                                                                if (N == 57) {
                                                                                                                  gebp_edge_neon_microkernel_1x57(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                                } else {
                                                                                                                  if (N == 58) {
                                                                                                                    gebp_edge_neon_microkernel_1x58(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                                  } else {
                                                                                                                    if (N == 59) {
                                                                                                                      gebp_edge_neon_microkernel_1x59(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                                    } else {
                                                                                                                      if (N == 60) {
                                                                                                                        gebp_edge_neon_microkernel_1x60(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                                      } else {
                                                                                                                        if (N == 61) {
                                                                                                                          gebp_edge_neon_microkernel_1x61(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                                        } else {
                                                                                                                          if (N == 62) {
                                                                                                                            gebp_edge_neon_microkernel_1x62(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                                          } else {
                                                                                                                            if (N == 63) {
                                                                                                                              gebp_edge_neon_microkernel_1x63(ctxt,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                                                                                                            } else {
                                                                                                                              for (int i = 0; i < 64; i++) {
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
//     B : [f32][64,64]  @DRAM,
//     C : [f32][64,64]  @DRAM
// )
void neon_microkernel( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[64][16];
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 16; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
float32x4_t A_vec[64];
for (int k = 0; k < 64; k++) {
  for (int i = 0; i < 64; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
}
for (int k = 0; k < 64; k++) {
  float32x4_t B_vec[16];
  for (int jo = 0; jo < 16; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 64; i++) {
    for (int jo = 0; jo < 16; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 64; i++) {
  for (int jo = 0; jo < 16; jo++) {
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
for (int io = 0; io < 1; io++) {
  for (int jo = 0; jo < ((N) / (64)); jo++) {
    neon_microkernel(ctxt,(struct exo_win_2f32){ (float*)&A.data[(64 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (64 * jo) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(64 * io) * (C.strides[0]) + (64 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
for (int io = 0; io < 1; io++) {
  if (N % 64 > 0) {
    microkernel_edge_gebp_scheduled(ctxt,N % 64,(struct exo_win_2f32){ (float*)&A.data[(64 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (64 * ((N) / (64))) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(64 * io) * (C.strides[0]) + (64 * ((N) / (64))) * (C.strides[1])], { C.strides[0], C.strides[1] } });
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
