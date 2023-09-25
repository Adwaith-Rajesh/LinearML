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

#include <stddef.h>

typedef struct {
    float *elems;
    size_t rows;
    size_t cols;
} Mat;

#define MAT_AT(m, r, c) (m)->elems[c + (m)->cols * r]

// global variable that defines the number of decimal places printed
extern int mat_print_prec;

/*
Set the printing precision for mat_print
*/
void set_mat_print_prec(int prec);

/*
Create a rows x cols matrix
*/
Mat *mat_create(size_t rows, size_t cols);

/*
Create a Mat from an existing array
*/
Mat *mat_create_from_array(float *arr, size_t rows, size_t cols);

/*
Create a zero matrix of size rows x cols
*/
Mat *mat_create_zeros(size_t rows, size_t cols);

/*
Create a size x size identity matrix
*/
Mat *mat_identity(size_t size);

/*
Display the given matrix
*/
void mat_print(Mat *mat);

/*
Free a Mat
*/
void mat_free(Mat *mat);

/*
Free mat with user created arr
*/
void mat_free_no_array(Mat *mat);

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
Mat *mat_scalar_mul(Mat *mat, float val);

/*
Returns a new matrix that is the transpose of the given mat

you need to free the new matrix
*/
Mat *mat_transpose(Mat *mat);

/*
Find the determinant of a matrix
*/
float mat_det(Mat *mat);

/*
Find the cofactor of a given elements in Mat
*/
float mat_cofactor(Mat *mat, size_t row, size_t col);

/*
Returns a new Mat, that is the cofactor matrix of the given Mat

You need to free the returned Mat
*/
Mat *mat_cofactor_matrix(Mat *mat);

/*
Returns a new Mat that is the adjoint of the given Mat

You need to free the returned Mat;
*/
Mat *mat_adj(Mat *mat);

/*
Return a new Mat that is the inverse of the given Mat

You need to free the returned Mat
*/
Mat *mat_inverse(Mat *mat);

#endif
