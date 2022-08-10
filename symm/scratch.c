/* Messing around to try to figure out partitioning stuff for SYMM */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


int int_pow(int a, int b) {
    if (b==0)
        return 0;
    int result = a;
    while (b>1) {
        result *= result;
        b-=1;
    }
    return result;
}


void partition_A(float *A, int m, int k, int blk) {
    float *A_TL;
    float *A_TR = (float *)malloc(sizeof(float)*blk*k);
    float *A_BR = (float *)malloc(sizeof(float)*(m-blk)*(k-blk));
    float *A_BL = (float *)malloc(sizeof(float)*(m-blk)*blk);

    float *A00;
    int m_atl = 0;
    int k_atl = 0;

    float *A01;
    int m_01 = blk;
    int k_01 = blk*2;

    float *A02;
    int m_02 = blk;
    int k_02 = blk*2;

    float *A10;
    int m_10 = blk;
    int k_10 = blk;

    float *A11;
    int m_11 = blk;
    int k_11 = blk;

    float *A12;
    int m_12 = blk;
    int k_12 = blk*2;

    float *A20;
    int m_20 = blk*2;
    int k_20 = blk;

    float *A21;
    int m_21 = blk*2;
    int k_21 = blk;

    float *A22;
    int m_22 = blk*2;
    int k_22 = blk*2;

    int niters = 1;

    while (m_atl<m && niters<4) {
        
        //TODO: Refactor this mess into a function 
        printf("ITERATION %d\n", niters);
        printf("===============\n");
        
        printf("m_atl: %d\n", m_atl);
        printf("k_atl: %d\n", k_atl);
        printf("\n");

        printf("m_01: %d\n", m_01);
        printf("k_01: %d\n", k_01);
        printf("\n");

        printf("m_02: %d\n", m_02);
        printf("k_02: %d\n", k_02);
        printf("\n");

        printf("m_10: %d\n", m_10);
        printf("k_10: %d\n", k_10);
        printf("\n");

        printf("m_11: %d\n", m_11);
        printf("k_11: %d\n", k_11);
        printf("\n");

        printf("m_12: %d\n", m_12);
        printf("k_12: %d\n", k_12);
        printf("\n");

        printf("m_20: %d\n", m_20);
        printf("k_20: %d\n", k_20);
        printf("\n");

        printf("m_21: %d\n", m_21);
        printf("k_21: %d\n", k_21);
        printf("\n");

        printf("m_22: %d\n", m_22);
        printf("k_22: %d\n", k_22);
        printf("\n");

        //call me a faucet cuz this memory is leaky
        A00 = (float *)malloc(sizeof(float) * m_atl * m_atl);
        A01 = (float *)malloc(sizeof(float) * m_01 * k_01);
        A02 = (float *)malloc(sizeof(float) * m_02 * k_02);
        A10 = (float *)malloc(sizeof(float) * m_10 * k_10);
        A11 = (float *)malloc(sizeof(float) * m_11 * k_11);
        A12 = (float *)malloc(sizeof(float) * m_12 * k_12);
        A20 = (float *)malloc(sizeof(float) * m_20 * k_20);
        A21 = (float *)malloc(sizeof(float) * m_21 * k_21);
        A22 = (float *)malloc(sizeof(float) * m_22 * k_22);

        ++niters;

        /*
         * Basically two cases. 
         * One where the dimension changes so that it's equal to blk**niters,
         * and another where the dimension changes so that it's prev_dim/blk.
         * I will need to figure out which blk to use for each, since this implementation assumes 
         * square block sizes. I think for changes to m, it should just be m_c, and for k, k_c.
         * That seems to make sense.
         * 
         * I'm also not 100% sure this always works, I've only mentally run through it on some small
         * square matrices with small square blocks. 
         * 
         * I think we should be able to use a loop variable as the niters substitution.
         * Since m_atl is set equal to blk**niters at each iteration, we should just be able to call
         * partial_eval(M=log(M)) with base=blk (I think m_c if not square?),
         * 
         * Now, as far as actually changing the buffer sizes at each iteration... yeah need to think more
         * about that one. For case 1, should be easy I think. I think we can change case 2 so that instead
         * of k_01 = k_01/blk, k_01 = k_original/(blk**niters)... I THINK but need to mentally run thru that.
         * If I'm right about that, then this should be doable.
         * 
         * This should hopefully be fine for partitioning A. B and C should be easy in comparison I HOPE.
         */

        m_atl = int_pow(blk, niters);
        k_atl = int_pow(blk, niters);
        
        m_01 = int_pow(blk, niters);
        k_01 = k_01/blk;
        
        m_02 = int_pow(blk, niters);
        k_02 = k_02/blk;

        m_10 = m_10/blk;
        k_10 = int_pow(blk, niters);

        m_11 = blk;
        k_11 = blk;

        m_12 = m_12/blk;
        k_12 = k_12/blk;

        m_20 = m_20/blk;
        k_20 = int_pow(blk, niters);

        m_21 = m_21/blk;
        k_21 = k_21/blk;

        m_22 = m_22/blk;
        k_22 = k_22/blk;
    }

    printf("ITERATION FINAL\n");
    printf("===============\n");
        
    printf("m_atl: %d\n", m_atl);
    printf("k_atl: %d\n", k_atl);
    printf("\n");

    printf("m_01: %d\n", m_01);
    printf("k_01: %d\n", k_01);
    printf("\n");

    printf("m_02: %d\n", m_02);
    printf("k_02: %d\n", k_02);
    printf("\n");

    printf("m_10: %d\n", m_10);
    printf("k_10: %d\n", k_10);
    printf("\n");

    printf("m_11: %d\n", m_11);
    printf("k_11: %d\n", k_11);
    printf("\n");

    printf("m_12: %d\n", m_12);
    printf("k_12: %d\n", k_12);
    printf("\n");

    printf("m_20: %d\n", m_20);
    printf("k_20: %d\n", k_20);
    printf("\n");

    printf("m_21: %d\n", m_21);
    printf("k_21: %d\n", k_21);
    printf("\n");

    printf("m_22: %d\n", m_22);
    printf("k_22: %d\n", k_22);
    printf("\n");
}


int main() {
    int dim = 8;
    float *M = (float *)malloc(sizeof(float)*dim*dim);
    partition_A(M, dim, dim, 2);
    return 0;
}