#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils/mem.h"

int mat_print_prec = 2;

void set_mat_print_prec(int prec) {
    mat_print_prec = prec;
}

void mat_print(Mat *mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%.*lf ", mat_print_prec, MAT_AT(mat, i, j));
        }
        printf("\n");
    }
}

Mat *mat_create(int rows, int cols) {
    Mat *new_mat = malloc_with_check(sizeof(Mat));
    new_mat->elems = malloc_with_check(sizeof(double *) * rows * cols);
    new_mat->rows = rows;
    new_mat->cols = cols;
    return new_mat;
}

void mat_free(Mat *mat) {
    if (mat == NULL) return;
    free(mat->elems);
    free(mat);
}
