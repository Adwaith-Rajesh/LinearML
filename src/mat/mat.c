#include "mat.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils/mem.h"

int mat_print_prec = 2;

static void _set_zeros(float *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = 0.0f;
    }
}

void set_mat_print_prec(int prec) {
    mat_print_prec = prec;
}

void mat_print(Mat *mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%.*f ", mat_print_prec, MAT_AT(mat, i, j));
        }
        printf("\n");
    }
}

Mat *mat_create(int rows, int cols) {
    Mat *new_mat = malloc_with_check(sizeof(Mat));
    new_mat->elems = malloc_with_check(sizeof(float) * rows * cols);
    new_mat->rows = rows;
    new_mat->cols = cols;
    return new_mat;
}

Mat *mat_create_zeros(int rows, int cols) {
    Mat *new_mat = malloc_with_check(sizeof(Mat));
    new_mat->elems = malloc_with_check(sizeof(float) * rows * cols);
    new_mat->rows = rows;
    new_mat->cols = cols;
    _set_zeros(new_mat->elems, rows * cols);
    return new_mat;
}

void mat_free(Mat *mat) {
    if (mat == NULL) return;
    free(mat->elems);
    free(mat);
}
