void GEPP_syrk( c_code_str_Context *ctxt, int_fast32_t M, struct exo_win_2f32 A, struct exo_win_2f32 A_t, struct exo_win_2f32 C ) {
EXO_ASSUME(M >= 1);
EXO_ASSUME(A.strides[1] == 1);
EXO_ASSUME(A_t.strides[1] == 1);
EXO_ASSUME(C.strides[1] == 1);
for (int i = 0; i < M; i++) {
        ...
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
                    neon_microkernel_two_8(ctxt,(struct exo_win_2f32){ (float*)&A.data[(9) * (A.strides[0]) + (0) * (A.strides[1])], { A.strides[0], A.strides[1] } },(struct exo_win_2f32){ (float*)&A_t.data[(0) * (A_t.strides[0]) + (0) * (A_t.strides[1])], { A_t.strides[0], A_t.strides[1] } },(struct exo_win_2f32){ (float*)&C.data[(9) * (C.strides[0]) + (0) * (C.strides[1])], { C.strides[0], C.strides[1] } });                } else {
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