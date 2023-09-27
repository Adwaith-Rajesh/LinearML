#include "array.h"

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

void arr_print(Array *arr) {
    if (arr == NULL) return;
    for (size_t i = 0; i < arr->size; i++) {
        printf("%f ", ARR_AT(arr, i));
    }
    printf("\n");
}

Array *arr_map(Array *arr, ArrayMapFuncType fn) {
    for (size_t i = 0; i < arr->size; i++) {
        ARR_AT(arr, i) = fn(ARR_AT(arr, i));
    }
    return arr;
}
