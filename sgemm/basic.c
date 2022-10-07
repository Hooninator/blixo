
#include <stdint.h>
#include <stdbool.h>



// sgemm_exo_g(
//     M : size,
//     N : size,
//     K : size,
//     A : f32[M,K]  @DRAM,
//     B : f32[K,N]  @DRAM,
//     C : f32[M,N]  @DRAM
// )
void sgemm_exo_g( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, int_fast32_t K, float* A, float* B, float* C );



#include <stdio.h>
#include <stdlib.h>


#include <arm_neon.h>


/* relying on the following instruction...
neon_vfmadd_4xf32_4xf32(dst,lhs,rhs)
{dst_data} = vmlaq_f32({dst_data}, {lhs_data}, {rhs_data});
*/


/* relying on the following instruction...
neon_vst_4xf32(dst,src)
vst1q_f32(&{dst_data}, {src_data});
*/


/* relying on the following instruction...
neon_broadcast_4xf32(dst,src)
{dst_data} = vld1q_dup_f32(&{src_data});
*/


/* relying on the following instruction...
neon_vld_4xf32(dst,src)
{dst_data} = vld1q_f32(&{src_data});
*/

// neon_microkernel_g(
//     K : size,
//     A : [f32][4,K]  @DRAM,
//     B : [f32][K,16]  @DRAM,
//     C : [f32][4,16]  @DRAM
// )
void neon_microkernel_g( c_code_str_Context *ctxt, int_fast32_t K, struct exo_win_2f32 A, struct exo_win_2f32 B, struct exo_win_2f32 C ) {
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

// sgemm_exo_g(
//     M : size,
//     N : size,
//     K : size,
//     A : f32[M,K]  @DRAM,
//     B : f32[K,N]  @DRAM,
//     C : f32[M,N]  @DRAM
// )
void sgemm_exo_g( c_code_str_Context *ctxt, int_fast32_t M, int_fast32_t N, int_fast32_t K, float* A, float* B, float* C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(N >= 1);
EXO_ASSUME(K >= 1);
EXO_ASSUME(1 == 1);
EXO_ASSUME(1 == 1);
EXO_ASSUME(1 == 1);
float *Atile = (float *)malloc(64 * 64 * sizeof(*Atile));
float *Btile = (float *)malloc(64 * 64 * sizeof(*Btile));
for (int ko = 0; ko < ((K) / (64)); ko++) {
  for (int io = 0; io < ((((M) / (4))) / (16)); io++) {
    for (int i0 = 0; i0 < 64; i0++) {
      for (int i1 = 0; i1 < 64; i1++) {
        Atile[(i0) * (64) + (i1) * (1)] = A[(i0 + 64 * io) * (K) + (i1 + 64 * ko) * (1)];
      }
    }
    for (int jo = 0; jo < ((((N) / (16))) / (4)); jo++) {
      for (int i0 = 0; i0 < 64; i0++) {
        for (int i1 = 0; i1 < 64; i1++) {
          Btile[(i0) * (64) + (i1) * (1)] = B[(i0 + 64 * ko) * (N) + (i1 + 64 * jo) * (1)];
        }
      }
      for (int im = 0; im < 16; im++) {
        for (int jm = 0; jm < 4; jm++) {
          neon_microkernel_g(ctxt,64,(struct exo_win_2f32){ (float*)&Atile[(4 * im) * (64) + (0) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&Btile[(0) * (64) + (16 * jm) * (1)], { 64, 1 } },(struct exo_win_2f32){ (float*)&C[(64 * io + 4 * im) * (N) + (64 * jo + 16 * jm) * (1)], { N, 1 } });
        }
      }
    }
  }
}
for (int ko = 0; ko < ((K) / (64)); ko++) {
  for (int io = 0; io < ((((M) / (4))) / (16)); io++) {
    for (int jm = 0; jm < ((N) / (16)) % 4; jm++) {
      for (int im = 0; im < 16; im++) {
        neon_microkernel_g(ctxt,64,(struct exo_win_2f32){ (float*)&A[(64 * io + 4 * im) * (K) + (64 * ko) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B[(64 * ko) * (N) + (16 * (jm + ((((N) / (16))) / (4)) * 4)) * (1)], { N, 1 } },(struct exo_win_2f32){ (float*)&C[(64 * io + 4 * im) * (N) + (16 * (jm + ((((N) / (16))) / (4)) * 4)) * (1)], { N, 1 } });
      }
    }
  }
  for (int jo = 0; jo < ((N) / (16)); jo++) {
    for (int im = 0; im < ((M) / (4)) % 16; im++) {
      neon_microkernel_g(ctxt,64,(struct exo_win_2f32){ (float*)&A[(4 * (im + ((((M) / (4))) / (16)) * 16)) * (K) + (64 * ko) * (1)], { K, 1 } },(struct exo_win_2f32){ (float*)&B[(64 * ko) * (N) + (16 * jo) * (1)], { N, 1 } },(struct exo_win_2f32){ (float*)&C[(4 * (im + ((((M) / (4))) / (16)) * 16)) * (N) + (16 * jo) * (1)], { N, 1 } });
    }
  }
}
for (int io = 0; io < ((M) / (4)); io++) {
  for (int jo = 0; jo < ((N) / (16)); jo++) {
    for (int ii = 0; ii < 4; ii++) {
      for (int ji = 0; ji < 16; ji++) {
        if (K % 64 > 0) {
          for (int ki = 0; ki < K % 64; ki++) {
            C[(4 * io + ii) * (N) + (16 * jo + ji) * (1)] += A[(4 * io + ii) * (K) + (ki + ((K) / (64)) * 64) * (1)] * B[(ki + ((K) / (64)) * 64) * (N) + (16 * jo + ji) * (1)];
          }
        }
      }
    }
  }
}
for (int io = 0; io < ((M) / (4)); io++) {
  for (int ii = 0; ii < 4; ii++) {
    if (N % 16 > 0) {
      for (int ji = 0; ji < N % 16; ji++) {
        for (int k = 0; k < K; k++) {
          C[(4 * io + ii) * (N) + (ji + ((N) / (16)) * 16) * (1)] += A[(4 * io + ii) * (K) + (k) * (1)] * B[(k) * (N) + (ji + ((N) / (16)) * 16) * (1)];
        }
      }
    }
  }
}
if (M % 4 > 0) {
  for (int ii = 0; ii < M % 4; ii++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < K; k++) {
        C[(ii + ((M) / (4)) * 4) * (N) + (j) * (1)] += A[(ii + ((M) / (4)) * 4) * (K) + (k) * (1)] * B[(k) * (N) + (j) * (1)];
      }
    }
  }
}
free(Atile);
free(Btile);
}
