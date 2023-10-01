/*
LinearML - A Linear Algebra and Machine Learning "Library" in C
Copyright (c) 2023 Adwaith Rajesh <adwaithrajesh3180[at]gmail[dot]com>

LICENSE: MIT

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MAT_H
#define MAT_H

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
You need to free the returned Mat
*/
Mat *mat_inverse(Mat *mat);

/*
Returns a copy of the given matrix
*/
Mat *mat_cpy(Mat *mat);

#endif
