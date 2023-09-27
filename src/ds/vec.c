#include "ds/vec.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "utils/mem.h"

int vec_print_prec = 4;

void set_vec_print_prec(int prec) {
    vec_print_prec = prec;
}

Vec *vec_create(int dim, float *elems) {
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
            printf(" %.*f ", vec_print_prec, vec->elems[i]);
        }
    }
    puts(")");
}

Vec *vec_add(Vec *v1, Vec *v2) {
    if (v2->dim != v1->dim) {
        fprintf(stderr, "The vectors must be of the same dimensions, got %d and %d",
                v1->dim, v2->dim);
        return NULL;
    }

    for (int i = 0; i < v1->dim; ++i) {
        v1->elems[i] += v2->elems[i];
    }
    return v1;
}

Vec *vec_sub(Vec *v1, Vec *v2) {
    if (v2->dim != v1->dim) {
        fprintf(stderr, "The vectors must be of the same dimensions, got %d and %d",
                v1->dim, v2->dim);
        return NULL;
    }

    for (int i = 0; i < v1->dim; ++i) {
        v1->elems[i] -= v2->elems[i];
    }
    return v1;
}

Vec *vec_scalar_multiply(Vec *vec, float scalar_val) {
    for (int i = 0; i < vec->dim; ++i) {
        vec->elems[i] *= scalar_val;
    }
    return vec;
}

float vec_norm(Vec *vec) {
    float sum = 0;
    for (int i = 0; i < vec->dim; i++) {
        sum += (vec->elems[i]) * (vec->elems[i]);
    }
    return sqrtf(sum);
}

float vec_dot(Vec *v1, Vec *v2) {
    if (v1->dim != v2->dim) {
        fprintf(stderr, "The dimensions of the vector must be the same\n");
        return 0;
    }

    float product = 0.0;
    for (int i = 0; i < v1->dim; i++) {
        product += (v1->elems[i] * v2->elems[i]);
    }
    return product;
}

Vec *vec_cross(Vec *v1, Vec *v2) {
    if (v1->dim != 3 || v2->dim != 3) {
        fprintf(stderr, "Cannot only do cross product on vec that are 3D\n");
        return NULL;
    }

    // refer notes/vec.md
    float i = (v1->elems[1] * v2->elems[2]) - (v1->elems[2] * v2->elems[1]);
    float j = (v1->elems[0] * v2->elems[2]) - (v1->elems[2] * v2->elems[0]);
    float k = (v1->elems[0] * v2->elems[1]) - (v1->elems[1] * v2->elems[0]);

    float *elems = malloc_with_check(sizeof(float) * 3);
    elems[0] = i;
    elems[1] = -j;
    elems[2] = k;

    return vec_create(3, elems);
}

Vec *vec_to_unit(Vec *vec) {
    // refer notes/vec.md
    float norm = vec_norm(vec);

    for (int i = 0; i < vec->dim; i++) {
        vec->elems[i] /= norm;
    }
    return vec;
}

float vec_get_angle(Vec *v1, Vec *v2) {
    // refer notes/vec.md

    float dot_p = vec_dot(v1, v2);
    float n_p = vec_norm(v1) * vec_norm(v2);  // Norm Product

    return acosf(dot_p / n_p);
}
