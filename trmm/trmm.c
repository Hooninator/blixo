
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
typedef struct c_code_str_Context { 

} c_code_str_Context;


// GEPP_trmm_intermediate(
//     N : size,
//     A : [f32][8,8]  @DRAM,
//     B : [f32][8,N]  @DRAM
// )
void GEPP_trmm_intermediate( c_code_str_Context *ctxt, int_fast32_t N, struct exo_win_2f32 A, struct exo_win_2f32 B );


static int _floor_div(int num, int quot) {
  int off = (num>=0)? 0 : quot-1;
  return (num-off)/quot;
}

static int8_t _clamp_32to8(int32_t x) {
  return (x < -128)? -128 : ((x > 127)? 127 : x);
}

#include <stdio.h>
#include <stdlib.h>


// GEPP_trmm_intermediate(
//     N : size,
//     A : [f32][8,8]  @DRAM,
//     B : [f32][8,N]  @DRAM
// )
void GEPP_trmm_intermediate( c_code_str_Context *ctxt, int_fast32_t N, struct exo_win_2f32 A, struct exo_win_2f32 B ) {
for (int k = 0; k < 8; k++) {
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < k; i++) {
      B.data[(i) * (B.strides[0]) + (j) * (B.strides[1])] += B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])] * A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])];
    }
    B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])] = A.data[(k) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (j) * (B.strides[1])];
  }
}
}

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

typedef struct c_code_str_Context { 

} c_code_str_Context;


// exo_trmm(
//     M : size,
//     N : size,
//     A : f32[M,M]  @DRAM,
//     B : f32[M,N]  @DRAM
// )
void exo_trmm( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, float* A, float* B );


static int _floor_div(int num, int quot) {
  int off = (num>=0)? 0 : quot-1;
  return (num-off)/quot;
}

static int8_t _clamp_32to8(int32_t x) {
  return (x < -128)? -128 : ((x > 127)? 127 : x);
}

#include <stdio.h>
#include <stdlib.h>


// exo_trmm(
//     M : size,
//     N : size,
//     A : f32[M,M]  @DRAM,
//     B : f32[M,N]  @DRAM
// )
void exo_trmm( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, float* A, float* B ) {
for (int ki = 0; ki < ((M) / (8)); ki++) {
  if (ki == 0) {
    for (int ko = 0; ko < 8; ko++) {
      for (int j = 0; j < N; j++) {
        for (int i = 0; i < ko; i++) {
          B[(i) * (N) + (j) * (1)] += B[(ko) * (N) + (j) * (1)] * A[(i) * (M) + (ko) * (1)];
        }
        B[(ko) * (N) + (j) * (1)] = A[(ko) * (M) + (ko) * (1)] * B[(ko) * (N) + (j) * (1)];
      }
    }
  } else {
    if (ki == 1) {
      for (int ko = 0; ko < 8; ko++) {
        for (int j = 0; j < N; j++) {
          for (int i = 0; i < 8 + ko; i++) {
            B[(i) * (N) + (j) * (1)] += B[(8 + ko) * (N) + (j) * (1)] * A[(i) * (M) + (8 + ko) * (1)];
          }
          B[(8 + ko) * (N) + (j) * (1)] = A[(8 + ko) * (M) + (8 + ko) * (1)] * B[(8 + ko) * (N) + (j) * (1)];
        }
      }
    } else {
      for (int ko = 0; ko < 8; ko++) {
        for (int j = 0; j < N; j++) {
          for (int i = 0; i < 8 * ki + ko; i++) {
            B[(i) * (N) + (j) * (1)] += B[(8 * ki + ko) * (N) + (j) * (1)] * A[(i) * (M) + (8 * ki + ko) * (1)];
          }
          B[(8 * ki + ko) * (N) + (j) * (1)] = A[(8 * ki + ko) * (M) + (8 * ki + ko) * (1)] * B[(8 * ki + ko) * (N) + (j) * (1)];
        }
      }
    }
  }
}
if (M % 8 > 0) {
  for (int ko = 0; ko < M % 8; ko++) {
    for (int j = 0; j < N; j++) {
      for (int i = 0; i < ko + ((M) / (8)) * 8; i++) {
        B[(i) * (N) + (j) * (1)] += B[(ko + ((M) / (8)) * 8) * (N) + (j) * (1)] * A[(i) * (M) + (ko + ((M) / (8)) * 8) * (1)];
      }
      B[(ko + ((M) / (8)) * 8) * (N) + (j) * (1)] = A[(ko + ((M) / (8)) * 8) * (M) + (ko + ((M) / (8)) * 8) * (1)] * B[(ko + ((M) / (8)) * 8) * (N) + (j) * (1)];
    }
  }
}
}
