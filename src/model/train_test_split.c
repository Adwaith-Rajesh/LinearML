#include "model/train_test_split.h"

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ds/mat.h"

void train_test_split(Mat *X, Mat *Y, Mat **X_train, Mat **X_test, Mat **Y_train, Mat **Y_test,
                      double test_size, int rand_state) {
    if (X->rows != Y->rows) {
        fprintf(stderr, "train_test_split: The number of values in X and Y must be same of X: %ld and Y: %ld", X->rows, Y->rows);
        exit(EXIT_FAILURE);
    }

    size_t n_rows = X->rows;
    size_t test_n_rows = (size_t)(n_rows * test_size);
    if (test_n_rows == 0) {
        fprintf(stderr, "train_test_split: sample size is too small to split.");
        exit(EXIT_FAILURE);
    }

    size_t train_n_rows = n_rows - test_n_rows;

    // shuffle the two Mat X, Y using Fisher-Yates Algorithm
    // refer: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle

    srand(rand_state);

    for (size_t i = n_rows - 1; i > 0; i--) {
        size_t j = rand() % i;

        gsl_matrix_swap_rows(X->mat, i, j);
        gsl_matrix_swap_rows(Y->mat, i, j);
    }

    *X_test = mat_create(test_n_rows, X->cols);
    *Y_test = mat_create(test_n_rows, Y->cols);
    *X_train = mat_create(train_n_rows, X->cols);
    *Y_train = mat_create(train_n_rows, Y->cols);

    gsl_vector *x_temp = gsl_vector_alloc(X->cols);
    gsl_vector *y_temp = gsl_vector_alloc(Y->cols);

    for (size_t i = 0; i < test_n_rows; i++) {
        gsl_matrix_get_row(x_temp, X->mat, i);
        gsl_matrix_set_row((*X_test)->mat, i, x_temp);

        gsl_matrix_get_row(y_temp, Y->mat, i);
        gsl_matrix_set_row((*Y_test)->mat, i, y_temp);
    }

    for (size_t i = 0; i < train_n_rows; i++) {
        gsl_matrix_get_row(x_temp, X->mat, i + test_n_rows);
        gsl_matrix_set_row((*X_train)->mat, i, x_temp);

        gsl_matrix_get_row(y_temp, Y->mat, i + test_n_rows);
        gsl_matrix_set_row((*Y_train)->mat, i, y_temp);
    }

    gsl_vector_free(x_temp);
    gsl_vector_free(y_temp);
}
