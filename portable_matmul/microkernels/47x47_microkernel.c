
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


// SGEMM(
//     M : size,
//     N : size,
//     K : size,
//     A : f32[M,K]  @DRAM,
//     B : f32[K,N]  @DRAM,
//     C : f32[M,N]  @DRAM
// )
void SGEMM( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, int_fast32_t K, float* A, float* B, float* C );


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

// microkernel_3x16_1(
//     K : size,
//     A : [f32][3,K]  @DRAM,
//     B : [f32][K,16]  @DRAM,
//     C : [f32][3,16]  @DRAM
// )
void microkernel_3x16_1( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[3][4];
for (int i = 0; i < 3; i++) {
  for (int jo = 0; jo < 4; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  float32x4_t A_vec[3];
  for (int i = 0; i < 3; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[4];
  for (int jo = 0; jo < 4; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 3; i++) {
    for (int jo = 0; jo < 4; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 3; i++) {
  for (int jo = 0; jo < 4; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// microkernel_4x12_2(
//     K : size,
//     A : [f32][4,K]  @DRAM,
//     B : [f32][K,12]  @DRAM,
//     C : [f32][4,12]  @DRAM
// )
void microkernel_4x12_2( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[4][3];
for (int i = 0; i < 4; i++) {
  for (int jo = 0; jo < 3; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  float32x4_t A_vec[4];
  for (int i = 0; i < 4; i++) {
    A_vec[i] = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
  }
  float32x4_t B_vec[3];
  for (int jo = 0; jo < 3; jo++) {
    B_vec[jo] = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
  }
  for (int i = 0; i < 4; i++) {
    for (int jo = 0; jo < 3; jo++) {
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec[i], B_vec[jo]);
    }
  }
}
for (int i = 0; i < 4; i++) {
  for (int jo = 0; jo < 3; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// microkernel_4x3x44_3(
//     A : [f32][4,44]  @DRAM,
//     B : [f32][44,3]  @DRAM,
//     C : [f32][4,3]  @DRAM
// )
void microkernel_4x3x44_3( c_code_str_Context *ctxt, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[44][1];
for (int j = 0; j < 3; j++) {
  for (int k = 0; k < 44; k++) {
    for (int io = 0; io < 1; io++) {
      C_reg[k][io] = vld1q_f32(&C.data[(4 * io) * (C.strides[0]) + (j) * (C.strides[1])]);
    }
  }
}
for (int j = 0; j < 3; j++) {
  float32x4_t A_vec[44][1];
  float32x4_t B_vec[44];
  for (int k = 0; k < 44; k++) {
    for (int io = 0; io < 1; io++) {
      A_vec[k][io] = vld1q_f32(&A.data[(4 * io) * (A.strides[0]) + (k) * (A.strides[1])]);
      B_vec[k] = vld1q_dup_f32(&B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])]);
      C_reg[k][io] = vmlaq_f32(C_reg[k][io], A_vec[k][io], B_vec[k]);
    }
  }
}
for (int j = 0; j < 3; j++) {
  for (int k = 0; k < 44; k++) {
    for (int io = 0; io < 1; io++) {
      vst1q_f32(&C.data[(4 * io) * (C.strides[0]) + (j) * (C.strides[1])], C_reg[k][io]);
    }
  }
}
}


/* relying on the following instruction...
neon_broadcast_4xf32(dst,src)
{dst_data} = vld1q_dup_f32(&{src_data});
*/


/* relying on the following instruction...
neon_vst_4xf32(dst,src)
vst1q_f32(&{dst_data}, {src_data});
*/


/* relying on the following instruction...
neon_vfmadd_4xf32_4xf32(dst,lhs,rhs)
{dst_data} = vmlaq_f32({dst_data}, {lhs_data}, {rhs_data});
*/


/* relying on the following instruction...
neon_vld_4xf32(dst,src)
{dst_data} = vld1q_f32(&{src_data});
*/

// microkernel_4x16_0(
//     K : size,
//     A : [f32][4,K]  @DRAM,
//     B : [f32][K,16]  @DRAM,
//     C : [f32][4,16]  @DRAM
// )
void microkernel_4x16_0( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[4][4];
for (int i = 0; i < 4; i++) {
  for (int jo = 0; jo < 4; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
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

// SGEMM(
//     M : size,
//     N : size,
//     K : size,
//     A : f32[M,K]  @DRAM,
//     B : f32[K,N]  @DRAM,
//     C : f32[M,N]  @DRAM
// )
void SGEMM( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, int_fast32_t K, float* A, float* B, float* C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(N >= 1);
EXO_ASSUME(K >= 1);
EXO_ASSUME(1 == 1);
EXO_ASSUME(1 == 1);
EXO_ASSUME(1 == 1);
for (int ji = 0; ji < ((N) / (16)); ji++) {
  float *B_strip = malloc(K * 16 * sizeof(*B_strip));
  for (int i0 = 0; i0 < K; i0++) {
    for (int i1 = 0; i1 < 16; i1++) {
      B_strip[(i0) * (16) + (i1) * (1)] = B[(i0) * (N) + (i1 + 16 * ji) * (1)];
    }
  }
  for (int ii = 0; ii < ((M) / (4)); ii++) {
    microkernel_4x16_0(ctxt,K,(struct exo_win_2f32){ (float*)&A[(4 * ii) * (K) + (0) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B_strip[(0) * (16) + (0) * (1)], { 16, 1 } },(struct exo_win_2f32){ (float*)&C[(4 * ii) * (N) + (16 * ji) * (1)], { N, 1 } });
  }
  for (int iii = 0; iii < ((M % 4) / (3)); iii++) {
    microkernel_3x16_1(ctxt,K,(struct exo_win_2f32){ (float*)&A[(4 * ((M) / (4)) + 3 * iii) * (K) + (0) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B[(0) * (N) + (16 * ji) * (1)], { N, 1 } },(struct exo_win_2f32){ (float*)&C[(4 * ((M) / (4)) + 3 * iii) * (N) + (16 * ji) * (1)], { N, 1 } });
  }
  for (int ioo = 0; ioo < M % 4 % 3; ioo++) {
    for (int jo = 0; jo < 16; jo++) {
      for (int k = 0; k < K; k++) {
        C[(ioo + ((M % 4) / (3)) * 3 + ((M) / (4)) * 4) * (N) + (16 * ji + jo) * (1)] += A[(ioo + ((M % 4) / (3)) * 3 + ((M) / (4)) * 4) * (K) + (k) * (1)] * B[(k) * (N) + (16 * ji + jo) * (1)];
      }
    }
  }
  free(B_strip);
}
for (int ii = 0; ii < ((M) / (4)); ii++) {
  for (int jii = 0; jii < ((N % 16) / (12)); jii++) {
    microkernel_4x12_2(ctxt,K,(struct exo_win_2f32){ (float*)&A[(4 * ii) * (K) + (0) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B[(0) * (N) + (16 * ((N) / (16)) + 12 * jii) * (1)], { N, 1 } },(struct exo_win_2f32){ (float*)&C[(4 * ii) * (N) + (16 * ((N) / (16)) + 12 * jii) * (1)], { N, 1 } });
  }
  for (int ko = 0; ko < ((K) / (44)); ko++) {
    for (int jiii = 0; jiii < ((N % 16 % 12) / (3)); jiii++) {
      microkernel_4x3x44_3(ctxt,(struct exo_win_2f32){ (float*)&A[(4 * ii) * (K) + (44 * ko) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B[(44 * ko) * (N) + (12 * ((N % 16) / (12)) + 16 * ((N) / (16)) + 3 * jiii) * (1)], { N, 1 } },(struct exo_win_2f32){ (float*)&C[(4 * ii) * (N) + (12 * ((N % 16) / (12)) + 16 * ((N) / (16)) + 3 * jiii) * (1)], { N, 1 } });
    }
    for (int jooo = 0; jooo < N % 16 % 12 % 3; jooo++) {
      for (int io = 0; io < 4; io++) {
        for (int ki = 0; ki < 44; ki++) {
          C[(4 * ii + io) * (N) + (jooo + ((N % 16 % 12) / (3)) * 3 + ((N % 16) / (12)) * 12 + ((N) / (16)) * 16) * (1)] += A[(4 * ii + io) * (K) + (44 * ko + ki) * (1)] * B[(44 * ko + ki) * (N) + (jooo + ((N % 16 % 12) / (3)) * 3 + ((N % 16) / (12)) * 12 + ((N) / (16)) * 16) * (1)];
        }
      }
    }
  }
  for (int jiii = 0; jiii < ((N % 16 % 12) / (3)); jiii++) {
    for (int jooo = 0; jooo < 3; jooo++) {
      for (int io = 0; io < 4; io++) {
        for (int ki = 0; ki < K % 44; ki++) {
          C[(4 * ii + io) * (N) + (3 * jiii + jooo + ((N % 16) / (12)) * 12 + ((N) / (16)) * 16) * (1)] += A[(4 * ii + io) * (K) + (ki + ((K) / (44)) * 44) * (1)] * B[(ki + ((K) / (44)) * 44) * (N) + (3 * jiii + jooo + ((N % 16) / (12)) * 12 + ((N) / (16)) * 16) * (1)];
        }
      }
    }
  }
  for (int jooo = 0; jooo < N % 16 % 12 % 3; jooo++) {
    for (int io = 0; io < 4; io++) {
      for (int ki = 0; ki < K % 44; ki++) {
        C[(4 * ii + io) * (N) + (jooo + ((N % 16 % 12) / (3)) * 3 + ((N % 16) / (12)) * 12 + ((N) / (16)) * 16) * (1)] += A[(4 * ii + io) * (K) + (ki + ((K) / (44)) * 44) * (1)] * B[(ki + ((K) / (44)) * 44) * (N) + (jooo + ((N % 16 % 12) / (3)) * 3 + ((N % 16) / (12)) * 12 + ((N) / (16)) * 16) * (1)];
      }
    }
  }
}
for (int io = 0; io < M % 4; io++) {
  for (int jo = 0; jo < N % 16; jo++) {
    for (int k = 0; k < K; k++) {
      C[(io + ((M) / (4)) * 4) * (N) + (jo + ((N) / (16)) * 16) * (1)] += A[(io + ((M) / (4)) * 4) * (K) + (k) * (1)] * B[(k) * (N) + (jo + ((N) / (16)) * 16) * (1)];
    }
  }
}
}
