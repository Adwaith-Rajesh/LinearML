#include "ds/mat.h"

#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils/mem.h"

void mat_printp(Mat *mat, int print_prec) {
    if (mat == NULL) {
        fprintf(stderr, "The mat is NULL\n");
        return;
    }

    for (size_t i = 0; i < mat->rows; i++) {
        for (size_t j = 0; j < mat->cols; j++) {
            printf("  %.*lf ", print_prec, gsl_matrix_get(mat->mat, i, j));
        }
        printf("\n");
    }
}

Mat *mat_create(size_t rows, size_t cols) {
    Mat *new_mat = malloc_with_check(sizeof(Mat));
    new_mat->mat = gsl_matrix_alloc(rows, cols);
    new_mat->rows = rows;
    new_mat->cols = cols;
    return new_mat;
}

Mat *mat_create_from_array(double *arr, size_t rows, size_t cols) {
    Mat *new_mat = mat_create(rows, cols);

    for (size_t r = 0; r < rows; r++) {
        for (size_t c = 0; c < cols; c++) {
            gsl_matrix_set(new_mat->mat, r, c, arr[(r * cols) + c]);
        }
    }
    return new_mat;
}

Mat *mat_create_zeros(size_t rows, size_t cols) {
    Mat *new_mat = malloc_with_check(sizeof(Mat));
    new_mat->mat = gsl_matrix_calloc(rows, cols);
    new_mat->rows = rows;
    new_mat->cols = cols;
    return new_mat;
}

Mat *mat_identity(size_t size) {
    Mat *new_mat = mat_create(size, size);
    gsl_matrix_set_identity(new_mat->mat);
    return new_mat;
}

double mat_get(Mat *mat, size_t row, size_t col) {
    if (mat == NULL) {
        fprintf(stderr, "mat_get: mat is null, returning 0.0\n");
        return 0.0;
    }
    return gsl_matrix_get(mat->mat, row, col);
}

Mat *mat_set(Mat *mat, size_t row, size_t col, double val) {
    if (mat == NULL) {
        fprintf(stderr, "mat_set: mat us NULL, returning NULL\n");
        return NULL;
    }

    gsl_matrix_set(mat->mat, row, col, val);
    return mat;
}

void mat_free(Mat *mat) {
    if (mat == NULL) return;
    if (mat->mat != NULL) {
        gsl_matrix_free(mat->mat);
    }
    free(mat);
}

Mat *mat_add(Mat *mat1, Mat *mat2) {
    if (mat1->rows != mat2->rows && mat1->cols != mat2->cols) {
        return NULL;
    }

    gsl_matrix_add(mat1->mat, mat2->mat);
    return mat1;
}

Mat *mat_sub(Mat *mat1, Mat *mat2) {
    if (mat1->rows != mat2->rows && mat1->cols != mat2->cols) {
        return NULL;
    }

    gsl_matrix_sub(mat1->mat, mat2->mat);
    return mat1;
}

Mat *mat_mul(Mat *mat1, Mat *mat2) {
    if (mat1 == NULL || mat2 == NULL) {
        return NULL;
    }

    if (mat1->cols != mat2->rows) {
        return NULL;
    }

    Mat *res_mat = mat_create(mat1->rows, mat2->cols);

    gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, mat1->mat, mat2->mat, 0.0, res_mat->mat);

    return res_mat;
}

Mat *mat_scalar_mul(Mat *mat, double val) {
    gsl_matrix_scale(mat->mat, val);
    return mat;
}

Mat *mat_transpose(Mat *mat) {
    if (mat == NULL) {
        return NULL;
    }

    Mat *new_mat = mat_create(mat->cols, mat->rows);
    gsl_matrix_transpose_memcpy(new_mat->mat, mat->mat);
    return new_mat;
}

double mat_det(Mat *mat) {
    if (mat == NULL) {
        fprintf(stderr, "mat_det: mat is NULL, returning 0.");
        return 0.0;
    }
    gsl_permutation *p = gsl_permutation_alloc(mat->rows);

    int signum;
    gsl_linalg_LU_decomp(mat->mat, p, &signum);

    double det = gsl_linalg_LU_det(mat->mat, signum);

    gsl_permutation_free(p);

    return det;
}

Mat *mat_inverse(Mat *mat) {
    if (mat == NULL) return NULL;

    gsl_permutation *p = gsl_permutation_alloc(mat->rows);

    int signum;
    gsl_linalg_LU_decomp(mat->mat, p, &signum);

    Mat *invert = mat_create(mat->rows, mat->cols);
    gsl_linalg_LU_invert(mat->mat, p, invert->mat);

    gsl_permutation_free(p);
    return invert;
}

Mat *mat_cpy(Mat *mat) {
    Mat *new_mat = mat_create(mat->rows, mat->cols);
    gsl_matrix_memcpy(new_mat->mat, mat->mat);
    return new_mat;
}
