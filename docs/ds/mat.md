# Mat

#### Structure

```c
typedef struct {
    gsl_matrix *mat;
    size_t rows;
    size_t cols;
} Mat;

```

Internally the Matrix is 1D array where the values are stored in row major order.

- #### 1. Available functions.

```c

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
```

- #### 2. Examples.

Here is a simple example on finding the inverse of a matrix

```c
#include <stdio.h>

#include "ds/mat.h"

int main(void) {
    Mat *mat = mat_create(2, 2);

    mat_set(mat, 0, 0, 4);
    mat_set(mat, 0, 1, 7);

    mat_set(mat, 1, 0, 2);
    mat_set(mat, 1, 1, 6);

    mat_printp(mat, 5);
    printf("\n");

    Mat *inv = mat_inverse(mat);
    mat_printp(inv, 7);

    mat_free(mat);
    mat_free(inv);

    return 0;
}
```

```console
  4.00000   7.00000
  2.00000   6.00000

  0.6000000   -0.7000000
  -0.2000000   0.4000000

```

> If you have any queries feel free to contact me through any of the socials given below
