#include <math.h>
#include <stdio.h>

#include "ml.h"
#include "stats.h"
#include "utils/mem.h"

LinearRegressionModel *ml_init_linregress_model() {
    LinearRegressionModel *new_model = malloc_with_check(sizeof(LinearRegressionModel));
    new_model->slope = 0.0f;
    new_model->intercept = 0.0f;
    new_model->rvalue = 0.0f;
    return new_model;
}

void ml_free_linregress_model(LinearRegressionModel *model) {
    if (model == NULL) {
        return;
    }
    free(model);
}

LinearRegressionModel *ml_fit_linregress_model(LinearRegressionModel *model, float *x, float *y, int len) {
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

float ml_predict_linregress_model(LinearRegressionModel *model, float x) {
    if (model == NULL) {
        fprintf(stderr, "ml_predict_linregress_model: model values is NULL");
        return 0.0f;
    }
    return (model->slope * x) + model->intercept;
}

float ml_score_linregress_model(LinearRegressionModel *model, float *x_test, float *y_test) {
}
