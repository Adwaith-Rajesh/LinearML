#include <stdio.h>

#include "ml.h"
#include "stats.h"
#include "utils/mem.h"

LinearRegressionModel *ml_init_linregress_model() {
    LinearRegressionModel *new_model = malloc_with_check(sizeof(LinearRegressionModel));
    new_model->slope = 0.0f;
    new_model->intercept = 0.0f;
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

    model->slope = stats_covar(x, y, len) / stats_var(x, len);
    model->intercept = stats_mean(y, len) - (model->slope * stats_mean(x, len));
    return model;
}

float ml_predict_linregress_model(LinearRegressionModel *model, float x) {
    if (model == NULL) {
        fprintf(stderr, "ml_predict_linregress_model: model values is NULL");
        return 0.0f;
    }
    return (model->slope * x) + model->intercept;
}
