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
    if (mat == NULL) {
        fprintf(stderr, "The mat is NULL\n");
        return;
    }

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

Mat *mat_identity(int size) {
    Mat *new_mat = malloc_with_check(sizeof(Mat));
    new_mat->elems = malloc_with_check(sizeof(float) * size * size);
    new_mat->rows = size;
    new_mat->cols = size;
    _set_zeros(new_mat->elems, size * size);

    for (int i = 0; i < size; i++) {
        MAT_AT(new_mat, i, i) = 1.0f;
    }
    return new_mat;
}

void mat_free(Mat *mat) {
    if (mat == NULL) return;
    free(mat->elems);
    free(mat);
}

Mat *mat_add(Mat *mat1, Mat *mat2) {
    if (mat1->rows != mat2->rows && mat1->cols != mat2->cols) {
        return NULL;
    }

    for (int i = 0; i < mat1->rows * mat2->rows; i++) {
        mat1->elems[i] += mat2->elems[i];
    }
    return mat1;
}

Mat *mat_sub(Mat *mat1, Mat *mat2) {
    if (mat1->rows != mat2->rows && mat1->cols != mat2->cols) {
        return NULL;
    }

    for (int i = 0; i < mat1->rows * mat2->rows; i++) {
        mat1->elems[i] -= mat2->elems[i];
    }
    return mat1;
}

Mat *mat_mul(Mat *mat1, Mat *mat2) {
    if (mat1 == NULL || mat2 == NULL) {
        return NULL;
    }

    if (mat1->cols != mat2->rows) {
        return NULL;
    }

    Mat *res_mat = mat_create_zeros(mat1->rows, mat2->cols);

    for (int r = 0; r < mat1->rows; r++) {
        for (int c = 0; c < mat2->cols; c++) {
            for (int k = 0; k < mat2->rows; k++) {
                MAT_AT(res_mat, r, c) += MAT_AT(mat1, r, k) * MAT_AT(mat2, k, c);
            }
        }
    }

    return res_mat;
}

Mat *mat_scalar_mul(Mat *mat, float val) {
    for (int i = 0; i < mat->cols * mat->rows; i++) {
        mat->elems[i] *= val;
    }
    return mat;
}

Mat *mat_transpose(Mat *mat) {
    if (mat == NULL) {
        return NULL;
    }

    Mat *new_mat = mat_create(mat->cols, mat->rows);
    for (int r = 0; r < mat->rows; r++) {
        for (int c = 0; c < mat->cols; c++) {
            MAT_AT(new_mat, c, r) = MAT_AT(mat, r, c);
        }
    }
    return new_mat;
}

float mat_det(Mat *mat) {
    if (mat == NULL) {
        fprintf(stderr, "mat_det: mat is NULL\n");
        return 0.0f;
    }

    if (mat->rows != mat->cols) {
        fprintf(stderr, "mat_det: mat is not a square matrix\n");
        return 0.0f;
    }

    if (mat->cols == 1) {  // 1 x 1 matrix
        return MAT_AT(mat, 0, 0);
    }

    if (mat->cols == 2) {  // 2 x 2 matrix
        return MAT_AT(mat, 0, 0) * MAT_AT(mat, 1, 1) - MAT_AT(mat, 0, 1) * MAT_AT(mat, 1, 0);
    }

    float det = 0;
    Mat *sub_mat = mat_create(mat->rows - 1, mat->cols - 1);

    for (int col = 0; col < mat->cols; col++) {
        int sub_row = 0;
        for (int i = 1; i < mat->cols; i++) {
            int sub_col = 0;
            for (int j = 0; j < mat->cols; j++) {
                if (j != col) {
                    MAT_AT(sub_mat, sub_row, sub_col) = MAT_AT(mat, i, j);
                    sub_col++;
                }
            }
            sub_row++;
        }
        int sign = (col % 2 == 0) ? 1 : -1;
        det += sign * MAT_AT(mat, 0, col) * mat_det(sub_mat);
    }

    mat_free(sub_mat);
    return det;
}

float mat_cofactor(Mat *mat, int row, int col) {
    if (mat == NULL) {
        fprintf(stderr, "mat_cofactor: mat is NULL\n");
        return 0.0f;
    }

    Mat *sub_mat = mat_create(mat->rows - 1, mat->cols - 1);

    // add the values of the sub matrix
    int s_row = 0;
    for (int r = 0; r < mat->rows; r++) {
        if (r == row) continue;
        int s_col = 0;
        for (int c = 0; c < mat->cols; c++) {
            if (c == col) continue;
            MAT_AT(sub_mat, s_row, s_col) = MAT_AT(mat, r, c);
            s_col++;
        }
        s_row++;
    }

    float sign = ((row + col) % 2 == 0) ? 1.0f : -1.0f;
    float cofactor = sign * mat_det(sub_mat);
    mat_free(sub_mat);
    return cofactor;
}

Mat *mat_cofactor_matrix(Mat *mat) {
    if (mat == NULL) {
        fprintf(stderr, "mat_cofactor_matrix: mat is NULL\n");
        return NULL;
    }

    Mat *cof_mat = mat_create(mat->rows, mat->cols);

    for (int r = 0; r < mat->rows; r++) {
        for (int c = 0; c < mat->cols; c++) {
            MAT_AT(cof_mat, r, c) = mat_cofactor(mat, r, c);
        }
    }
    return cof_mat;
}

Mat *mat_adj(Mat *mat) {
    Mat *cof_mat = mat_cofactor_matrix(mat);
    Mat *cof_tran_mat = mat_transpose(cof_mat);
    mat_free(cof_mat);
    return cof_tran_mat;
}
