
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

#include <immintrin.h>

#include <stdio.h>
#include <stdlib.h>


// microkernel_2x16_1(
//     K : size,
//     A : [f32][2,K]  @DRAM,
//     B : [f32][K,16]  @DRAM,
//     C : [f32][2,16]  @DRAM
// )
void microkernel_2x16_1( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
__m512 C_reg[2][1];
for (int i = 0; i < 2; i++) {
  for (int jo = 0; jo < 1; jo++) {
    C_reg[i][jo] = _mm512_loadu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  for (int i = 0; i < 2; i++) {
    __m512 A_vec;
    (A_vec) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
    for (int jo = 0; jo < 1; jo++) {
      __m512 B_vec;
      B_vec = _mm512_loadu_ps(&B.data[(k) * (B.strides[0]) + (16 * jo) * (B.strides[1])]);
      C_reg[i][jo] = _mm512_fmadd_ps((A_vec), (B_vec), C_reg[i][jo]);
    }
  }
}
for (int i = 0; i < 2; i++) {
  for (int jo = 0; jo < 1; jo++) {
    _mm512_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}


/* relying on the following instruction...
mm512_fmadd_ps(A,B,C)
{C_data} = _mm512_fmadd_ps({A}, {B}, {C_data});
*/


/* relying on the following instruction...
mm512_storeu_ps(dst,src)
_mm512_storeu_ps(&{dst_data}, {src_data});
*/


/* relying on the following instruction...
mm512_set1_ps(dst,src)
{dst} = _mm512_set1_ps({src_data});
*/


/* relying on the following instruction...
mm512_loadu_ps(dst,src)
{dst_data} = _mm512_loadu_ps(&{src_data});
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
__m512 C_reg[4][1];
for (int i = 0; i < 4; i++) {
  for (int jo = 0; jo < 1; jo++) {
    C_reg[i][jo] = _mm512_loadu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  for (int i = 0; i < 4; i++) {
    __m512 A_vec;
    (A_vec) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
    for (int jo = 0; jo < 1; jo++) {
      __m512 B_vec;
      B_vec = _mm512_loadu_ps(&B.data[(k) * (B.strides[0]) + (16 * jo) * (B.strides[1])]);
      C_reg[i][jo] = _mm512_fmadd_ps((A_vec), (B_vec), C_reg[i][jo]);
    }
  }
}
for (int i = 0; i < 4; i++) {
  for (int jo = 0; jo < 1; jo++) {
    _mm512_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])], C_reg[i][jo]);
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
  for (int iii = 0; iii < ((M % 4) / (2)); iii++) {
    microkernel_2x16_1(ctxt,K,(struct exo_win_2f32){ (float*)&A[(4 * ((M) / (4)) + 2 * iii) * (K) + (0) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B[(0) * (N) + (16 * ji) * (1)], { N, 1 } },(struct exo_win_2f32){ (float*)&C[(4 * ((M) / (4)) + 2 * iii) * (N) + (16 * ji) * (1)], { N, 1 } });
  }
  for (int ioo = 0; ioo < M % 4 % 2; ioo++) {
    for (int jo = 0; jo < 16; jo++) {
      for (int k = 0; k < K; k++) {
        C[(ioo + ((M % 4) / (2)) * 2 + ((M) / (4)) * 4) * (N) + (16 * ji + jo) * (1)] += A[(ioo + ((M % 4) / (2)) * 2 + ((M) / (4)) * 4) * (K) + (k) * (1)] * B[(k) * (N) + (16 * ji + jo) * (1)];
      }
    }
  }
  free(B_strip);
}
for (int ii = 0; ii < ((M) / (4)); ii++) {
  for (int io = 0; io < 4; io++) {
    for (int jo = 0; jo < N % 16; jo++) {
      for (int k = 0; k < K; k++) {
        C[(4 * ii + io) * (N) + (jo + ((N) / (16)) * 16) * (1)] += A[(4 * ii + io) * (K) + (k) * (1)] * B[(k) * (N) + (jo + ((N) / (16)) * 16) * (1)];
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
