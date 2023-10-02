#include "stats/stats.h"

#include <float.h>
#include <gsl/gsl_statistics.h>
#include <stddef.h>
#include <stdlib.h>

double stats_mean(double *arr, size_t len) {
    return gsl_stats_mean(arr, 1, len);
}

double stats_var(double *arr, size_t len) {
    return gsl_stats_variance(arr, 1, len);
}

double stats_covar(double *arr1, double *arr2, size_t len) {
    return gsl_stats_covariance(arr1, 1, arr2, 1, len);
}

double stats_max(double *arr, size_t len) {
    return gsl_stats_max(arr, 1, len);
}

double stats_min(double *arr, size_t len) {
    return gsl_stats_min(arr, 1, len);
}
