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

/*
The LinearML CSV parser will only work for float values.
Making the parser compatible for string values is not necessary as these values
can substituted by floats by the user.

eg.

Original CSV.

s_no,age,in_school
1,10,yes
2,20,no
3,1,no

CSV for LinearML (remove the header, and replace all string vals)

1,10,1
2,20,0
3,1,0

Here 1 represents a yes and 0 a no
*/

#ifndef INCLUDE_LINEAR_ML_CSV_H
#define INCLUDE_LINEAR_ML_CSV_H

#include <stddef.h>

#include "ds/mat.h"

typedef struct {
    size_t cols;
    size_t rows;
    Mat *values;
    char delim;
} CSV;

/*
Initialize the CSV reader/parser

the number rows should not include the header.
*/
CSV *csv_init(size_t rows, size_t cols, char delim);

/*
Free the CSV reader
*/
void csv_free(CSV *csv);

/*
Display the parsed CSV
*/
void csv_print(CSV *csv);

/*
Parse the given CSV file
*/
CSV *csv_parse(CSV *csv, const char *filename);

/*
Returns a new Mat with only the selected cols
*/
Mat *csv_get_mat(CSV *csv, int *rows, size_t c_size);

#endif
