
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


// exo_syrk(
//     M : size,
//     K : size,
//     A : f32[M,K]  @DRAM,
//     A_t : f32[M,K]  @DRAM,
//     C : f32[M,M]  @DRAM
// )
void exo_syrk( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t K, float* A, float* A_t, float* C );


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


// neon_microkernel_two_12(
//     A : [f32][12,4]  @DRAM,
//     A_t : [f32][12,4]  @DRAM,
//     C : [f32][12,12]  @DRAM
// )
void neon_microkernel_two_12( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 A_t, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(A_t.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[3];
C_reg[0 + 0] = vld1q_f32(&C.data[(0) * (C.strides[0]) + (4 * 0 + 0) * (C.strides[1])]);
C_reg[1 + 0] = vld1q_f32(&C.data[(0) * (C.strides[0]) + (4 * 1 + 0) * (C.strides[1])]);
C_reg[2 + 0] = vld1q_f32(&C.data[(0) * (C.strides[0]) + (4 * 2 + 0) * (C.strides[1])]);
float32x4_t A_vec;
for (int k = 0; k < 4; k++) {
  A_vec = vld1q_dup_f32(&A.data[(0) * (A.strides[0]) + (k + 0) * (A.strides[1])]);
}
float32x4_t A_t_vec[3];
for (int k = 0; k < 4; k++) {
  A_t_vec[0] = vld1q_f32(&A_t.data[(4 * 0 + 0) * (A_t.strides[0]) + (k + 0) * (A_t.strides[1])]);
  A_t_vec[1] = vld1q_f32(&A_t.data[(4 * 1 + 0) * (A_t.strides[0]) + (k + 0) * (A_t.strides[1])]);
  A_t_vec[2] = vld1q_f32(&A_t.data[(4 * 2 + 0) * (A_t.strides[0]) + (k + 0) * (A_t.strides[1])]);
}
for (int k = 0; k < 4; k++) {
  C_reg[0 + 0] = vmlaq_f32(C_reg[0 + 0], A_vec, A_t_vec[0]);
  C_reg[1 + 0] = vmlaq_f32(C_reg[1 + 0], A_vec, A_t_vec[1]);
  C_reg[2 + 0] = vmlaq_f32(C_reg[2 + 0], A_vec, A_t_vec[2]);
}
vst1q_f32(&C.data[(0) * (C.strides[0]) + (4 * 0 + 0) * (C.strides[1])], C_reg[0 + 0]);
vst1q_f32(&C.data[(0) * (C.strides[0]) + (4 * 1 + 0) * (C.strides[1])], C_reg[1 + 0]);
vst1q_f32(&C.data[(0) * (C.strides[0]) + (4 * 2 + 0) * (C.strides[1])], C_reg[2 + 0]);
}

// neon_microkernel_two_8(
//     A : [f32][8,4]  @DRAM,
//     A_t : [f32][8,4]  @DRAM,
//     C : [f32][8,8]  @DRAM
// )
void neon_microkernel_two_8( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 A_t, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(A_t.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[2];
C_reg[0 + 0] = vld1q_f32(&C.data[(0) * (C.strides[0]) + (4 * 0 + 0) * (C.strides[1])]);
C_reg[1 + 0] = vld1q_f32(&C.data[(0) * (C.strides[0]) + (4 * 1 + 0) * (C.strides[1])]);
float32x4_t A_vec;
for (int k = 0; k < 4; k++) {
  A_vec = vld1q_dup_f32(&A.data[(0) * (A.strides[0]) + (k + 0) * (A.strides[1])]);
}
float32x4_t A_t_vec[2];
for (int k = 0; k < 4; k++) {
  A_t_vec[0] = vld1q_f32(&A_t.data[(4 * 0 + 0) * (A_t.strides[0]) + (k + 0) * (A_t.strides[1])]);
  A_t_vec[1] = vld1q_f32(&A_t.data[(4 * 1 + 0) * (A_t.strides[0]) + (k + 0) * (A_t.strides[1])]);
}
for (int k = 0; k < 4; k++) {
  C_reg[0 + 0] = vmlaq_f32(C_reg[0 + 0], A_vec, A_t_vec[0]);
  C_reg[1 + 0] = vmlaq_f32(C_reg[1 + 0], A_vec, A_t_vec[1]);
}
vst1q_f32(&C.data[(0) * (C.strides[0]) + (4 * 0 + 0) * (C.strides[1])], C_reg[0 + 0]);
vst1q_f32(&C.data[(0) * (C.strides[0]) + (4 * 1 + 0) * (C.strides[1])], C_reg[1 + 0]);
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

// neon_microkernel_two_4(
//     A : [f32][4,4]  @DRAM,
//     A_t : [f32][4,4]  @DRAM,
//     C : [f32][4,4]  @DRAM
// )
void neon_microkernel_two_4( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 A_t, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(A_t.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[1];
C_reg[0 + 0] = vld1q_f32(&C.data[(0) * (C.strides[0]) + (4 * 0 + 0) * (C.strides[1])]);
float32x4_t A_vec;
for (int k = 0; k < 4; k++) {
  A_vec = vld1q_dup_f32(&A.data[(0) * (A.strides[0]) + (k + 0) * (A.strides[1])]);
}
float32x4_t A_t_vec[1];
for (int k = 0; k < 4; k++) {
  A_t_vec[0] = vld1q_f32(&A_t.data[(4 * 0 + 0) * (A_t.strides[0]) + (k + 0) * (A_t.strides[1])]);
}
for (int k = 0; k < 4; k++) {
  C_reg[0 + 0] = vmlaq_f32(C_reg[0 + 0], A_vec, A_t_vec[0]);
}
vst1q_f32(&C.data[(0) * (C.strides[0]) + (4 * 0 + 0) * (C.strides[1])], C_reg[0 + 0]);
}

// GEPP_syrk(
//     M : size,
//     A : [f32][M,4]  @DRAM,
//     A_t : [f32][M,4]  @DRAM,
//     C : [f32][M,M]  @DRAM
// )
void GEPP_syrk( c_code_str_Context *ctxt, int_fast32_t M, struct exo_win_2f32 A, struct exo_win_2f32 A_t, struct exo_win_2f32 C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(A_t.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
for (int i = 0; i < M; i++) {
  if (i == 0) {
    for (int j = 0; j < 1; j++) {
      for (int k = 0; k < 4; k++) {
        C.data[(0) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(0) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
      }
    }
  } else {
    if (i == 1) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 4; k++) {
          C.data[(1) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(1) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
        }
      }
    } else {
      if (i == 2) {
        for (int j = 0; j < 3; j++) {
          for (int k = 0; k < 4; k++) {
            C.data[(2) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(2) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
          }
        }
      } else {
        if (i == 3) {
          neon_microkernel_two_4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(3) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(3) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
        } else {
          if (i == 4) {
            neon_microkernel_two_4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(4) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(4) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
            for (int j = 0; j < 1; j++) {
              for (int k = 0; k < 4; k++) {
                C.data[(4) * (C.strides[0]) + (j + 4) * (C.strides[1])] += A.data[(4) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j + 4) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
              }
            }
          } else {
            if (i == 5) {
              neon_microkernel_two_4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(5) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(5) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
              for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 4; k++) {
                  C.data[(5) * (C.strides[0]) + (j + 4) * (C.strides[1])] += A.data[(5) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j + 4) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
                }
              }
            } else {
              if (i == 6) {
                neon_microkernel_two_4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(6) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(6) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                for (int j = 0; j < 3; j++) {
                  for (int k = 0; k < 4; k++) {
                    C.data[(6) * (C.strides[0]) + (j + 4) * (C.strides[1])] += A.data[(6) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j + 4) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
                  }
                }
              } else {
                if (i == 7) {
                  neon_microkernel_two_4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(7) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(7) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                  neon_microkernel_two_4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(7) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(4) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(7) * (C.strides[0]) + (4) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                } else {
                  if (i == 8) {
                    neon_microkernel_two_8(ctxt,(struct exo_win_2f32){ (float*)&A.data[(8) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(8) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                    for (int j = 0; j < 1; j++) {
                      for (int k = 0; k < 4; k++) {
                        C.data[(8) * (C.strides[0]) + (j + 8) * (C.strides[1])] += A.data[(8) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j + 8) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
                      }
                    }
                  } else {
                    if (i == 9) {
                      neon_microkernel_two_8(ctxt,(struct exo_win_2f32){ (float*)&A.data[(9) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(9) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                      for (int j = 0; j < 2; j++) {
                        for (int k = 0; k < 4; k++) {
                          C.data[(9) * (C.strides[0]) + (j + 8) * (C.strides[1])] += A.data[(9) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j + 8) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
                        }
                      }
                    } else {
                      if (i == 10) {
                        neon_microkernel_two_8(ctxt,(struct exo_win_2f32){ (float*)&A.data[(10) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(10) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                        for (int j = 0; j < 3; j++) {
                          for (int k = 0; k < 4; k++) {
                            C.data[(10) * (C.strides[0]) + (j + 8) * (C.strides[1])] += A.data[(10) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j + 8) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
                          }
                        }
                      } else {
                        if (i == 11) {
                          neon_microkernel_two_8(ctxt,(struct exo_win_2f32){ (float*)&A.data[(11) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(11) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                          neon_microkernel_two_4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(11) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(8) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(11) * (C.strides[0]) + (8) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                        } else {
                          if (i == 12) {
                            neon_microkernel_two_12(ctxt,(struct exo_win_2f32){ (float*)&A.data[(12) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(12) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                            for (int j = 0; j < 1; j++) {
                              for (int k = 0; k < 4; k++) {
                                C.data[(12) * (C.strides[0]) + (j + 12) * (C.strides[1])] += A.data[(12) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j + 12) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
                              }
                            }
                          } else {
                            if (i == 13) {
                              neon_microkernel_two_12(ctxt,(struct exo_win_2f32){ (float*)&A.data[(13) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(13) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                              for (int j = 0; j < 2; j++) {
                                for (int k = 0; k < 4; k++) {
                                  C.data[(13) * (C.strides[0]) + (j + 12) * (C.strides[1])] += A.data[(13) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j + 12) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
                                }
                              }
                            } else {
                              if (i == 14) {
                                neon_microkernel_two_12(ctxt,(struct exo_win_2f32){ (float*)&A.data[(14) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(14) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                for (int j = 0; j < 3; j++) {
                                  for (int k = 0; k < 4; k++) {
                                    C.data[(14) * (C.strides[0]) + (j + 12) * (C.strides[1])] += A.data[(14) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j + 12) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
                                  }
                                }
                              } else {
                                if (i == 15) {
                                  neon_microkernel_two_12(ctxt,(struct exo_win_2f32){ (float*)&A.data[(15) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(15) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                  neon_microkernel_two_4(ctxt,(struct exo_win_2f32){ (float*)&A.data[(15) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(12) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(15) * (C.strides[0]) + (12) * (C.strides[1])], { C.strides[0], C.strides[1] } });
                                } else {
                                  for (int j = 0; j < i + 1; j++) {
                                    for (int k = 0; k < 4; k++) {
                                      C.data[(i) * (C.strides[0]) + (j) * (C.strides[1])] += A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])] * A_t.data[(j) * (A_t.strides[0]) + (k) * (A_t.strides[1])];
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

// exo_syrk(
//     M : size,
//     K : size,
//     A : f32[M,K]  @DRAM,
//     A_t : f32[M,K]  @DRAM,
//     C : f32[M,M]  @DRAM
// )
void exo_syrk( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t K, float* A, float* A_t, float* C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(K >= 1);
EXO_ASSUME(1 == 1);
EXO_ASSUME(1 == 1);
EXO_ASSUME(1 == 1);
for (int ki = 0; ki < ((K) / (4)); ki++) {
  GEPP_syrk(ctxt,M,(struct exo_win_2f32){ (float*)&A[(0) * (K) + (4 * ki) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&A_t[(0) * (K) + (4 * ki) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&C[(0) * (M) + (0) * (1)], { M, 1 } });
}
if (K % 4 > 0) {
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < i + 1; j++) {
      for (int ko = 0; ko < K % 4; ko++) {
        C[(i) * (M) + (j) * (1)] += A[(i) * (K) + (ko + ((K) / (4)) * 4) * (1)] * A_t[(j) * (K) + (ko + ((K) / (4)) * 4) * (1)];
      }
    }
  }
}
}
