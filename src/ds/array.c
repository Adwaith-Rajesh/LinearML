#include "ds/array.h"

#include <stdio.h>

#include "utils/mem.h"

Array *arr_create(size_t size) {
    Array *new_arr = malloc_with_check(sizeof(Array));
    new_arr->size = size;
    new_arr->arr = malloc_with_check(sizeof(float) * size);
    return new_arr;
}

Array *arr_init(float *arr, size_t size) {
    Array *new_arr = malloc_with_check(sizeof(Array));
    new_arr->size = size;
    new_arr->arr = arr;
    return new_arr;
}

void arr_free(Array *arr) {
    if (arr == NULL) return;
    if (arr->arr != NULL) {
        free(arr->arr);
    }
    free(arr);
}

void arr_init_free(Array *arr) {
    if (arr == NULL) return;
    free(arr);
}

void arr_printp(Array *arr, int print_prec) {
    if (arr == NULL) return;

    printf("[ ");
    if (arr->size <= 20) {
        for (size_t i = 0; i < arr->size; i++) {
            printf("%.*f ", print_prec, ARR_AT(arr, i));
        }
    } else {
        // print rows of 15 values
        int count = 0;
        for (size_t i = 0; i < arr->size; i++) {
            if (count == 15) {
                printf("\n  ");
                count = 0;
            }
            count++;
            printf("%.*f ", print_prec, ARR_AT(arr, i));
        }
    }

    printf("]\n");
}

Array *arr_map(Array *arr, ArrayMapFuncType fn) {
    for (size_t i = 0; i < arr->size; i++) {
        ARR_AT(arr, i) = fn(ARR_AT(arr, i));
    }
    return arr;
}
