#include "vec.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils/mem.h"

Vec *Vec_create(int dim, double *elems) {
    Vec *new_vec = malloc_with_check(sizeof(Vec));
    new_vec->dim = dim;
    new_vec->elems = elems;
    return new_vec;
}

void Vec_free(Vec *vec) {
    free(vec);
}

void Vec_display(Vec *vec) {
    printf("(");
    for (int i = 0; i < vec->dim; i++) {
        printf(" %lf ", vec->elems[i]);
    }
    puts(")");
}
