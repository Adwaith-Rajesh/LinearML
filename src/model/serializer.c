#include "model/serializer.h"

#include <stdio.h>

#include "ds/mat.h"
#include "ml/linregress.h"
#include "ml/multiregress.h"

static void _serialize_size_t(size_t val, FILE *stream) {
    size_t temp = val;
    fwrite(&temp, sizeof(size_t), 1, stream);
}

static void _serialize_mat(Mat *mat, FILE *stream) {
    _serialize_size_t(mat->rows, stream);
    _serialize_size_t(mat->cols, stream);
    fwrite(mat->mat->data, sizeof(double), mat->rows * mat->cols, stream);
}

static void _serialize_double(double val, FILE *stream) {
    double temp = val;
    fwrite(&temp, sizeof(double), 1, stream);
}

static size_t _deserialize_size_t(FILE *stream) {
    size_t temp;
    fread(&temp, sizeof(size_t), 1, stream);
    return temp;
}

static Mat *_deserialize_mat(FILE *stream) {
    size_t rows = _deserialize_size_t(stream);
    size_t cols = _deserialize_size_t(stream);
    double values[rows * cols];

    fread(values, sizeof(double), rows * cols, stream);

    return mat_create_from_array(values, rows, cols);
}

static double _deserialize_double(FILE *stream) {
    double temp;
    fread(&temp, sizeof(double), 1, stream);
    return temp;
}

// ----------------------------------------

static void _serializer_linregress_model(LinearRegressionModel *model, const char *filepath) {
}
static void _serializer_mlinregress_model(MLinearRegressionModel *model, const char *filepath) {
    /*
    typedef struct {
        Mat *coefs;
        double intercept;
    } MLinearRegressionModel
    we can serializer the double value and the gsl_matrix within the coefs, along
    with it's rows and cols
     */

    FILE *fp = fopen(filepath, "wb");
    if (fp == NULL) {
        perror("model_serialize");
        exit(EXIT_FAILURE);
    }

    _serialize_double(model->intercept, fp);
    _serialize_mat(model->coefs, fp);

    fclose(fp);
}

static LinearRegressionModel *_deserialize_linregress_model(const char *filepath) {
}

static MLinearRegressionModel *_deserialize_mlinregress_model(MLinearRegressionModel *model, const char *filepath) {
    FILE *fp = fopen(filepath, "rb");
    if (fp == NULL) {
        perror("model_deserialize");
    }

    double intercept = _deserialize_double(fp);
    Mat *coefs = _deserialize_mat(fp);

    model->intercept = intercept;
    model->coefs = coefs;

    fclose(fp);
    return model;
}

void model_serialize(void *model, model_type type, const char *filepath) {
    if (type == LinearRegression) {
        _serializer_linregress_model(model, filepath);
    } else if (type == MLinearRegression) {
        _serializer_mlinregress_model(model, filepath);
    }
}

void model_deserialize(void *model, model_type type, const char *filepath) {
    switch (type) {
        case LinearRegression: {
        }
        case MLinearRegression:
            _deserialize_mlinregress_model(model, filepath);
    }
}
