
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


// SYRK(
//     M : size,
//     K : size,
//     A : f32[M,K]  @DRAM,
//     C : f32[M,K]  @DRAM
// )
void SYRK( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t K, float* A, float* C );


static int _floor_div(int num, int quot) {
  int off = (num>=0)? 0 : quot-1;
  return (num-off)/quot;
}

static int8_t _clamp_32to8(int32_t x) {
  return (x < -128)? -128 : ((x > 127)? 127 : x);
}

#include <stdio.h>
#include <stdlib.h>


// SYRK(
//     M : size,
//     K : size,
//     A : f32[M,K]  @DRAM,
//     C : f32[M,K]  @DRAM
// )
void SYRK( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t K, float* A, float* C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(K >= 1);
EXO_ASSUME(K == M);
EXO_ASSUME(1 == 1);
EXO_ASSUME(1 == 1);
for (int j = 0; j < M; j++) {
  for (int i = 0; i < j + 1; i++) {
    for (int k = 0; k < K; k++) {
      C[(i) * (K) + (j) * (1)] += A[(k) * (K) + (i) * (1)] * A[(k) * (K) + (j) * (1)];
    }
  }
}
}
