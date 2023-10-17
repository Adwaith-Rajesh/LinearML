#include "ml/logisticregress.h"

#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_vector.h>
#include <math.h>

#include "ds/array.h"
#include "ds/mat.h"
#include "utils/mem.h"

size_t MAX_ITER = 100;

void logregress_set_max_iter(size_t iter) {
    MAX_ITER = iter;
}

LogisticRegressionModel *logregress_init() {
    LogisticRegressionModel *model = malloc_with_check(sizeof(LogisticRegressionModel));
    model->intercept = 0.0;
    model->weights = NULL;
    return model;
}

void logregress_free(LogisticRegressionModel *model) {
    if (model == NULL) {
        return;
    }

    if (model->weights != NULL) {
        gsl_vector_free(model->weights);
    }
    free(model);
}

static double _sigmoid(double x) {
    double ev = 1 / (1 + exp(-x));
    if (ev < 0.00001) return 0.00001;
    if (ev > 0.99999) return 0.99999;
    return ev;
}

// TODO: something is wrong with the gradient descent
LogisticRegressionModel *logregress_fit(LogisticRegressionModel *model, Mat *X, Mat *Y) {
    if (X == NULL || Y == NULL) {
        fprintf(stderr, "logregress: X or Y is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (Y->cols != 1) {
        fprintf(stderr, "logregress: Y must be of the shape (r, 1) got (%ld, %ld)\n", Y->rows, Y->cols);
        exit(EXIT_FAILURE);
    }

    size_t n_cols = X->cols;
    size_t n_rows = X->rows;
    gsl_vector *weights = gsl_vector_calloc(n_cols);
    double intercept = 0.0;

    gsl_vector *curr_row = gsl_vector_alloc(n_cols);
    double alpha = 0.01;  // learning rate
    double pred, err;
    size_t i = -1;

    for (size_t j = 0; j < MAX_ITER; j++) {
        i = ((i + 1) % n_rows);
        gsl_matrix_get_row(curr_row, X->mat, i);
        gsl_blas_ddot(weights, curr_row, &pred);

        pred = _sigmoid(pred + intercept);
        err = gsl_matrix_get(Y->mat, i, 0) - pred;

        // update the intercept and the weights
        intercept = intercept - (alpha * err * pred * (1 - pred));  // * 1.0

        // weights
        double curr_w;
        for (size_t k = 0; k < n_cols; k++) {
            curr_w = gsl_vector_get(weights, k);
            curr_w = curr_w - (alpha * err * pred * (1 - pred) * gsl_matrix_get(X->mat, i, k));
            gsl_vector_set(weights, k, curr_w);
        }
    }
    gsl_vector_free(curr_row);
    model->weights = weights;
    model->intercept = intercept;
    return model;
}

double logregress_predict(LogisticRegressionModel *model, double *x, size_t len) {
    gsl_vector_view vv = gsl_vector_view_array(x, len);
    double dot;
    gsl_blas_ddot(model->weights, &vv.vector, &dot);
    return ((dot + model->intercept) > 0.5) ? 1 : 0;
}

Array *logregress_predict_many(LogisticRegressionModel *model, Mat *x) {
    size_t n_cols = x->cols;
    size_t n_rows = x->rows;
    Array *pred_array = arr_create(n_rows);
    gsl_vector *curr_row = gsl_vector_alloc(n_cols);

    for (size_t i = 0; i < n_rows; i++) {
        gsl_matrix_get_row(curr_row, x->mat, i);
        pred_array->arr[i] = logregress_predict(model, curr_row->data, n_cols);
    }

    gsl_vector_free(curr_row);
    return pred_array;
}
