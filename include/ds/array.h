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

// A simple way to store the array and the size
// for my use case the the array is float array

#ifndef LINEAR_ML_ARRAY_H
#define LINEAR_ML_ARRAY_H

#include <stddef.h>

typedef struct {
    size_t size;
    float *arr;
} Array;

#define ARR_AT(i_arr, idx) ((i_arr)->arr[idx])

/*
Creates an array of the specified size and returns it

you have to free it using arr_free
*/
Array *arr_create(size_t size);

/*
Creates an array using an existing C array and returns an Array

you have to free it using arr_init_free
*/
Array *arr_init(float *arr, size_t size);

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
void arr_print(Array *arr);

typedef float (*ArrayMapFuncType)(float);

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
