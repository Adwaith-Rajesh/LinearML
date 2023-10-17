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

// A simple way to store the array and the size
// for my use case the the array is double array

#ifndef LINEAR_ML_ARRAY_H
#define LINEAR_ML_ARRAY_H

#include <stddef.h>

typedef struct {
    size_t size;
    double *arr;
} Array;

#define ARR_AT(i_arr, idx) ((i_arr)->arr[idx])

#define arr_print(array) arr_printp(array, 2)

/*
Creates an array of the specified size and returns it

you have to free it using arr_free
*/
Array *arr_create(size_t size);

/*
Creates an array using an existing C array and returns an Array

you have to free it using arr_init_free
*/
Array *arr_init(double *arr, size_t size);

/*
Frees an Array crated using arr_create
*/
void arr_free(Array *arr);

/*
Frees an Array crated using arr_init
*/
void arr_init_free(Array *arr);

/*
Display the given array
*/
void arr_printp(Array *arr, int print_prec);

typedef double (*ArrayMapFuncType)(double);

/*
Map a function over the given array and returns the same array
*/
Array *arr_map(Array *arr, ArrayMapFuncType fn);

#ifdef INCLUDE_ARRAY_STATS

#include "stats/stats.h"

/* mean of an array */
#define arr_mean(arr) (stats_mean(arr->arr, arr->size))

/* max value of an array */
#define arr_max(arr) (stats_max(arr->arr, arr->size))

/* min value of an array */
#define arr_min(arr) (stats_min(arr->arr, arr->size))

#endif

#endif
