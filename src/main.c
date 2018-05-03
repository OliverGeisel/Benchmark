#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <x86intrin.h>
#include "matrix/matrixPointer.h"
#include "matrix/matrixArray.h"

int secondmain();

int main(int argc, char **argv) {
    secondmain();
    double t_start, t_end;
    double gflops;
    uint32_t dim = 0;
    uint32_t step = 32;
    uint32_t max = 2048;

    printf("\nMatrix matrix multiply example:\n\n");

    while (dim < max) {
        if (dim < 256) { dim += step; }
        else if (dim < 512) { dim += step * 2; }
        else if (dim < 1024) { dim += step * 4; }
        else if (dim < 2048) { dim += step * 8; }
        else if (dim < 4096) { dim += step * 16; }
        else { dim += step * 32; }

        double *A = random_mat(dim);
        double *B = random_mat(dim);
        double *C = zero_mat(dim);

        if (A == NULL || B == NULL || C == NULL) {
            printf("Allocation of matrix failed.\n");
            exit(EXIT_FAILURE);
        }

        t_start = gtod();

        /* Begin matrix matrix multiply kernel */
        for (uint32_t i = 0; i < dim; i++) {
            for (uint32_t k = 0; k < dim; k++) {
                for (uint32_t j = 0; j < dim; j++) {
                    // C[i][j] += A[i][k] * B[k][j]
                    C[i * dim + j] += A[i * dim + k] * B[k * dim + j];
                }
            }
        }
        /* End matrix matrix multiply kernel */

        t_end = gtod();
        gflops = ((double) 2 * dim * dim * dim / 1000000000.0) / (t_end - t_start);

        printf("Dim: %4d  runtime: %7.4fs  GFLOP/s: %0.2f\n", dim, t_end - t_start, gflops);

        free(A);
        free(B);
        free(C);
    }
    printf("\n");

    return EXIT_SUCCESS;
}


int secondmain(){
    double t_start, t_end;
    double gflops;
    uint32_t dim = 0;
    uint32_t step = 32;
    uint32_t max = 2048;

    printf("\nMatrix matrix multiply example:\n\n");

    while (dim < max) {
        if (dim < 256) { dim += step; }
        else if (dim < 512) { dim += step * 2; }
        else if (dim < 1024) { dim += step * 4; }
        else if (dim < 2048) { dim += step * 8; }
        else if (dim < 4096) { dim += step * 16; }
        else { dim += step * 32; }

        double **A = random_mat_A(dim);
        double **B = random_mat_A(dim);
        double **C = zero_mat_A(dim);

        if (A == NULL || B == NULL || C == NULL) {
            printf("Allocation of matrix failed.\n");
            exit(EXIT_FAILURE);
        }

        t_start = gtod();

        /* Begin matrix matrix multiply kernel */
        for (uint32_t i = 0; i < dim; i++) {
            for (uint32_t k = 0; k < dim; k++) {
                for (uint32_t j = 0; j < dim; j++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        /* End matrix matrix multiply kernel */

        t_end = gtod();
        gflops = ((double) 2 * dim * dim * dim / 1000000000.0) / (t_end - t_start);

        printf("Dim: %4d  runtime: %7.4fs  GFLOP/s: %0.2f\n", dim, t_end - t_start, gflops);

        free(A);
        free(B);
        free(C);
    }
    printf("\n");
}
