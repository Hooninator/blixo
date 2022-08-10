#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <vector>
#include <iostream>

#include <chrono>


#include <cblas.h>
#include "symm.c"
//#include "output.c"

static std::vector<float> gen_matrix(long m, long n, float v) {
  static std::random_device rd;
  static std::mt19937 rng{rd()};
  std::uniform_real_distribution<> rv{-1.0f, 1.0f};

  std::vector<float> mat(m * n);
  std::generate(std::begin(mat), std::end(mat), [&]() { return v; });

  return mat;
}

static void print_matrix(std::vector<float> M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << M[j*n + i] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    int n = atoi(argv[1]);

    auto a = gen_matrix(n, n, 2.0);
    auto b = gen_matrix(n, n, 2.0);
    auto c = gen_matrix(n, n, 0.0);
    auto c2 = c; 

    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                n, n, n, // M N K
                1.0, // alpha
                a.data(),
                n, // M
                b.data(),
                n, // K
                1.0, // beta
                c.data(),
                n  // M
                );

    print_matrix(c, n);

    __SYMM_BLK(NULL, n, a.data(), b.data(), c2.data());
    //sgemm_exo(NULL, n, n, n, a.data(), b.data(), c2.data());

    print_matrix(c2, n);
}