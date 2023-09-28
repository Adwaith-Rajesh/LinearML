#include "ml/multiregress.h"

#include "ds/mat.h"
#include "utils/mem.h"

MLinearRegressionModel *mlinregress_init() {
    MLinearRegressionModel *new_model = malloc_with_check(sizeof(MLinearRegressionModel));
    new_model->coefs = NULL;
    new_model->intercept = 0.0f;
    // new_model->rvalue = 0.0f;
    return new_model;
}

void mlinregress_free(MLinearRegressionModel *model) {
    if (model == NULL) {
        return;
    }
    if (model->coefs != NULL) {
        mat_free(model->coefs);
    }
    free(model);
}

// refer: https://adwaith-rajesh.github.io/LinearML/ml/multiregress/#the-math
MLinearRegressionModel *mlinregress_fit(MLinearRegressionModel *model, Mat *x, Mat *y) {
    Mat *xt = mat_transpose(x);
    Mat *xt_x = mat_mul(xt, x);
    Mat *xt_x_i = mat_inverse(xt_x);
    Mat *xt_y = mat_mul(xt, y);
    Mat *betas = mat_mul(xt_x_i, xt_y);

    model->intercept = MAT_AT(betas, 0, 0);
    model->coefs = betas;

    mat_free(xt_y);
    mat_free(xt_x_i);
    mat_free(xt_x);
    mat_free(xt);

    return model;
}
