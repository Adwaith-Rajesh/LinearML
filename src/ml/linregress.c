#include "ml/linregress.h"

#include <math.h>
#include <stddef.h>
#include <stdio.h>

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
