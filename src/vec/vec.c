#include "vec.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "utils/internal.h"
#include "utils/mem.h"

Vec *vec_create(int dim, double *elems) {
    Vec *new_vec = malloc_with_check(sizeof(Vec));
    new_vec->dim = dim;
    new_vec->elems = elems;
    return new_vec;
}

void vec_free(Vec *vec) {
    free(vec);
}

void vec_free_elem(Vec *vec) {
    free(vec->elems);
    free(vec);
}

void vec_print(Vec *vec) {
    printf("(");
    if (vec != NULL) {
        for (int i = 0; i < vec->dim; i++) {
            printf(" %lf ", vec->elems[i]);
        }
    }
    puts(")");
}

Vec *vec_add(Vec *v1, Vec *v2) {
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

Vec *vec_sub(Vec *v1, Vec *v2) {
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

Vec *vec_scalar_multiply(Vec *vec, double scalar_val) {
    check_null(vec, NULL);
    for (int i = 0; i < vec->dim; ++i) {
        vec->elems[i] *= scalar_val;
    }
    return vec;
}

double vec_norm(Vec *vec) {
    check_null(vec, -1);
    double sum = 0;
    for (int i = 0; i < vec->dim; i++) {
        sum += (vec->elems[i]) * (vec->elems[i]);
    }
    return sqrt(sum);
}

// TODO: implement a proper error propagation mechanism for vec_dot

double vec_dot(Vec *v1, Vec *v2) {
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

Vec *vec_cross(Vec *v1, Vec *v2) {
    if (v1->dim != 3 || v2->dim != 3) {
        set_error("One of v1, v2 is not 3D");
        return NULL;
    }

    // refer notes/vec.md
    double i = (v1->elems[1] * v2->elems[2]) - (v1->elems[2] * v2->elems[1]);
    double j = (v1->elems[0] * v2->elems[2]) - (v1->elems[2] * v2->elems[0]);
    double k = (v1->elems[0] * v2->elems[1]) - (v1->elems[1] * v2->elems[0]);

    double *elems = malloc_with_check(sizeof(double) * 3);
    elems[0] = i;
    elems[1] = -j;
    elems[2] = k;

    return vec_create(3, elems);
}

Vec *vec_to_unit(Vec *vec) {
    check_null(vec, NULL);

    // refer notes/vec.md
    double norm = vec_norm(vec);

    for (int i = 0; i < vec->dim; i++) {
        vec->elems[i] /= norm;
    }
    return vec;
}

float vec_get_angle(Vec *v1, Vec *v2) {
    // refer notes/vec.md

    double dot_p = vec_dot(v1, v2);
    double n_p = vec_norm(v1) * vec_norm(v2);  // Norm Product

    return acos(dot_p / n_p);
}
