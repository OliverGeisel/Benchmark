//
// Created by Oliver on 5/3/2018.
//

#include "matrixPointer.h"
#include <stdlib.h>
#include <stdint.h>
#include <time.h>





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

