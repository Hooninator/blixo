
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

// sgemm_kernel_avx512_6x4(
//     K : size,
//     A : [f32][6,K]  @DRAM,
//     B : [f32][K,16]  @DRAM,
//     C : [f32][6,16]  @DRAM
// )
void sgemm_kernel_avx512_6x4( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
float32x4_t C_reg[6][4];
for (int i = 0; i < 6; i++) {
  for (int jo = 0; jo < 4; jo++) {
    C_reg[i][jo] = vld1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  for (int i = 0; i < 6; i++) {
    float32x4_t A_vec;
    A_vec = vld1q_dup_f32(&A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
    for (int jo = 0; jo < 4; jo++) {
      float32x4_t B_vec;
      B_vec = vld1q_f32(&B.data[(k) * (B.strides[0]) + (4 * jo) * (B.strides[1])]);
      C_reg[i][jo] = vmlaq_f32(C_reg[i][jo], A_vec, B_vec);
    }
  }
}
for (int i = 0; i < 6; i++) {
  for (int jo = 0; jo < 4; jo++) {
    vst1q_f32(&C.data[(i) * (C.strides[0]) + (4 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// sgemm_above_kernel(
//     M : size,
//     N : size,
//     K : size,
//     A : [f32][M,K]  @DRAM,
//     B : [f32][K,N]  @DRAM,
//     C : [f32][M,N]  @DRAM
// )
void sgemm_above_kernel( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(N >= 1);
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
for (int io = 0; io < ((M) / (6)); io++) {
  for (int jo = 0; jo < ((N) / (16)); jo++) {
    sgemm_kernel_avx512_6x4(ctxt,K,(struct exo_win_2f32){ (float*)&A.data[(6 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (16 * jo) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(6 * io) * (C.strides[0]) + (16 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
if (N % 16 > 0) {
  for (int io = 0; io < ((M) / (6)); io++) {
    for (int k = 0; k < K; k++) {
      for (int ii = 0; ii < 6; ii++) {
        for (int ji = 0; ji < N % 16; ji++) {
          C.data[(6 * io + ii) * (C.strides[0]) + (ji + ((N) / (16)) * 16) * (C.strides[1])] += A.data[(6 * io + ii) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + ((N) / (16)) * 16) * (B.strides[1])];
        }
      }
    }
  }
}
if (M % 6 > 0) {
  for (int jo = 0; jo < ((N) / (16)); jo++) {
    for (int k = 0; k < K; k++) {
      for (int ii = 0; ii < M % 6; ii++) {
        for (int ji = 0; ji < 16; ji++) {
          C.data[(ii + ((M) / (6)) * 6) * (C.strides[0]) + (16 * jo + ji) * (C.strides[1])] += A.data[(ii + ((M) / (6)) * 6) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (16 * jo + ji) * (B.strides[1])];
        }
      }
    }
  }
  if (N % 16 > 0) {
    for (int k = 0; k < K; k++) {
      for (int ii = 0; ii < M % 6; ii++) {
        for (int ji = 0; ji < N % 16; ji++) {
          C.data[(ii + ((M) / (6)) * 6) * (C.strides[0]) + (ji + ((N) / (16)) * 16) * (C.strides[1])] += A.data[(ii + ((M) / (6)) * 6) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + ((N) / (16)) * 16) * (B.strides[1])];
        }
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
static float A1_cache[264 * 512];
static float B1_cache[512 * 16];
for (int ko = 0; ko < ((K) / (512)); ko++) {
  for (int io = 0; io < ((M) / (264)); io++) {
    for (int i0 = 0; i0 < 264; i0++) {
      for (int i1 = 0; i1 < 512; i1++) {
        A1_cache[(i0) * (512) + (i1) * (1)] = A[(264 * io + i0) * (K) + (512 * ko + i1) * (1)];
      }
    }
    for (int jo = 0; jo < ((N) / (16)); jo++) {
      for (int i0 = 0; i0 < 512; i0++) {
        for (int i1 = 0; i1 < 16; i1++) {
          B1_cache[(i0) * (16) + (i1) * (1)] = B[(512 * ko + i0) * (N) + (16 * jo + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,264,16,512,(struct exo_win_2f32){ (float*)&A1_cache[(0) * (512) + (0) * (1)], { 512, 1 } },(struct exo_win_2f32){ (float*)&B1_cache[(0) * (16) + (0) * (1)], { 16, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * io) * (N) + (16 * jo) * (1)], { N, 1 } });
    }
  }
}
if (N % 16 > 0) {
  for (int ko = 0; ko < ((K) / (512)); ko++) {
    static float B2_cache[512 * 16];
    for (int i0 = 0; i0 < 512; i0++) {
      for (int i1 = 0; i1 < N - 16 * ((N) / (16)); i1++) {
        B2_cache[(i0) * (16) + (i1) * (1)] = B[(512 * ko + i0) * (N) + (16 * ((N) / (16)) + i1) * (1)];
      }
    }
    for (int io = 0; io < ((M) / (264)); io++) {
      sgemm_above_kernel(ctxt,264,N % 16,512,(struct exo_win_2f32){ (float*)&A[(264 * io) * (K) + (512 * ko) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B2_cache[(0) * (16) + (0) * (1)], { 16, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * io) * (N) + (16 * ((N) / (16))) * (1)], { N, 1 } });
    }
  }
}
if (M % 264 > 0) {
  for (int ko = 0; ko < ((K) / (512)); ko++) {
    for (int jo = 0; jo < ((N) / (16)); jo++) {
      static float B3_cache[512 * 16];
      for (int i0 = 0; i0 < 512; i0++) {
        for (int i1 = 0; i1 < 16; i1++) {
          B3_cache[(i0) * (16) + (i1) * (1)] = B[(512 * ko + i0) * (N) + (16 * jo + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,M % 264,16,512,(struct exo_win_2f32){ (float*)&A[(264 * ((M) / (264))) * (K) + (512 * ko) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B3_cache[(0) * (16) + (0) * (1)], { 16, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * ((M) / (264))) * (N) + (16 * jo) * (1)], { N, 1 } });
    }
  }
}
if (M % 264 > 0) {
  if (N % 16 > 0) {
    for (int ko = 0; ko < ((K) / (512)); ko++) {
      static float B4_cache[512 * 16];
      for (int i0 = 0; i0 < 512; i0++) {
        for (int i1 = 0; i1 < N - 16 * ((N) / (16)); i1++) {
          B4_cache[(i0) * (16) + (i1) * (1)] = B[(512 * ko + i0) * (N) + (16 * ((N) / (16)) + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,M % 264,N % 16,512,(struct exo_win_2f32){ (float*)&A[(264 * ((M) / (264))) * (K) + (512 * ko) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B4_cache[(0) * (16) + (0) * (1)], { 16, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * ((M) / (264))) * (N) + (16 * ((N) / (16))) * (1)], { N, 1 } });
    }
  }
}
if (K % 512 > 0) {
  for (int io = 0; io < ((M) / (264)); io++) {
    for (int jo = 0; jo < ((N) / (16)); jo++) {
      static float B5_cache[512 * 16];
      for (int i0 = 0; i0 < K - 512 * ((K) / (512)); i0++) {
        for (int i1 = 0; i1 < 16; i1++) {
          B5_cache[(i0) * (16) + (i1) * (1)] = B[(512 * ((K) / (512)) + i0) * (N) + (16 * jo + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,264,16,K % 512,(struct exo_win_2f32){ (float*)&A[(264 * io) * (K) + (512 * ((K) / (512))) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B5_cache[(0) * (16) + (0) * (1)], { 16, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * io) * (N) + (16 * jo) * (1)], { N, 1 } });
    }
  }
}
if (K % 512 > 0) {
  if (N % 16 > 0) {
    for (int io = 0; io < ((M) / (264)); io++) {
      static float B6_cache[512 * 16];
      for (int i0 = 0; i0 < K - 512 * ((K) / (512)); i0++) {
        for (int i1 = 0; i1 < N - 16 * ((N) / (16)); i1++) {
          B6_cache[(i0) * (16) + (i1) * (1)] = B[(512 * ((K) / (512)) + i0) * (N) + (16 * ((N) / (16)) + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,264,N % 16,K % 512,(struct exo_win_2f32){ (float*)&A[(264 * io) * (K) + (512 * ((K) / (512))) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B6_cache[(0) * (16) + (0) * (1)], { 16, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * io) * (N) + (16 * ((N) / (16))) * (1)], { N, 1 } });
    }
  }
}
if (K % 512 > 0) {
  if (M % 264 > 0) {
    for (int jo = 0; jo < ((N) / (16)); jo++) {
      static float B7_cache[512 * 16];
      for (int i0 = 0; i0 < K - 512 * ((K) / (512)); i0++) {
        for (int i1 = 0; i1 < 16; i1++) {
          B7_cache[(i0) * (16) + (i1) * (1)] = B[(512 * ((K) / (512)) + i0) * (N) + (16 * jo + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,M % 264,16,K % 512,(struct exo_win_2f32){ (float*)&A[(264 * ((M) / (264))) * (K) + (512 * ((K) / (512))) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B7_cache[(0) * (16) + (0) * (1)], { 16, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * ((M) / (264))) * (N) + (16 * jo) * (1)], { N, 1 } });
    }
  }
}
if (K % 512 > 0) {
  if (M % 264 > 0) {
    if (N % 16 > 0) {
      static float B8_cache[512 * 16];
      for (int i0 = 0; i0 < K - 512 * ((K) / (512)); i0++) {
        for (int i1 = 0; i1 < N - 16 * ((N) / (16)); i1++) {
          B8_cache[(i0) * (16) + (i1) * (1)] = B[(512 * ((K) / (512)) + i0) * (N) + (16 * ((N) / (16)) + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,M % 264,N % 16,K % 512,(struct exo_win_2f32){ (float*)&A[(264 * ((M) / (264))) * (K) + (512 * ((K) / (512))) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B8_cache[(0) * (16) + (0) * (1)], { 16, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * ((M) / (264))) * (N) + (16 * ((N) / (16))) * (1)], { N, 1 } });
    }
  }
}
}
