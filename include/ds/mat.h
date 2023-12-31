/*
LinearML - A Linear Algebra and Machine Learning "Library" in C
Copyright (c) 2023 Adwaith Rajesh <adwaithrajesh3180[at]gmail[dot]com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DS_MAT_H
#define DS_MAT_H

#include <gsl/gsl_matrix.h>
#include <stddef.h>

typedef struct {
    gsl_matrix *mat;
    size_t rows;
    size_t cols;
} Mat;

#define mat_print(matrix) mat_printp(matrix, 2)

/*
Create a rows x cols matrix
*/
Mat *mat_create(size_t rows, size_t cols);

/*
Create a Mat from an existing array
*/
Mat *mat_create_from_array(double *arr, size_t rows, size_t cols);

/*
Create a zero matrix of size rows x cols
*/
Mat *mat_create_zeros(size_t rows, size_t cols);

/*
Create a size x size identity matrix
*/
Mat *mat_identity(size_t size);

/*
get value at mat[row, col]
*/
double mat_get(Mat *mat, size_t row, size_t col);

/*
Set mat[row, col] = val, and return the mat
*/
Mat *mat_set(Mat *mat, size_t row, size_t col, double val);

/*
Display the given matrix
*/
void mat_printp(Mat *mat, int print_prec);

/*
Free a Mat
*/
void mat_free(Mat *mat);

/*
Free count number of Mat's
*/
void mat_free_many(int count, ...);

/*
Add two Mat of the same dimension

Adds mat2 to mat1 and returns mat1
*/
Mat *mat_add(Mat *mat1, Mat *mat2);

/*
Subtract two Mat of the same dimension

Subtract mat2 from mat1 and returns mat1
*/
Mat *mat_sub(Mat *mat1, Mat *mat2);

/*
Multiplies mat1 and mat2 and returns a new Mat

you need to free the new Mat
*/
Mat *mat_mul(Mat *mat1, Mat *mat2);

/*
Multiplies a scalar value to the Mat and returns the given mat
*/
Mat *mat_scalar_mul(Mat *mat, double val);

/*
Returns a new matrix that is the transpose of the given mat

you need to free the new matrix
*/
Mat *mat_transpose(Mat *mat);

/*
Find the determinant of a matrix
*/
double mat_det(Mat *mat);

/*
Find the inverse of the given mat using LU decomposition

You need to free the returned Mat
*/
Mat *mat_inverse(Mat *mat);

/*
returns and inverse of MxN matrix using SVD
*/
Mat *mat_invert_svd(Mat *mat);

/*
Returns a copy of the given matrix
*/
Mat *mat_cpy(Mat *mat);

#ifdef INCLUDE_MAT_CONVERSIONS
#include <gsl/gsl_vector.h>

#include "ds/array.h"

/*
Get a matrix col as an Array
*/

Array *mat_get_col_arr(Mat *mat, size_t col) {
    gsl_vector *col_vec = gsl_vector_alloc(mat->rows);
    Array *arr = arr_create(mat->rows);

    gsl_matrix_get_col(col_vec, mat->mat, col);

    for (size_t i = 0; i < col_vec->size; i++) {
        arr->arr[i] = col_vec->data[i];
    }

    gsl_vector_free(col_vec);
    return arr;
}

/*
Get a matrix  row as an Array
*/
Array *mat_get_row_arr(Mat *mat, size_t row) {
    gsl_vector *row_vec = gsl_vector_alloc(mat->cols);
    Array *arr = arr_create(mat->cols);

    gsl_matrix_get_row(row_vec, mat->mat, row);

    for (size_t i = 0; i < row_vec->size; i++) {
        arr->arr[i] = row_vec->data[i];
    }

    gsl_vector_free(row_vec);
    return arr;
}

#endif

#endif
