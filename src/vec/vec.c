#include "vec.h"

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "utils/internal.h"
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
    if (vec != NULL) {
        for (int i = 0; i < vec->dim; i++) {
            printf(" %lf ", vec->elems[i]);
        }
    }
    puts(")");
}

Vec *Vec_add(Vec *v1, Vec *v2) {
    if (v2->dim != v1->dim) {
        set_error("The vectors must be of the same dimensions, got %d and %d",
                  v1->dim, v2->dim);
        return NULL;
    }

    for (int i = 0; i < v1->dim; ++i) {
        v1->elems[i] += v2->elems[i];
    }
    return v1;
}

Vec *Vec_sub(Vec *v1, Vec *v2) {
    if (v2->dim != v1->dim) {
        set_error("The vectors must be of the same dimensions, got %d and %d",
                  v1->dim, v2->dim);
        return NULL;
    }

    for (int i = 0; i < v1->dim; ++i) {
        v1->elems[i] -= v2->elems[i];
    }
    return v1;
}
