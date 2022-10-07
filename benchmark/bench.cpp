#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <cblas.h>

#include <chrono>
#include "include/blis/blis.h"


static std::vector<float> gen_matrix(long m, long n) {
  static std::random_device rd;
  static std::mt19937 rng{rd()};
  std::uniform_real_distribution<> rv{-1.0f, 1.0f};

  std::vector<float> mat(m * n);
  std::generate(std::begin(mat), std::end(mat), [&]() { return rv(rng); });

  return mat;
}


int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <n>\n", argv[0]);
    return 1;
  }
  int n = std::atoi(argv[1]);
  if (n < 1) {
    printf("n < 1!!\n");
    return 1;
  }

  std::string op(argv[2]);

  std::ofstream log_file;
  log_file.open("stats.out", std::ios_base::app);

  auto a = gen_matrix(n, n);
  auto b = gen_matrix(n, n);
  auto c = gen_matrix(n, n);
  auto c2 = c;

  printf("\n\n\n\n");
  printf("Multiplying two %d x %d matrices\n", n, n);
  long FLOP_C = 2 * long(n)*long(n)*long(n);

  /* openBLAS benchmark */
  int N_TIMES_BLAS = 10;
  auto begin = std::chrono::steady_clock::now();
  for(int times = 0; times<N_TIMES_BLAS; times++) {
    if (op==std::string("sgemm"))
      cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                  n, n, n, 
                  1.0, 
                  a.data(), n,
                  b.data(), n,
                  1.0,
                  c.data(), n);
    else if (op==std::string("syrk"))
      cblas_ssyrk(CblasRowMajor, CblasUpper, CblasNoTrans,
                  n, n, 
                  1.0, 
                  a.data(), n,
                  1.0,
                  c.data(), n);
    else if (op==std::string("symm"))
      cblas_ssymm(CblasRowMajor, CblasRight, CblasUpper,
                  n, n,
                  1.0, a.data(),
                  n, b.data(),
                  n, 1.0,
                  c.data(), n);
  }
  auto end = std::chrono::steady_clock::now();
  double duration = std::chrono::duration<double>(end - begin).count();
  double ms_per_gemm = duration/N_TIMES_BLAS*1.0e3;
  double gflops_blas = (FLOP_C*1.0e-6)/ms_per_gemm;
  //log_file << gflops << '\n';
  printf("-----------------------------------------------------------\n");
  printf("  openBLAS %s took %5.1lf ms, or %4.1lf GFLOPS. That's %4.1lf percent of peak.\n",
         op, ms_per_gemm, (FLOP_C*1.0e-6)/ms_per_gemm, (((FLOP_C*1.0e-6)/ms_per_gemm)/16)*100);
  
  /* BLIS benchmark */
  int N_TIMES_BLIS = 10;
  begin = std::chrono::steady_clock::now();
  const float alpha = 1.0;
  const float beta = 1.0;
  for(int times = 0; times<N_TIMES_BLIS; times++) {
    if (op==std::string("sgemm"))
      bli_sgemm(BLIS_NO_TRANSPOSE, BLIS_NO_TRANSPOSE, 
                n, n, n, 
                &alpha, a.data(), 1, n, 
                b.data(), 1, n, &beta, 
                c.data(), 1, n);
    else if (op==std::string("syrk"))
      bli_ssyrk(BLIS_UPPER, BLIS_NO_TRANSPOSE,
                  n, n, 
                  &alpha, 
                  a.data(), n, n,
                  &beta,
                  c.data(), n, n);
    else if (op==std::string("symm"))
      bli_ssymm(BLIS_RIGHT, BLIS_UPPER, BLIS_NO_CONJUGATE, BLIS_NO_TRANSPOSE,
                n, n,
                &alpha,
                a.data(), n, n,
                b.data(), n, n, &beta,
                c.data(), n, n);
  }
  end = std::chrono::steady_clock::now();
  duration = std::chrono::duration<double>(end - begin).count();
  ms_per_gemm = duration/N_TIMES_BLIS*1.0e3;
  double gflops_blis = (FLOP_C*1.0e-6)/ms_per_gemm;
  log_file << n << ", " << gflops_blas << ", " << gflops_blis << '\n';
  printf("-----------------------------------------------------------\n");
  printf("  BLIS %s took %5.1lf ms, or %4.1lf GFLOPS. That's %4.1lf percent of peak.\n",
         op, ms_per_gemm, (FLOP_C*1.0e-6)/ms_per_gemm, (((FLOP_C*1.0e-6)/ms_per_gemm)/16)*100);
  
}