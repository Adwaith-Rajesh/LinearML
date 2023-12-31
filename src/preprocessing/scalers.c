#include "preprocessing/scalers.h"

#include <gsl/gsl_matrix.h>
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_vector.h>
#include <math.h>

#include "ds/mat.h"
#include "utils/mem.h"

StandardScaler *standard_scaler_initp(int with_mean, int with_std) {
    StandardScaler *new_scaler = malloc_with_check(sizeof(StandardScaler));
    new_scaler->with_mean = (with_mean >= 1) ? 1 : 0;
    new_scaler->with_std = (with_std >= 1) ? 1 : 0;
    new_scaler->_n_cols = 0;
    new_scaler->col_vals = NULL;
    return new_scaler;
}

static double _get_population_mean(double *arr, size_t size) {
    double sum = 0.0;
    for (size_t i = 0; i < size; i++) {
        sum += arr[i];
    }
    return (sum / size);
}

StandardScaler *standard_scaler_fit(StandardScaler *scaler, Mat *data) {
    scaler->_n_cols = data->cols;
    scaler->col_vals = malloc_with_check(sizeof(struct _SSData) * data->cols);

    gsl_vector *curr_col = gsl_vector_alloc(data->rows);
    for (size_t i = 0; i < data->cols; i++) {
        gsl_matrix_get_col(curr_col, data->mat, i);
        double mean = _get_population_mean(curr_col->data, curr_col->size);

        if (scaler->with_mean == 0) {
            scaler->col_vals[i].mean = 0;
        } else {
            scaler->col_vals[i].mean = mean;
        }

        if (scaler->with_std == 0) {
            scaler->col_vals[i].std = 1;
        } else {
            scaler->col_vals[i].std = gsl_stats_sd_with_fixed_mean(curr_col->data, 1, curr_col->size, mean);
            printf("std: %lf\n", scaler->col_vals[i].std);
        }
    }
    gsl_vector_free(curr_col);
    return scaler;
}

static inline double _do_z_norm(double x, double mean, double std) {
    return (x - mean) / std;
}

Mat *standard_scaler_transform(StandardScaler *scaler, Mat *data) {
    if (data->cols != scaler->_n_cols) {
        fprintf(stderr, "data col size does not match with scalers col size\n");
        exit(EXIT_FAILURE);
    }

    for (size_t c = 0; c < data->cols; c++) {
        double mean = scaler->col_vals[c].mean;
        double std = scaler->col_vals[c].std;

        for (size_t r = 0; r < data->rows; r++) {
            mat_set(data, r, c, _do_z_norm(mat_get(data, r, c), mean, std));
        }
    }
    return data;
}

void standard_scaler_free(StandardScaler *scaler) {
    if (scaler == NULL) return;
    if (scaler->col_vals != NULL) {
        free(scaler->col_vals);
    }
    free(scaler);
}

// ------------------------------------------------------------------------------
// min-max scaler

MinMaxScaler *minmax_scaler_initp(double new_min, double new_max) {
    MinMaxScaler *new_scaler = malloc_with_check(sizeof(MinMaxScaler));
    new_scaler->new_min = new_min;
    new_scaler->new_max = new_max;
    new_scaler->col_vals = 0;
    new_scaler->col_vals = NULL;
    return new_scaler;
}

MinMaxScaler *minmax_scaler_fit(MinMaxScaler *scaler, Mat *data) {
    scaler->_n_cols = data->cols;
    scaler->col_vals = malloc_with_check(sizeof(struct _MMData) * data->cols);

    gsl_vector *curr_col = gsl_vector_alloc(data->rows);

    for (size_t i = 0; i < data->cols; i++) {
        gsl_matrix_get_col(curr_col, data->mat, i);
        scaler->col_vals[i].col_max = gsl_vector_max(curr_col);
        scaler->col_vals[i].col_min = gsl_vector_min(curr_col);
    }

    gsl_vector_free(curr_col);
    return scaler;
}

static double _scale_x_minmax(double x, double col_min, double col_max, double new_min, double new_max) {
    double x_std = (x - col_min) / (col_max - col_min);
    return x_std * (new_max - new_min) + new_min;
}

Mat *minmax_scaler_transform(MinMaxScaler *scaler, Mat *data) {
    if (data->cols != scaler->_n_cols) {
        fprintf(stderr, "data col size does not match with scalers col size\n");
        exit(EXIT_FAILURE);
    }

    double new_min = scaler->new_min;
    double new_max = scaler->new_max;

    for (size_t c = 0; c < data->cols; c++) {
        double col_min = scaler->col_vals[c].col_min;
        double col_max = scaler->col_vals[c].col_max;

        for (size_t r = 0; r < data->rows; r++) {
            mat_set(data, r, c, _scale_x_minmax(mat_get(data, r, c), col_min, col_max, new_min, new_max));
        }
    }
    return data;
}

void minmax_scaler_free(MinMaxScaler *scaler) {
    if (scaler == NULL) return;
    if (scaler->col_vals != NULL) {
        free(scaler->col_vals);
    }
    free(scaler);
}
