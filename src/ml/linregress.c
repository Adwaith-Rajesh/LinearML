#include "ml/linregress.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "ds/mat.h"
#include "stats/stats.h"
#include "utils/mem.h"

LinearRegressionModel *linregress_init() {
    LinearRegressionModel *new_model = malloc_with_check(sizeof(LinearRegressionModel));
    new_model->slope = 0.0f;
    new_model->intercept = 0.0f;
    new_model->rvalue = 0.0f;
    return new_model;
}

void linregress_free(LinearRegressionModel *model) {
    if (model == NULL) {
        return;
    }
    free(model);
}

LinearRegressionModel *linregress_fit(LinearRegressionModel *model, double *x, double *y, size_t len) {
    // find the value of slope and intercept

    double mean_x = stats_mean(x, len);
    double mean_y = stats_mean(y, len);
    double var_x = stats_var(x, len);
    double var_y = stats_var(y, len);
    double sd_x = sqrtf(var_x);  // std deviation
    double sd_y = sqrtf(var_y);
    double cov_xy = stats_covar(x, y, len);

    model->slope = cov_xy / var_x;
    model->intercept = mean_y - (model->slope * mean_x);
    model->rvalue = cov_xy / (sd_x * sd_y);
    return model;
}

double linregress_predict(LinearRegressionModel *model, double x) {
    if (model == NULL) {
        fprintf(stderr, "ml_predict_linregress_model: model values is NULL");
        return 0.0f;
    }
    return (model->slope * x) + model->intercept;
}

double linregress_score(LinearRegressionModel *model, double *x_test, double *y_test, size_t len) {
    double ssr = 0.0f;  // sum (predicted - target)^2  squared sum of residuals
    double sst = 0.0f;  // sum (target - target_mean)^2  squared sum of targets

    double y_mean = stats_mean(y_test, len);

    for (size_t i = 0; i < len; i++) {
        double pred_val = linregress_predict(model, x_test[i]);
        ssr += (pred_val - y_test[i]) * (pred_val - y_test[i]);
        sst += (y_test[i] - y_mean) * (y_test[i] - y_mean);
    }
    return 1.0f - (ssr / sst);
}

LinearRegressionModel *linregress_fit_mat(LinearRegressionModel *model, Mat *X, Mat *Y) {
    if (X->cols > 1 || Y->cols > 1) {
        fprintf(stderr, "linregress_fit_mat: expected shape mat (n, 1)  got X: (%ld, %ld) Y: {%ld, %ld}",
                X->rows, X->cols, Y->rows, Y->cols);
        exit(EXIT_FAILURE);
    }

    return linregress_fit(model, X->mat->data, Y->mat->data, X->rows);
}

double linregress_score_mat(LinearRegressionModel *model, Mat *x_test, Mat *y_test) {
    if (x_test->cols > 1 || y_test->cols > 1) {
        fprintf(stderr, "linregress_fit_mat: expected shape mat (n, 1)  got X: (%ld, %ld) Y: {%ld, %ld}",
                x_test->rows, x_test->cols, y_test->rows, y_test->cols);
        exit(EXIT_FAILURE);
    }

    return linregress_score(model, x_test->mat->data, y_test->mat->data, x_test->rows);
}

void linregress_print(LinearRegressionModel *model) {
    printf("LinearRegressionModel(slope: %.7lf, intercept: %.7lf, rvalue: %.7lf)\n", model->slope, model->intercept, model->rvalue);
}
