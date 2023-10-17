#include "model/metrics.h"

#include <stdio.h>

#include "ds/array.h"
#include "ds/mat.h"

Mat *model_confusion_matrix(Array *y_true, Array *y_pred) {
    // TODO: generate confusion matrix for multi-class
    // classification

    if (y_true == NULL || y_pred == NULL) {
        fprintf(stderr, "model_confusion_matrix: y_true or y_pred is NULL\n");
        exit(EXIT_FAILURE);
    }

    if (y_true->size != y_pred->size) {
        fprintf(stderr, "model_confusion_matrix: y_true->size != y_pred->size\n");
        exit(EXIT_FAILURE);
    }

    /*
        [tp  fn]
        [fp, tn]
    */
    Mat *con_mat = mat_create_zeros(2, 2);

    for (size_t i = 0; i < y_true->size; i++) {
        if (y_pred->arr[i] == 1 && y_true->arr[i] == 1) {
            // true positive
            mat_set(con_mat, 0, 0, mat_get(con_mat, 0, 0) + 1);
        } else if (y_pred->arr[i] == 0 && y_true->arr[i] == 0) {
            // true negative
            mat_set(con_mat, 1, 1, mat_get(con_mat, 1, 1) + 1);
        } else if (y_pred->arr[i] == 1 && y_true->arr[i] == 0) {
            // false positive
            mat_set(con_mat, 1, 0, mat_get(con_mat, 1, 0) + 1);
        } else if (y_pred->arr[i] == 0 && y_true->arr[i] == 1) {
            // false negative
            mat_set(con_mat, 0, 1, mat_get(con_mat, 0, 1) + 1);
        }
    }

    return con_mat;
}
