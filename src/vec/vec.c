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

void Vec_free_elem(Vec *vec) {
    free(vec->elems);
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

// TODO: implement a proper error propagation mechanism for Vec_dot

double Vec_dot(Vec *v1, Vec *v2) {
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

Vec *Vec_cross(Vec *v1, Vec *v2) {
    if (v1->dim != 3 || v2->dim != 3) {
        set_error("One of v1, v2 is not 3D");
        return NULL;
    }

    // refer notes/vec.md
    double i = (v1->elems[1] * v2->elems[2]) - (v1->elems[2] * v2->elems[1]);
    double j = (v1->elems[0] * v2->elems[2]) - (v1->elems[2] * v2->elems[0]);
    double k = (v1->elems[0] * v2->elems[1]) - (v1->elems[1] * v2->elems[0]);

    double *elems = malloc(sizeof(double) * 3);
    elems[0] = i;
    elems[1] = -j;
    elems[2] = k;

    return Vec_create(3, elems);
}

Vec *Vec_to_unit(Vec *vec) {
}

float Vec_get_angle(Vec *v1, Vec *v2) {
}
