//
// Created by Oliver on 5/3/2018.
//

#include "matrixPointer.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <x86intrin.h>
#include <stdint-gcc.h>


/** @brief Get current time stamp in seconds.
 *
 *  @return         Returns current time stamp in seconds.
 */
 double gtod() {
    struct timeval act_time;
    gettimeofday(&act_time, NULL);

    return (double) act_time.tv_sec + (double) act_time.tv_usec / 1000000.0;
}


/** @brief Generate randomized matrix.
 *
 *  @param dim      Dimension for the generated matrix.
 *
 *  @return         Returns a pointer to the generated matrix on success, NULL
 *                  otherwise.
 */
 double *random_mat(uint32_t dim) {
    double *matrix = (double *) malloc(sizeof(double) * dim * dim);
    if (matrix == NULL) {
        return NULL;
    }

    srand((unsigned) time(NULL));

    for (uint32_t i = 0; i < dim * dim; ++i) {
        matrix[i] = (double) rand();
    }

    return matrix;
}


/** @brief Generate zero matrix.
 *
 *  @param dim      Dimension for the generated matrix.
 *
 *  @return         Returns a pointer to the generated matrix on success, NULL
 *                  otherwise.
 */
 double *zero_mat(uint32_t dim) {
    double *matrix = (double *) malloc(sizeof(double) * dim * dim);
    if (matrix == NULL) {
        return NULL;
    }

    for (uint32_t i = 0; i < dim * dim; ++i) {
        matrix[i] = (double) 0.0;
    }

    return matrix;
}

