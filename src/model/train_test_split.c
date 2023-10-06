#include "model/train_test_split.h"

#include <gsl/gsl_matrix.h>
#include <stdlib.h>

#include "ds/mat.h"

void train_test_split(const Mat *X, const Mat *Y, Mat *X_train, Mat *X_test, Mat *Y_train, Mat *Y_test,
                      double test_size, int rand_state) {
    if (X->rows != Y->rows) {
        fprintf(stderr, "train_test_split: The number of values in X and Y must be same of X: %ld and Y: %ld", X->rows, Y->rows);
        exit(EXIT_FAILURE);
    }

    size_t test_n_rows = (size_t)(X->rows * test_size);
    if (test_n_rows == 0) {
        fprintf(stderr, "train_test_split: sample size is too small to split.");
        exit(EXIT_FAILURE);
    }

    size_t train_n_rows = X->rows - test_n_rows;
}
