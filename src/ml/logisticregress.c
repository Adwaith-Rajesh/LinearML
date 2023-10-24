#include "ml/logisticregress.h"

#include <gsl/gsl_blas.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_vector.h>
#include <math.h>

#include "ds/array.h"
#include "ds/mat.h"
#include "utils/mem.h"

#define RATE 0.01
size_t MAX_ITER = 100;

void logregress_set_max_iter(size_t iter) {
    MAX_ITER = iter;
}

LogisticRegressionModel *logregress_init() {
    LogisticRegressionModel *model = malloc_with_check(sizeof(LogisticRegressionModel));
    model->bias = 0.0;
    model->loss = 0.0;
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

static double _loss(Mat *y_pred, Mat *y_true) {
    if (y_pred->rows != y_true->rows) {
        fprintf(stderr, "logregress::_loss[internal error] vector sizes for loss computation mismatch\n");
        exit(EXIT_FAILURE);
    }

    double sum = 0.0;
    for (size_t i = 0; i < y_pred->rows; i++) {
        sum += (mat_get(y_true, i, 0) * log(mat_get(y_pred, i, 0) + 1e-9) +
                (1 - mat_get(y_true, i, 0) * log(1 - mat_get(y_pred, i, 0) + 1e-9)));
    }

    double loss = -(sum / y_pred->rows);
    return loss;
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

static void _do_logregress_fit(Mat *x, Mat *y, gsl_vector *m_weights, double *m_bias, double *m_loss) {
    size_t n_cols = x->cols;
    size_t n_rows = x->rows;

    double error_b;
    gsl_vector *dot_vec = gsl_vector_alloc(n_rows);
    gsl_vector *error_w = gsl_vector_alloc(n_cols);
    Mat *y_pred = mat_create(y->rows, y->cols);

    gsl_blas_dgemv(CblasNoTrans, 1.0, x->mat, m_weights, 0.0, dot_vec);
    gsl_vector_add_constant(dot_vec, *m_bias);

    // predictions
    for (size_t v = 0; v < n_rows; v++) {
        double sig = _sigmoid(gsl_vector_get(dot_vec, v));
        // printf("sig: %lf\n", sig);
        mat_set(y_pred, v, 0, sig);
    }

    *m_loss = _loss(y_pred, y);
    _get_gradient(x, y_pred, y, &error_b, error_w);
    _update_parameters(m_weights, m_bias, error_w, error_b);

    gsl_vector_free(dot_vec);
    gsl_vector_free(error_w);
    mat_free(y_pred);
}

LogisticRegressionModel *logregress_fit(LogisticRegressionModel *model, Mat *X, Mat *Y) {
    if (X == NULL || Y == NULL) {
        fprintf(stderr, "logregress: X or Y is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (Y->cols != 1) {
        fprintf(stderr, "logregress: Y must be of the shape (r, 1) got (%ld, %ld)\n", Y->rows, Y->cols);
        exit(EXIT_FAILURE);
    }

    gsl_vector *weights = gsl_vector_calloc(X->cols);
    double bias = 0.0;
    double loss = 0.0;

    for (size_t e = 0; e < MAX_ITER; e++) {
        _do_logregress_fit(X, Y, weights, &bias, &loss);
    }
    model->weights = weights;
    model->bias = bias;
    model->loss = loss;
    return model;
}

double logregress_predict(LogisticRegressionModel *model, double *x, size_t len) {
    gsl_vector_view vv = gsl_vector_view_array(x, len);
    double dot;
    gsl_blas_ddot(model->weights, &vv.vector, &dot);
    return (_sigmoid(dot + model->bias) > 0.5) ? 1 : 0;
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

void logregress_print(LogisticRegressionModel *model) {
    printf("LogisticRegressionModel(bias: %.7lf, loss: %.7lf, weights: %p)\n", model->bias, model->loss, model->weights);
    printf("weights: \n");
    gsl_vector_fprintf(stdout, model->weights, "%.7lf");
}
