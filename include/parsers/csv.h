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

#ifndef PARSERS_CSV_H
#define PARSERS_CSV_H

#include <stddef.h>

#include "ds/mat.h"
#include "ds/str.h"

typedef struct {
    size_t cols;
    size_t rows;
    Mat *values;
    char delim;
} CSV;

typedef struct {
    size_t lower;
    size_t upper;  // non inclusive
} Slice;

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

if a StrList is provided the strings will be automatically added to the list

*/
CSV *csv_parse(CSV *csv, const char *filename, StrList *str_list);

/*
Returns a new Mat with only the selected cols
*/
Mat *csv_get_mat(CSV *csv, int *rows, size_t c_size);

/*
Returns a new Mat with only the selected cols using Slice type
*/

Mat *csv_get_mat_slice(CSV *csv, Slice slice);

#endif
