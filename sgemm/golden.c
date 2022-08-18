
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

#include <immintrin.h>

#include <stdio.h>
#include <stdlib.h>


#include <stdio.h>
#include <stdlib.h>



/* relying on the following instruction...
mm512_mask_storeu_ps(N,dst,src)
_mm512_mask_storeu_ps(&{dst_data}, ((1 << {N}) - 1), {src_data});
*/


/* relying on the following instruction...
mm512_mask_set1_ps(N,dst,src)
{dst} = _mm512_set1_ps({src_data});
*/


/* relying on the following instruction...
mm512_maskz_loadu_ps(N,dst,src)
{dst_data} = _mm512_maskz_loadu_ps(((1 << {N}) - 1), &{src_data});
*/


/* relying on the following instruction...
mm512_mask_fmadd_ps(N,A,B,C)
{C_data} = _mm512_mask_fmadd_ps({A}, ((1 << {N}) - 1), {B}, {C_data});
*/

// right_panel_kernel_scheduled(
//     N : size,
//     K : size,
//     A : [f32][6,K]  @DRAM,
//     B : [f32][K,N]  @DRAM,
//     C : [f32][6,N]  @DRAM
// )
void right_panel_kernel_scheduled( c_code_str_Context *ctxt, int_fast32_t N, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(N >= 1);
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
EXO_ASSUME(((N) / (16)) < 4);
if (((N) / (16)) == 0) {
  __m512 C_reg[6][1];
  __m512 C_reg_1[6];
  for (int i = 0; i < 6; i++) {
    C_reg_1[i] = _mm512_maskz_loadu_ps(((1 << (N)) - 1), &C.data[(i) * (C.strides[0]) + (0) * (C.strides[1])]);
  }
  for (int k = 0; k < K; k++) {
    for (int i = 0; i < 6; i++) {
      __m512 A_reg2;
      (A_reg2) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
      __m512 B_reg2;
      B_reg2 = _mm512_maskz_loadu_ps(((1 << (N)) - 1), &B.data[(k) * (B.strides[0]) + (0) * (B.strides[1])]);
      C_reg_1[i] = _mm512_mask_fmadd_ps((A_reg2), ((1 << (N)) - 1), (B_reg2), C_reg_1[i]);
    }
  }
  for (int i = 0; i < 6; i++) {
    _mm512_mask_storeu_ps(&C.data[(i) * (C.strides[0]) + (0) * (C.strides[1])], ((1 << (N)) - 1), C_reg_1[i]);
  }
} else {
  if (((N) / (16)) == 1) {
    __m512 C_reg[6][2];
    __m512 C_reg_1[6];
    for (int i = 0; i < 6; i++) {
      for (int jo = 0; jo < 1; jo++) {
        C_reg[i][jo] = _mm512_loadu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])]);
      }
      C_reg_1[i] = _mm512_maskz_loadu_ps(((1 << (N % 16)) - 1), &C.data[(i) * (C.strides[0]) + (16) * (C.strides[1])]);
    }
    for (int k = 0; k < K; k++) {
      for (int i = 0; i < 6; i++) {
        for (int jo = 0; jo < 1; jo++) {
          __m512 A_reg;
          (A_reg) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
          __m512 B_reg;
          B_reg = _mm512_loadu_ps(&B.data[(k) * (B.strides[0]) + (16 * jo) * (B.strides[1])]);
          C_reg[i][jo] = _mm512_fmadd_ps((A_reg), (B_reg), C_reg[i][jo]);
        }
        __m512 A_reg2;
        (A_reg2) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
        __m512 B_reg2;
        B_reg2 = _mm512_maskz_loadu_ps(((1 << (N % 16)) - 1), &B.data[(k) * (B.strides[0]) + (16) * (B.strides[1])]);
        C_reg_1[i] = _mm512_mask_fmadd_ps((A_reg2), ((1 << (N % 16)) - 1), (B_reg2), C_reg_1[i]);
      }
    }
    for (int i = 0; i < 6; i++) {
      for (int jo = 0; jo < 1; jo++) {
        _mm512_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])], C_reg[i][jo]);
      }
      _mm512_mask_storeu_ps(&C.data[(i) * (C.strides[0]) + (16) * (C.strides[1])], ((1 << (N % 16)) - 1), C_reg_1[i]);
    }
  } else {
    if (((N) / (16)) == 2) {
      __m512 C_reg[6][3];
      __m512 C_reg_1[6];
      for (int i = 0; i < 6; i++) {
        for (int jo = 0; jo < 2; jo++) {
          C_reg[i][jo] = _mm512_loadu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])]);
        }
        C_reg_1[i] = _mm512_maskz_loadu_ps(((1 << (N % 16)) - 1), &C.data[(i) * (C.strides[0]) + (32) * (C.strides[1])]);
      }
      for (int k = 0; k < K; k++) {
        for (int i = 0; i < 6; i++) {
          for (int jo = 0; jo < 2; jo++) {
            __m512 A_reg;
            (A_reg) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
            __m512 B_reg;
            B_reg = _mm512_loadu_ps(&B.data[(k) * (B.strides[0]) + (16 * jo) * (B.strides[1])]);
            C_reg[i][jo] = _mm512_fmadd_ps((A_reg), (B_reg), C_reg[i][jo]);
          }
          __m512 A_reg2;
          (A_reg2) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
          __m512 B_reg2;
          B_reg2 = _mm512_maskz_loadu_ps(((1 << (N % 16)) - 1), &B.data[(k) * (B.strides[0]) + (32) * (B.strides[1])]);
          C_reg_1[i] = _mm512_mask_fmadd_ps((A_reg2), ((1 << (N % 16)) - 1), (B_reg2), C_reg_1[i]);
        }
      }
      for (int i = 0; i < 6; i++) {
        for (int jo = 0; jo < 2; jo++) {
          _mm512_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])], C_reg[i][jo]);
        }
        _mm512_mask_storeu_ps(&C.data[(i) * (C.strides[0]) + (32) * (C.strides[1])], ((1 << (N % 16)) - 1), C_reg_1[i]);
      }
    } else {
      if (((N) / (16)) == 3) {
        __m512 C_reg[6][4];
        __m512 C_reg_1[6];
        for (int i = 0; i < 6; i++) {
          for (int jo = 0; jo < 3; jo++) {
            C_reg[i][jo] = _mm512_loadu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])]);
          }
          C_reg_1[i] = _mm512_maskz_loadu_ps(((1 << (N % 16)) - 1), &C.data[(i) * (C.strides[0]) + (48) * (C.strides[1])]);
        }
        for (int k = 0; k < K; k++) {
          for (int i = 0; i < 6; i++) {
            for (int jo = 0; jo < 3; jo++) {
              __m512 A_reg;
              (A_reg) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
              __m512 B_reg;
              B_reg = _mm512_loadu_ps(&B.data[(k) * (B.strides[0]) + (16 * jo) * (B.strides[1])]);
              C_reg[i][jo] = _mm512_fmadd_ps((A_reg), (B_reg), C_reg[i][jo]);
            }
            __m512 A_reg2;
            (A_reg2) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
            __m512 B_reg2;
            B_reg2 = _mm512_maskz_loadu_ps(((1 << (N % 16)) - 1), &B.data[(k) * (B.strides[0]) + (48) * (B.strides[1])]);
            C_reg_1[i] = _mm512_mask_fmadd_ps((A_reg2), ((1 << (N % 16)) - 1), (B_reg2), C_reg_1[i]);
          }
        }
        for (int i = 0; i < 6; i++) {
          for (int jo = 0; jo < 3; jo++) {
            _mm512_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])], C_reg[i][jo]);
          }
          _mm512_mask_storeu_ps(&C.data[(i) * (C.strides[0]) + (48) * (C.strides[1])], ((1 << (N % 16)) - 1), C_reg_1[i]);
        }
      } else {
        __m512 C_reg[6][(((N) / (16)) + 1)];
        __m512 C_reg_1[6];
        for (int i = 0; i < 6; i++) {
          for (int jo = 0; jo < ((N) / (16)); jo++) {
            C_reg[i][jo] = _mm512_loadu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])]);
          }
          C_reg_1[i] = _mm512_maskz_loadu_ps(((1 << (N % 16)) - 1), &C.data[(i) * (C.strides[0]) + (16 * ((N) / (16))) * (C.strides[1])]);
        }
        for (int k = 0; k < K; k++) {
          for (int i = 0; i < 6; i++) {
            for (int jo = 0; jo < ((N) / (16)); jo++) {
              __m512 A_reg;
              (A_reg) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
              __m512 B_reg;
              B_reg = _mm512_loadu_ps(&B.data[(k) * (B.strides[0]) + (16 * jo) * (B.strides[1])]);
              C_reg[i][jo] = _mm512_fmadd_ps((A_reg), (B_reg), C_reg[i][jo]);
            }
            __m512 A_reg2;
            (A_reg2) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
            __m512 B_reg2;
            B_reg2 = _mm512_maskz_loadu_ps(((1 << (N % 16)) - 1), &B.data[(k) * (B.strides[0]) + (16 * ((N) / (16))) * (B.strides[1])]);
            C_reg_1[i] = _mm512_mask_fmadd_ps((A_reg2), ((1 << (N % 16)) - 1), (B_reg2), C_reg_1[i]);
          }
        }
        for (int i = 0; i < 6; i++) {
          for (int jo = 0; jo < ((N) / (16)); jo++) {
            _mm512_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])], C_reg[i][jo]);
          }
          _mm512_mask_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * ((N) / (16))) * (C.strides[1])], ((1 << (N % 16)) - 1), C_reg_1[i]);
        }
      }
    }
  }
}
}

