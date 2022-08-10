
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


// __SYMM_BLK(
//     K : size,
//     A : f32[32,K]  @DRAM,
//     B : f32[K,32]  @DRAM,
//     C : f32[32,32]  @DRAM
// )
void __SYMM_BLK( c_code_str_Context *ctxt, int_fast32_t K, float* A, float* B, float* C );


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
//     A : [f32][4,4]  @DRAM,
//     B : [f32][4,4]  @DRAM,
//     C : [f32][4,4]  @DRAM
// )
void neon_microkernel( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[4][1];
for (int i = 0; i < 4; i++) {
  C_reg[i][0] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (0) * (C.strides[1])]);
}
for (int k = 0; k < 4; k++) {
  float32x4_t A_vec[4];
  for (int i = 0; i < 4; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[1];
  B_vec[0] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (0) * (B.strides[1])]);
  for (int i = 0; i < 4; i++) {
    C_reg[i][0] = vmlaq_f32(C_reg[i][0], A_vec[i], B_vec[0]);
  }
}
for (int i = 0; i < 4; i++) {
  vst1q_f32(&C.data[(i) * (C.strides[0]) + (0) * (C.strides[1])], C_reg[i][0]);
}
}

// GEBP(
//     N : size,
//     A : [f32][4,4]  @DRAM,
//     B : [f32][4,N]  @DRAM,
//     C : [f32][4,N]  @DRAM
// )
void GEBP( c_code_str_Context *ctxt, int_fast32_t N, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(N >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
for (int io = 0; io < 1; io++) {
  for (int jo = 0; jo < ((N) / (4)); jo++) {
    neon_microkernel(ctxt,(struct exo_win_2f32){ (float*)&A.data[(4 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (4 * jo) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(4 * io) * (C.strides[0]) + (4 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
for (int io = 0; io < 1; io++) {
  if (N % 4 > 0) {
    for (int ii = 0; ii < 4; ii++) {
      for (int ji = 0; ji < N % 4; ji++) {
        for (int k = 0; k < 4; k++) {
          C.data[(4 * io + ii) * (C.strides[0]) + (ji + ((N) / (4)) * 4) * (C.strides[1])] += A.data[(4 * io + ii) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + ((N) / (4)) * 4) * (B.strides[1])];
        }
      }
    }
  }
}
}

// GEPP(
//     M : size,
//     N : size,
//     A : [f32][M,4]  @DRAM,
//     B : [f32][4,N]  @DRAM,
//     C : [f32][M,N]  @DRAM
// )
void GEPP( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(N >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
for (int io = 0; io < ((M) / (4)); io++) {
  static float A_blk[4 * 4];
  for (int i0 = 0; i0 < 4; i0++) {
    for (int i1 = 0; i1 < 4; i1++) {
      A_blk[(i0) * (4) + (i1) * (1)] = A.data[(i0 + 4 * io) * (A.strides[0]) + (i1) * (A.strides[1])];
    }
  }
  GEBP(ctxt,N,(struct exo_win_2f32){ (float*)&A_blk[(0) * (4) + (0) * (1)], { 4, 1 } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(4 * io) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
}
if (M % 4 > 0) {
  for (int ii = 0; ii < M % 4; ii++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < 4; k++) {
        C.data[(ii + ((M) / (4)) * 4) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(ii + ((M) / (4)) * 4) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])];
      }
    }
  }
}
}

// __SYMM_BLK(
//     K : size,
//     A : f32[32,K]  @DRAM,
//     B : f32[K,32]  @DRAM,
//     C : f32[32,32]  @DRAM
// )
void __SYMM_BLK( c_code_str_Context *ctxt, int_fast32_t K, float* A, float* B, float* C ) {
EXO_ASSUME(32 >= 1);
EXO_ASSUME(K >= 1);
EXO_ASSUME(K > 4);
EXO_ASSUME(K % 4 == 0);
EXO_ASSUME(32 % 4 == 0);
EXO_ASSUME(K >= 4 * (7 + 1));
EXO_ASSUME(32 >= 4 * (7 + 1));
EXO_ASSUME(1 == 1);
EXO_ASSUME(1 == 1);
EXO_ASSUME(1 == 1);
for (int n_iter = 0; n_iter < 7 + 1; n_iter++) {
  static float A_panel[32 * 4];
  for (int i = 0; i < n_iter * 4; i++) {
    for (int k = 0; k < 4; k++) {
      A_panel[(i) * (4) + (k) * (1)] = A[(k + n_iter * 4) * (K) + (i) * (1)];
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int k = 0; k < 4; k++) {
      A_panel[(n_iter * 4 + i) * (4) + (k) * (1)] = A[(i + n_iter * 4) * (K) + (k + n_iter * 4) * (1)];
    }
  }
  for (int i = 0; i < 32 - 4 - n_iter * 4; i++) {
    for (int k = 0; k < 4; k++) {
      A_panel[(4 + n_iter * 4 + i) * (4) + (k) * (1)] = A[(i + 4 * n_iter + 4) * (K) + (k + n_iter * 4) * (1)];
    }
  }
  static float B_panel[4 * 32];
  for (int j = 0; j < 32; j++) {
    for (int k = 0; k < 4; k++) {
      B_panel[(k) * (32) + (j) * (1)] = B[(k + 4 * n_iter) * (32) + (j) * (1)];
    }
  }
  GEPP(ctxt,32,32,(struct exo_win_2f32){ (float*)&A_panel[(0) * (4) + (0) * (1)], { 4, 1 } },(struct exo_win_2f32){ (float*)&B_panel[(0) * (32) + (0) * (1)], { 32, 1 } },(struct exo_win_2f32){ (float*)&C[(0) * (32) + (0) * (1)], { 32, 1 } });
}
}
