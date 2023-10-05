#include "model/serializer.h"

#include <gsl/gsl_matrix.h>
#include <stdio.h>

static void _serialize_size_t(size_t val, FILE *stream) {
}

static void _serialize_gsl_matrix(gsl_matrix *mat, size_t size, FILE *stream) {
}

static void _serialize_double(double val, FILE *stream) {
}
