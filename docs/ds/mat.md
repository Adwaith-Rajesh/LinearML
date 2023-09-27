# Mat

#### Structure

```c
typedef struct {
    float *elems;
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
void mat_printp(Mat *mat, int print_prec);

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
```

- #### 2. Examples.

Here is a simple example on finding the inverse of a matrix

```c
#include <stdio.h>

#include "ds/mat.h"

int main(void) {
    Mat *mat = mat_create(2, 2);

    MAT_AT(mat, 0, 0) = 4;
    MAT_AT(mat, 0, 1) = 7;

    MAT_AT(mat, 1, 0) = 2;
    MAT_AT(mat, 1, 1) = 6;

    mat_printp(mat, 5);
    printf("\n");

    Mat *adj = mat_adj(mat);
    mat_print(adj);

    printf("\n");

    Mat *inv = mat_inverse(mat);
    mat_printp(inv, 7);

    mat_free(mat);
    mat_free(adj);
    mat_free(inv);

    return 0;
}
```

```console
  4.00000   7.00000
  2.00000   6.00000

  6.00   -7.00
  -2.00   4.00

  0.6000000   -0.7000000
  -0.2000000   0.4000000
```

> If you have any queries feel free to contact me through any of the socials given below
