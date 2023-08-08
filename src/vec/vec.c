#include "vec.h"

#include <math.h>
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

void Vec_print(Vec *vec) {
    printf("(");
    if (vec != NULL) {
        for (int i = 0; i < vec->dim; i++) {
            printf(" %lf ", vec->elems[i]);
        }
    }
    puts(")");
}

Vec *Vec_add(Vec *v1, Vec *v2) {
    check_null(v1, NULL);
    check_null(v2, NULL);
    if (v2->dim != v1->dim) {
        set_errorf("The vectors must be of the same dimensions, got %d and %d",
                   v1->dim, v2->dim);
        return NULL;
    }

    for (int i = 0; i < v1->dim; ++i) {
        v1->elems[i] += v2->elems[i];
    }
    return v1;
}

Vec *Vec_sub(Vec *v1, Vec *v2) {
    check_null(v1, NULL);
    check_null(v2, NULL);
    if (v2->dim != v1->dim) {
        set_errorf("The vectors must be of the same dimensions, got %d and %d",
                   v1->dim, v2->dim);
        return NULL;
    }

    for (int i = 0; i < v1->dim; ++i) {
        v1->elems[i] -= v2->elems[i];
    }
    return v1;
}

Vec *Vec_scalar_multiply(Vec *vec, double scalar_val) {
    check_null(vec, NULL);
    for (int i = 0; i < vec->dim; ++i) {
        vec->elems[i] *= scalar_val;
    }
    return vec;
}

double Vec_norm(Vec *vec) {
    check_null(vec, -1);
    double sum = 0;
    for (int i = 0; i < vec->dim; i++) {
        sum += (vec->elems[i]) * (vec->elems[i]);
    }
    return sqrt(sum);
}

// TODO: implement a proper error propagation mechanism for Vec_dot_product

double Vec_dot_product(Vec *v1, Vec *v2) {
    check_null(v1, 0);  // FIXME: The dot product can result in a zero
    check_null(v2, 0);

    if (v1->dim != v2->dim) {
        set_errorf("The vectors must be of the same dimensions, got %d and %d",
                   v1->dim, v2->dim);
        return 0;  // FIXME: Return Zero is not a proper indication of error
    }

    double product = 0.0;
    for (int i = 0; i < v1->dim; i++) {
        product += (v1->elems[i] * v2->elems[i]);
    }
    return product;
}
