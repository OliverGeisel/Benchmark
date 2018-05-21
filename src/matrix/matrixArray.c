//
// Created by Oliver on 5/3/2018.
//
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "matrixArray.h"

double **zero_mat_A(uint32_t dim) {
    double **matrix = (double **) malloc(sizeof(double*) *dim );
    if (matrix == NULL) {
        return NULL;
    }

    for (uint32_t i = 0; i < dim; ++i) {
        matrix[i]=(double*)malloc(sizeof(double)*dim);
        for (uint32_t j = 0; j < dim; j++)
            matrix[i][j] =  0.0;
    }

    return matrix;
}


double **random_mat_A(uint32_t dim) {
    double **matrix = (double **) malloc(sizeof(double*) *dim );
    if (matrix == NULL) {
        return NULL;
    }

    srand((unsigned) time(NULL));

    for (uint32_t i = 0; i < dim; ++i) {
        matrix[i]=(double*)malloc(sizeof(double)*dim);
        for (uint32_t j = 0; j < dim; j++) {
            matrix[i][j] = rand();
        }
    }

    return matrix;
}