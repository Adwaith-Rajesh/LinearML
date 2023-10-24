#include "model/metrics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ds/array.h"
#include "ds/mat.h"
#include "utils/mem.h"

#define _INT(x) (*(int *)((x)))

int _compare_val(const void *val1, const void *val2) {
    if (_INT(val1) == _INT(val2)) return 0;
    if (_INT(val1) < _INT(val2)) return -1;
    if (_INT(val1) > _INT(val2)) return 1;
    return 0;
}

int _in_array(int *arr, int val, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (arr[i] == val) return 1;
    }
    return 0;
}

int *_combine_classes(int *pred_classes, int *true_classes, size_t pred_curr, size_t *true_curr) {
    // if by any change the predicted classes are not the test set.
    // we randomly picked so nicely that we missed a class in the test set.
    for (size_t i = 0; i < pred_curr; i++) {
        if (!_in_array(true_classes, pred_classes[i], *true_curr)) {
            true_classes[*true_curr] = pred_classes[i];
            (*true_curr)++;
        }
    }
    return true_classes;
}

int *_get_unique_sort_int_conv(double *arr, size_t size, size_t *sorted_size) {
    int *c_arr = malloc_with_check(sizeof(int) * size);
    // memcpy(c_arr, arr, sizeof(double) * size);

    // since we need to convert types, we will do it manually
    for (size_t i = 0; i < size; i++) {
        c_arr[i] = (int)arr[i];
    }

    qsort(c_arr, size, sizeof(int), _compare_val);

    size_t curr_idx = 1;
    int curr_val = c_arr[0];

    for (size_t i = 1; i < size; i++) {
        if (c_arr[i] == curr_val) continue;
        curr_val = c_arr[i];
        c_arr[curr_idx++] = c_arr[i];
    }
    *sorted_size = curr_idx;
    return c_arr;
}

size_t _get_idx_of_class(int *classes, int class, size_t size) {
    // the class that we are looking for always exists in the array (kind of) :-)
    for (size_t i = 0; i < size; i++) {
        if (classes[i] == class) return i;
    }
    return 0;
}

/* ============= The metrics functions ============= */

Mat *model_confusion_matrix(Array *y_true, Array *y_pred) {
    if (y_true == NULL || y_pred == NULL) {
        fprintf(stderr, "model_confusion_matrix: y_true or y_pred is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (y_true->size != y_pred->size) {
        fprintf(stderr, "model_confusion_matrix: y_true->size != y_pred->size\n");
        exit(EXIT_FAILURE);
    }

    size_t ut_size;
    size_t up_size;
    int *u_t = _get_unique_sort_int_conv(y_true->arr, y_true->size, &ut_size);
    int *u_p = _get_unique_sort_int_conv(y_pred->arr, y_pred->size, &up_size);

    u_t = _combine_classes(u_p, u_t, up_size, &ut_size);

    /*
        Classes      Predicted

                       0 1 2 3 ...
                    0
        Original    1
                    2
                    3
                    .
                    .
    */
    Mat *con_mat = mat_create_zeros(ut_size, ut_size);

    for (size_t i = 0; i < y_true->size; i++) {
        size_t t_idx = _get_idx_of_class(u_t, (int)(y_true->arr[i]), ut_size);
        size_t p_idx = _get_idx_of_class(u_t, (int)(y_pred->arr[i]), ut_size);
        mat_set(con_mat, t_idx, p_idx, mat_get(con_mat, t_idx, p_idx) + 1);
    }
    free(u_t);
    free(u_p);
    return con_mat;
}
