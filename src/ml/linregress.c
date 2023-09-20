#include <math.h>
#include <stdio.h>

#include "ml.h"
#include "stats.h"
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

LinearRegressionModel *linregress_fit(LinearRegressionModel *model, float *x, float *y, int len) {
    // find the value of slope and intercept

    float mean_x = stats_mean(x, len);
    float mean_y = stats_mean(y, len);
    float var_x = stats_var(x, len);
    float var_y = stats_var(y, len);
    float sd_x = sqrtf(var_x);  // std deviation
    float sd_y = sqrtf(var_y);
    float cov_xy = stats_covar(x, y, len);

    model->slope = cov_xy / var_x;
    model->intercept = mean_y - (model->slope * mean_x);
    model->rvalue = cov_xy / (sd_x * sd_y);
    return model;
}

float linregress_predict(LinearRegressionModel *model, float x) {
    if (model == NULL) {
        fprintf(stderr, "ml_predict_linregress_model: model values is NULL");
        return 0.0f;
    }
    return (model->slope * x) + model->intercept;
}

float linregress_score(LinearRegressionModel *model, float *x_test, float *y_test, int len) {
    float ssr = 0.0f;  // sum (predicted - target)^2  squared sum of residuals
    float sst = 0.0f;  // sum (target - target_mean)^2  squared sum of targets

    float y_mean = stats_mean(y_test, len);

    for (int i = 0; i < len; i++) {
        float pred_val = ml_predict_linregress_model(model, x_test[i]);
        ssr += (pred_val - y_test[i]) * (pred_val - y_test[i]);
        sst += (y_test[i] - y_mean) * (y_test[i] - y_mean);
    }
    return 1.0f - (ssr / sst);
}
