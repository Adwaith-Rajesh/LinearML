#include "stats.h"

#include <stdlib.h>

float stats_mean(float *arr, int len) {
    if (arr == NULL) return 0.0f;

    float sum = 0.0f;
    for (int i = 0; i < len; i++) {
        sum += arr[i];
    }
    return (float)(sum / (float)len);
}

float stats_var(float *arr, int len) {
    if (arr == NULL) return 0.0f;

    float arr_mean = stats_mean(arr, len);

    float sum = 0.0f;
    float res;
    for (int i = 0; i < len; i++) {
        res = (arr[i] - arr_mean);
        sum += (float)(res * res);
    }
    return (float)(sum / (float)(len - 1));
}

float stats_covar(float *arr1, float *arr2, int len) {
    if (arr1 == NULL || arr2 == NULL) return 0.0f;

    float arr1_mean = stats_mean(arr1, len);
    float arr2_mean = stats_mean(arr2, len);

    float sum = 0.0f;
    for (int i = 0; i < len; i++) {
        sum += ((arr1[i] - arr1_mean) * (arr2[i] - arr2_mean));
    }
    return (float)(sum / (float)(len - 1));
}
