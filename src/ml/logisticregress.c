#include "ml/logisticregress.h"

#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_vector.h>
#include <math.h>

#include "ds/array.h"
#include "ds/mat.h"
#include "utils/mem.h"

#define RATE 0.1
size_t MAX_ITER = 100;

void logregress_set_max_iter(size_t iter) {
    MAX_ITER = iter;
}

LogisticRegressionModel *logregress_init() {
    LogisticRegressionModel *model = malloc_with_check(sizeof(LogisticRegressionModel));
    model->bias = 0.0;
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
    if (x >= 0) {
        return 1 / (1 + exp(-x));
    }
    return exp(x) / (1 + exp(x));
}

static double _loss(gsl_vector *y_pred, gsl_vector *y_true) {
    if (y_pred->size != y_true->size) {
        fprintf(stderr, "logregress::_loss[internal error] vector sizes for loss computation mismatch\n");
        exit(EXIT_FAILURE);
    }

    double sum = 0.0;
    for (size_t i = 0; i < y_pred->size; i++) {
        sum += (gsl_vector_get(y_true, i) * log(ls_vector_get(y_pred, i) + 1e-9) +
                (i - gsl_vector_get(y_true, i) * log(i - gsl_vector_get(y_pred, i) + 1e-9)));
    }

    return -(sum / y_pred->size);
}

static void _get_gradient(Mat *x, Mat *y_pred, Mat *y_true, double *grad_bias, gsl_vector *grad_weights) {
    if ((y_pred->rows != y_true->rows) || (y_pred->cols != 1 || y_true->cols != 1)) {
        fprintf(stderr, "logregress::_get_gradient[internal error] y_pred and y_true, shapes are different\n");
        exit(EXIT_FAILURE);
    }

    gsl_matrix *temp_mat = gsl_matrix_alloc(x->cols, y_pred->cols);  // used to store the multiplication result
    gsl_matrix *diff_mat = gsl_matrix_alloc(x->rows, 1);
    gsl_vector *temp_row = gsl_vector_alloc(temp_mat->size2);

    size_t y_n_rows = y_pred->rows;

    // grad_bias
    for (size_t i = 0; i < y_n_rows; i++) {
        gsl_matrix_set(diff_mat, i, 0, (mat_get(y_pred, i, 0) - mat_get(y_true, i, 0)));
    }
    *grad_bias = gsl_stats_mean(diff_mat->data, 1, diff_mat->size1 * diff_mat->size2);

    // grad weight
    gsl_blas_dgemm(CblasTrans, CblasNoTrans, 1.0, x->mat, diff_mat, 0.0, temp_mat);

    for (size_t i = 0; i < temp_mat->size1; i++) {
        gsl_matrix_get_row(temp_row, temp_mat, i);
        gsl_vector_set(grad_weights, i, gsl_stats_mean(temp_row->data, 1, temp_row->size));
    }

    gsl_matrix_free(temp_mat);
    gsl_matrix_free(diff_mat);
    gsl_vector_free(temp_row);
}

static void _update_parameters(gsl_vector *weights, double *bias, gsl_vector *error_w, double error_b) {
    *bias = *bias - RATE * error_b;
    for (size_t i = 0; i < weights->size; i++) {
        gsl_vector_set(weights, i, gsl_vector_get(weights, i) - RATE * gsl_vector_get(error_w, i));
    }
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

    // size_t n_cols = X->cols;
    // size_t n_rows = X->rows;
    // gsl_vector *weights = gsl_vector_calloc(n_cols);
    // double bias = 0.0;

    // gsl_vector *curr_row = gsl_vector_alloc(n_cols);
    // double alpha = 0.01;  // learning rate
    // double pred, err;
    // size_t i = -1;

    // for (size_t j = 0; j < MAX_ITER; j++) {
    //     i = ((i + 1) % n_rows);
    //     gsl_matrix_get_row(curr_row, X->mat, i);
    //     gsl_blas_ddot(weights, curr_row, &pred);

    //     pred = _sigmoid(pred + bias);
    //     err = gsl_matrix_get(Y->mat, i, 0) - pred;

    //     // update the bias and the weights
    //     bias = bias - (alpha * err * pred * (1 - pred));  // * 1.0

    //     // weights
    //     double curr_w;
    //     for (size_t k = 0; k < n_cols; k++) {
    //         curr_w = gsl_vector_get(weights, k);
    //         curr_w = curr_w - (alpha * err * pred * (1 - pred) * gsl_matrix_get(X->mat, i, k));
    //         gsl_vector_set(weights, k, curr_w);
    //     }
    // }
    // gsl_vector_free(curr_row);
    // model->weights = weights;
    // model->bias = bias;
    // return model;
}

double logregress_predict(LogisticRegressionModel *model, double *x, size_t len) {
    gsl_vector_view vv = gsl_vector_view_array(x, len);
    double dot;
    gsl_blas_ddot(model->weights, &vv.vector, &dot);
    return ((dot + model->bias) > 0.5) ? 1 : 0;
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
