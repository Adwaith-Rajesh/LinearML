#include "ml/multiregress.h"

#include <stdio.h>

#include "ds/array.h"
#include "ds/mat.h"
#include "utils/mem.h"

Mat *_prepare_mat_for_fit(Mat *mat) {
    // add new col of 1's to the provided mat

    Mat *new_mat = mat_create(mat->rows, mat->cols + 1);

    for (size_t r = 0; r < new_mat->rows; r++) {
        for (size_t c = 0; c < new_mat->cols; c++) {
            if (c == 0) {
                mat_set(new_mat, r, c, 1);
            } else {
                mat_set(new_mat, r, c, mat_get(mat, r, c - 1));
            }
        }
    }
    return new_mat;
}

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
    Mat *new_x = _prepare_mat_for_fit(x);

    Mat *xt = mat_transpose(new_x);
    Mat *xt_x = mat_mul(xt, new_x);

    Mat *xt_x_i = mat_invert_svd(xt_x);
    Mat *xt_y = mat_mul(xt, y);
    Mat *betas = mat_mul(xt_x_i, xt_y);

    model->intercept = mat_get(betas, 0, 0);

    double *new_betas_array = malloc_with_check(sizeof(double) * betas->rows - 1);
    for (size_t i = 0; i < betas->rows - 1; i++) new_betas_array[i] = mat_get(betas, i + 1, 0);
    Mat *new_betas_mat = mat_create_from_array(new_betas_array, betas->rows - 1, betas->cols);

    model->coefs = new_betas_mat;

    mat_free(betas);
    mat_free(xt_y);
    mat_free(xt_x_i);
    mat_free(xt_x);
    mat_free(xt);
    mat_free(new_x);

    return model;
}

double mlinregress_predict(MLinearRegressionModel *model, double *x_vals, size_t len) {
    if (len != model->coefs->rows) {
        fprintf(stderr, "Model is trained on %ld params, x_vals has %ld\n",
                model->coefs->rows, len);
        return 0.0f;
    }

    // the first value in the model->coefs matrix is the intercept
    // the rest are coefficients

    double pred_val = model->intercept;
    for (size_t i = 0; i < len; i++) {
        pred_val += (x_vals[i] * mat_get(model->coefs, i, 0));
    }
    return pred_val;
}

void mlinregress_print(MLinearRegressionModel *model) {
    printf("MLinearRegressionModel(intercept: %lf, coefs: %p)\n", model->intercept, model->coefs);
    printf("coefs\n");
    mat_printp(model->coefs, 7);
}
