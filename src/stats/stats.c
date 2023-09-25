#include "stats.h"

#include <float.h>
#include <stddef.h>
#include <stdlib.h>

float stats_mean(float *arr, size_t len) {
    if (arr == NULL) return 0.0f;

    float sum = 0.0f;
    for (size_t i = 0; i < len; i++) {
        sum += arr[i];
    }
    return (float)(sum / (float)len);
}

float stats_var(float *arr, size_t len) {
    if (arr == NULL) return 0.0f;

    float arr_mean = stats_mean(arr, len);

    float sum = 0.0f;
    float res;
    for (size_t i = 0; i < len; i++) {
        res = (arr[i] - arr_mean);
        sum += (float)(res * res);
    }
    return (float)(sum / (float)(len - 1));
}

float stats_covar(float *arr1, float *arr2, size_t len) {
    if (arr1 == NULL || arr2 == NULL) return 0.0f;

    float arr1_mean = stats_mean(arr1, len);
    float arr2_mean = stats_mean(arr2, len);

    float sum = 0.0f;
    for (size_t i = 0; i < len; i++) {
        sum += ((arr1[i] - arr1_mean) * (arr2[i] - arr2_mean));
    }
    return (float)(sum / (float)(len - 1));
}

float stats_max(float *arr, size_t len) {
    float max_val = FLT_MIN;

    for (size_t i = 0; i < len; i++) {
        max_val = (arr[i] > max_val) ? arr[i] : max_val;
    }

    return max_val;
}

float stats_min(float *arr, size_t len) {
    float min_val = FLT_MAX;

    for (size_t i = 0; i < len; i++) {
        min_val = (arr[i] < min_val) ? arr[i] : min_val;
    }

    return min_val;
}