// sgemm_kernel_avx512_1x4(
//     K : size,
//     A : [f32][1,K]  @DRAM,
//     B : [f32][K,64]  @DRAM,
//     C : [f32][1,64]  @DRAM
// )
void sgemm_kernel_avx512_1x4( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
__m512 C_reg[1][4];
for (int i = 0; i < 1; i++) {
  for (int jo = 0; jo < 4; jo++) {
    C_reg[i][jo] = _mm512_loadu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  for (int i = 0; i < 1; i++) {
    __m512 A_vec;
    (A_vec) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
    for (int jo = 0; jo < 4; jo++) {
      __m512 B_vec;
      B_vec = _mm512_loadu_ps(&B.data[(k) * (B.strides[0]) + (16 * jo) * (B.strides[1])]);
      C_reg[i][jo] = _mm512_fmadd_ps((A_vec), (B_vec), C_reg[i][jo]);
    }
  }
}
for (int i = 0; i < 1; i++) {
  for (int jo = 0; jo < 4; jo++) {
    _mm512_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// sgemm_kernel_avx512_3x4(
//     K : size,
//     A : [f32][3,K]  @DRAM,
//     B : [f32][K,64]  @DRAM,
//     C : [f32][3,64]  @DRAM
// )
void sgemm_kernel_avx512_3x4( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
__m512 C_reg[3][4];
for (int i = 0; i < 3; i++) {
  for (int jo = 0; jo < 4; jo++) {
    C_reg[i][jo] = _mm512_loadu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  for (int i = 0; i < 3; i++) {
    __m512 A_vec;
    (A_vec) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
    for (int jo = 0; jo < 4; jo++) {
      __m512 B_vec;
      B_vec = _mm512_loadu_ps(&B.data[(k) * (B.strides[0]) + (16 * jo) * (B.strides[1])]);
      C_reg[i][jo] = _mm512_fmadd_ps((A_vec), (B_vec), C_reg[i][jo]);
    }
  }
}
for (int i = 0; i < 3; i++) {
  for (int jo = 0; jo < 4; jo++) {
    _mm512_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// sgemm_kernel_avx512_5x4(
//     K : size,
//     A : [f32][5,K]  @DRAM,
//     B : [f32][K,64]  @DRAM,
//     C : [f32][5,64]  @DRAM
// )
void sgemm_kernel_avx512_5x4( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
__m512 C_reg[5][4];
for (int i = 0; i < 5; i++) {
  for (int jo = 0; jo < 4; jo++) {
    C_reg[i][jo] = _mm512_loadu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  for (int i = 0; i < 5; i++) {
    __m512 A_vec;
    (A_vec) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
    for (int jo = 0; jo < 4; jo++) {
      __m512 B_vec;
      B_vec = _mm512_loadu_ps(&B.data[(k) * (B.strides[0]) + (16 * jo) * (B.strides[1])]);
      C_reg[i][jo] = _mm512_fmadd_ps((A_vec), (B_vec), C_reg[i][jo]);
    }
  }
}
for (int i = 0; i < 5; i++) {
  for (int jo = 0; jo < 4; jo++) {
    _mm512_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// sgemm_kernel_avx512_2x4(
//     K : size,
//     A : [f32][2,K]  @DRAM,
//     B : [f32][K,64]  @DRAM,
//     C : [f32][2,64]  @DRAM
// )
void sgemm_kernel_avx512_2x4( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
__m512 C_reg[2][4];
for (int i = 0; i < 2; i++) {
  for (int jo = 0; jo < 4; jo++) {
    C_reg[i][jo] = _mm512_loadu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  for (int i = 0; i < 2; i++) {
    __m512 A_vec;
    (A_vec) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
    for (int jo = 0; jo < 4; jo++) {
      __m512 B_vec;
      B_vec = _mm512_loadu_ps(&B.data[(k) * (B.strides[0]) + (16 * jo) * (B.strides[1])]);
      C_reg[i][jo] = _mm512_fmadd_ps((A_vec), (B_vec), C_reg[i][jo]);
    }
  }
}
for (int i = 0; i < 2; i++) {
  for (int jo = 0; jo < 4; jo++) {
    _mm512_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// sgemm_kernel_avx512_4x4(
//     K : size,
//     A : [f32][4,K]  @DRAM,
//     B : [f32][K,64]  @DRAM,
//     C : [f32][4,64]  @DRAM
// )
void sgemm_kernel_avx512_4x4( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
__m512 C_reg[4][4];
for (int i = 0; i < 4; i++) {
  for (int jo = 0; jo < 4; jo++) {
    C_reg[i][jo] = _mm512_loadu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  for (int i = 0; i < 4; i++) {
    __m512 A_vec;
    (A_vec) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
    for (int jo = 0; jo < 4; jo++) {
      __m512 B_vec;
      B_vec = _mm512_loadu_ps(&B.data[(k) * (B.strides[0]) + (16 * jo) * (B.strides[1])]);
      C_reg[i][jo] = _mm512_fmadd_ps((A_vec), (B_vec), C_reg[i][jo]);
    }
  }
}
for (int i = 0; i < 4; i++) {
  for (int jo = 0; jo < 4; jo++) {
    _mm512_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])], C_reg[i][jo]);
  }
}
}

// bottom_panel_kernel_scheduled(
//     M : size,
//     K : size,
//     A : [f32][M,K]  @DRAM,
//     B : [f32][K,64]  @DRAM,
//     C : [f32][M,64]  @DRAM
// )
void bottom_panel_kernel_scheduled( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
EXO_ASSUME(M < 6);
if (M == 1) {
  sgemm_kernel_avx512_1x4(ctxt,K,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
} else {
  if (M == 2) {
    sgemm_kernel_avx512_2x4(ctxt,K,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  } else {
    if (M == 3) {
      sgemm_kernel_avx512_3x4(ctxt,K,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
    } else {
      if (M == 4) {
        sgemm_kernel_avx512_4x4(ctxt,K,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
      } else {
        if (M == 5) {
          sgemm_kernel_avx512_5x4(ctxt,K,(struct exo_win_2f32){ (float*)&A.data[(0) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (0) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(0) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });
        } else {
          for (int k = 0; k < K; k++) {
            for (int i = 0; i < M; i++) {
              for (int j = 0; j < 64; j++) {
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


/* relying on the following instruction...
mm512_set1_ps(dst,src)
{dst} = _mm512_set1_ps({src_data});
*/


/* relying on the following instruction...
mm512_fmadd_ps(A,B,C)
{C_data} = _mm512_fmadd_ps({A}, {B}, {C_data});
*/


/* relying on the following instruction...
mm512_storeu_ps(dst,src)
_mm512_storeu_ps(&{dst_data}, {src_data});
*/


/* relying on the following instruction...
mm512_loadu_ps(dst,src)
{dst_data} = _mm512_loadu_ps(&{src_data});
*/

// sgemm_kernel_avx512_6x4(
//     K : size,
//     A : [f32][6,K]  @DRAM,
//     B : [f32][K,64]  @DRAM,
//     C : [f32][6,64]  @DRAM
// )
void sgemm_kernel_avx512_6x4( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
EXO_ASSUME(K >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(B.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
__m512 C_reg[6][4];
for (int i = 0; i < 6; i++) {
  for (int jo = 0; jo < 4; jo++) {
    C_reg[i][jo] = _mm512_loadu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])]);
  }
}
for (int k = 0; k < K; k++) {
  for (int i = 0; i < 6; i++) {
    __m512 A_vec;
    (A_vec) = _mm512_set1_ps(A.data[(i) * (A.strides[0]) + (k) * (A.strides[1])]);
    for (int jo = 0; jo < 4; jo++) {
      __m512 B_vec;
      B_vec = _mm512_loadu_ps(&B.data[(k) * (B.strides[0]) + (16 * jo) * (B.strides[1])]);
      C_reg[i][jo] = _mm512_fmadd_ps((A_vec), (B_vec), C_reg[i][jo]);
    }
  }
}
for (int i = 0; i < 6; i++) {
  for (int jo = 0; jo < 4; jo++) {
    _mm512_storeu_ps(&C.data[(i) * (C.strides[0]) + (16 * jo) * (C.strides[1])], C_reg[i][jo]);
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
  for (int jo = 0; jo < ((N) / (64)); jo++) {
    sgemm_kernel_avx512_6x4(ctxt,K,(struct exo_win_2f32){ (float*)&A.data[(6 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (64 * jo) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(6 * io) * (C.strides[0]) + (64 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
if (N % 64 > 0) {
  for (int io = 0; io < ((M) / (6)); io++) {
    right_panel_kernel_scheduled(ctxt,N % 64,K,(struct exo_win_2f32){ (float*)&A.data[(6 * io) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (64 * ((N) / (64))) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(6 * io) * (C.strides[0]) + (64 * ((N) / (64))) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
}
if (M % 6 > 0) {
  for (int jo = 0; jo < ((N) / (64)); jo++) {
    bottom_panel_kernel_scheduled(ctxt,M % 6,K,(struct exo_win_2f32){ (float*)&A.data[(6 * ((M) / (6))) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&B.data[(0) * (B.strides[0]) + (64 * jo) * (B.strides[1])], { B.strides[0], B.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(6 * ((M) / (6))) * (C.strides[0]) + (64 * jo) * (C.strides[1])], { C.strides[0], C.strides[1] } });
  }
  if (N % 64 > 0) {
    for (int k = 0; k < K; k++) {
      for (int ii = 0; ii < M % 6; ii++) {
        for (int ji = 0; ji < N % 64; ji++) {
          C.data[(ii + ((M) / (6)) * 6) * (C.strides[0]) + (ji + ((N) / (64)) * 64) * (C.strides[1])] += A.data[(ii + ((M) / (6)) * 6) * (A.strides[0]) + (k) * (A.strides[1])] * B.data[(k) * (B.strides[0]) + (ji + ((N) / (64)) * 64) * (B.strides[1])];
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
static float B1_cache[512 * 64];
for (int ko = 0; ko < ((K) / (512)); ko++) {
  for (int io = 0; io < ((M) / (264)); io++) {
    for (int jo = 0; jo < ((N) / (64)); jo++) {
      for (int i0 = 0; i0 < 512; i0++) {
        for (int i1 = 0; i1 < 64; i1++) {
          B1_cache[(i0) * (64) + (i1) * (1)] = B[(512 * ko + i0) * (N) + (64 * jo + i1) * (1)];
        }
      }
    }
    for (int jo = 0; jo < ((N) / (64)); jo++) {
      sgemm_above_kernel(ctxt,264,64,512,(struct exo_win_2f32){ (float*)&A[(264 * io) * (K) + (512 * ko) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B1_cache[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * io) * (N) + (64 * jo) * (1)], { N, 1 } });
    }
  }
}
if (N % 64 > 0) {
  for (int ko = 0; ko < ((K) / (512)); ko++) {
    static float B2_cache[512 * 64];
    for (int io = 0; io < ((M) / (264)); io++) {
      for (int i0 = 0; i0 < 512; i0++) {
        for (int i1 = 0; i1 < N - 64 * ((N) / (64)); i1++) {
          B2_cache[(i0) * (64) + (i1) * (1)] = B[(512 * ko + i0) * (N) + (64 * ((N) / (64)) + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,264,N % 64,512,(struct exo_win_2f32){ (float*)&A[(264 * io) * (K) + (512 * ko) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B2_cache[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * io) * (N) + (64 * ((N) / (64))) * (1)], { N, 1 } });
    }
  }
}
if (M % 264 > 0) {
  for (int ko = 0; ko < ((K) / (512)); ko++) {
    for (int jo = 0; jo < ((N) / (64)); jo++) {
      static float B3_cache[512 * 64];
      for (int i0 = 0; i0 < 512; i0++) {
        for (int i1 = 0; i1 < 64; i1++) {
          B3_cache[(i0) * (64) + (i1) * (1)] = B[(512 * ko + i0) * (N) + (64 * jo + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,M % 264,64,512,(struct exo_win_2f32){ (float*)&A[(264 * ((M) / (264))) * (K) + (512 * ko) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B3_cache[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * ((M) / (264))) * (N) + (64 * jo) * (1)], { N, 1 } });
    }
  }
}
if (M % 264 > 0) {
  if (N % 64 > 0) {
    for (int ko = 0; ko < ((K) / (512)); ko++) {
      static float B4_cache[512 * 64];
      for (int i0 = 0; i0 < 512; i0++) {
        for (int i1 = 0; i1 < N - 64 * ((N) / (64)); i1++) {
          B4_cache[(i0) * (64) + (i1) * (1)] = B[(512 * ko + i0) * (N) + (64 * ((N) / (64)) + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,M % 264,N % 64,512,(struct exo_win_2f32){ (float*)&A[(264 * ((M) / (264))) * (K) + (512 * ko) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B4_cache[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * ((M) / (264))) * (N) + (64 * ((N) / (64))) * (1)], { N, 1 } });
    }
  }
}
if (K % 512 > 0) {
  for (int io = 0; io < ((M) / (264)); io++) {
    for (int jo = 0; jo < ((N) / (64)); jo++) {
      static float B5_cache[512 * 64];
      for (int i0 = 0; i0 < K - 512 * ((K) / (512)); i0++) {
        for (int i1 = 0; i1 < 64; i1++) {
          B5_cache[(i0) * (64) + (i1) * (1)] = B[(512 * ((K) / (512)) + i0) * (N) + (64 * jo + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,264,64,K % 512,(struct exo_win_2f32){ (float*)&A[(264 * io) * (K) + (512 * ((K) / (512))) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B5_cache[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * io) * (N) + (64 * jo) * (1)], { N, 1 } });
    }
  }
}
if (K % 512 > 0) {
  if (N % 64 > 0) {
    for (int io = 0; io < ((M) / (264)); io++) {
      static float B6_cache[512 * 64];
      for (int i0 = 0; i0 < K - 512 * ((K) / (512)); i0++) {
        for (int i1 = 0; i1 < N - 64 * ((N) / (64)); i1++) {
          B6_cache[(i0) * (64) + (i1) * (1)] = B[(512 * ((K) / (512)) + i0) * (N) + (64 * ((N) / (64)) + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,264,N % 64,K % 512,(struct exo_win_2f32){ (float*)&A[(264 * io) * (K) + (512 * ((K) / (512))) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B6_cache[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * io) * (N) + (64 * ((N) / (64))) * (1)], { N, 1 } });
    }
  }
}
if (K % 512 > 0) {
  if (M % 264 > 0) {
    for (int jo = 0; jo < ((N) / (64)); jo++) {
      static float B7_cache[512 * 64];
      for (int i0 = 0; i0 < K - 512 * ((K) / (512)); i0++) {
        for (int i1 = 0; i1 < 64; i1++) {
          B7_cache[(i0) * (64) + (i1) * (1)] = B[(512 * ((K) / (512)) + i0) * (N) + (64 * jo + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,M % 264,64,K % 512,(struct exo_win_2f32){ (float*)&A[(264 * ((M) / (264))) * (K) + (512 * ((K) / (512))) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B7_cache[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * ((M) / (264))) * (N) + (64 * jo) * (1)], { N, 1 } });
    }
  }
}
if (K % 512 > 0) {
  if (M % 264 > 0) {
    if (N % 64 > 0) {
      static float B8_cache[512 * 64];
      for (int i0 = 0; i0 < K - 512 * ((K) / (512)); i0++) {
        for (int i1 = 0; i1 < N - 64 * ((N) / (64)); i1++) {
          B8_cache[(i0) * (64) + (i1) * (1)] = B[(512 * ((K) / (512)) + i0) * (N) + (64 * ((N) / (64)) + i1) * (1)];
        }
      }
      sgemm_above_kernel(ctxt,M % 264,N % 64,K % 512,(struct exo_win_2f32){ (float*)&A[(264 * ((M) / (264))) * (K) + (512 * ((K) / (512))) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B8_cache[(0) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&C[(264 * ((M) / (264))) * (N) + (64 * ((N) / (64))) * (1)], { N, 1 } });
    }
  }
}
}
