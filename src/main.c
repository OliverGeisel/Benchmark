#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <x86intrin.h>
#include "matrix/matrixPointer.h"
#include "matrix/matrixArray.h"
#include <unistd.h>

int secondmain();
void collect_info(double t_start,double t_end, double gflops);


uint32_t dim = 0;
const uint32_t step = 32;
const uint32_t max = 2048*4;
FILE* results;

void set_dim() {
    if (dim < 256) { dim += step; }
    else if (dim < 512) { dim += step * 2; }
    else if (dim < 1024) { dim += step * 4; }
    else if (dim < 2048) { dim += step * 8; }
    else if (dim < 4096) { dim += step * 16; }
    else { dim += step * 32; }
}


/** @brief Get current time stamp in seconds.
 *
 *  @return         Returns current time stamp in seconds.
 */
inline double gtod() {
    struct timeval act_time;
    gettimeofday(&act_time, NULL);

    return (double) act_time.tv_sec + (double) act_time.tv_usec / 1000000.0;
}

int main(int argc, char **argv) {
    results = fopen("Ergebnisse.txt","w+");
    if (results==NULL)
        printf("Fehler");
    double t_start, t_end;
    double gflops;
    dim = 0;

    printf("\nMatrix matrix multiply example:\n\n");

    while (dim < max) {
        set_dim();

        double *A = random_mat(dim);
        double *B = random_mat(dim);
        double *C = zero_mat(dim);

        if (A == NULL || B == NULL || C == NULL) {
            printf("Allocation of matrix failed.\n");
            exit(EXIT_FAILURE);
        }

        
        t_start=0.0;
        t_end=0.0;
        sleep(1);

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

        collect_info(t_start,t_end,gflops);

        free(A);
        free(B);
        free(C);
    }
    printf("\n");
    fputs("\n========New Matrixtest========\n"
          "===========2D Array===========\n\n",results);
    secondmain();
    fclose(results);
    return EXIT_SUCCESS;
}


int secondmain() {

    double t_start, t_end;
    double gflops;
    dim = 0;
    printf("\nMatrix matrix multiply example with arrays:\n\n");

    while (dim < max) {
        set_dim();

        double **A = random_mat_A(dim);
        double **B = random_mat_A(dim);
        double **C = zero_mat_A(dim);

        if (A == NULL || B == NULL || C == NULL) {
            printf("Allocation of matrix failed.\n");
            exit(EXIT_FAILURE);
        }
        t_start=0.0;
        t_end=0.0;
        sleep(1);


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

        collect_info(t_start,t_end,gflops);

        free(A);
        free(B);
        free(C);
    }
    printf("\n");
    return EXIT_SUCCESS;
}

void collect_info(double t_start, double t_end, double gflops){
    printf("Dim: %4d\truntime: %7.4fs\tGFLOP/s: %0.2f\n", dim, t_end - t_start, gflops);
    char * c= (char*)malloc(100 * sizeof(char));
    sprintf(c,"Dim: %4d  runtime: %7.4fs  GFLOP/s: %0.2f\n", dim, t_end - t_start, gflops);
    fputs(c,results);
}