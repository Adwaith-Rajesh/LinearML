#include "parsers/csv.h"

#include "ds/mat.h"
#include "utils/mem.h"

CSV *csv_init(size_t rows, size_t cols, char delim) {
    CSV *new_csv = malloc_with_check(sizeof(CSV));
    new_csv->rows = rows;
    new_csv->cols = cols;

    new_csv->values = mat_create(rows, cols);
    new_csv->delim = delim;
    return new_csv;
}

void csv_free(CSV *csv) {
    if (csv == NULL) {
        return;
    }

    if (csv->values != NULL) {
        mat_free(csv->values);
    }

    free(csv);
}

void csv_print(CSV *csv) {
    if (csv == NULL) {
        return;
    }

    mat_print(csv->values);
}
