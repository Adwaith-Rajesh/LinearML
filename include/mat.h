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

#ifndef VEC_H
#define VEC_H

typedef struct {
    float *elems;
    int rows;
    int cols;
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
Mat *mat_create(int rows, int cols);

/*
Create a zero matrix of size rows x cols
 */
Mat *mat_create_zeros(int rows, int cols);

/*
Create a size x size identity matrix
 */
Mat *mat_identity(int size);

/*
Display the given matrix
 */
void mat_print(Mat *mat);

/*
Free a Mat
 */
void mat_free(Mat *mat);

#endif
