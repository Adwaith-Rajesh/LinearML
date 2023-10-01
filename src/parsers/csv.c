#include "parsers/csv.h"

#include <stdio.h>
#include <stdlib.h>

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

CSV *csv_parse(CSV *csv, const char *filename) {
    // the parsing is done using scansets

    const int MAX_SCANSET = 4096;
    const int MAX_ITEM_BUF = 128;

    char scanset[MAX_SCANSET];

    // a scanset that parses until the delimiter and also read the delimiter at the end
    snprintf(scanset, MAX_SCANSET, "%%[^%c\n]%%c", csv->delim);

    FILE *fp = fopen(filename, "r");

    char item[MAX_ITEM_BUF];
    char curr_delim;

    size_t r = 0;
    size_t c = 0;

    while (fscanf(fp, scanset, item, &curr_delim) != EOF) {
        mat_set(csv->values, r, c, strtod(item, NULL));
        c++;

        if (curr_delim == '\n') {
            r++;
            c = 0;
        }
    }

    fclose(fp);
    return csv;
}

Mat *csv_get_mat(CSV *csv, int *cols, size_t c_size) {
    Mat *new_mat = mat_create(csv->values->rows, c_size);

    size_t new_mat_col = 0;

    for (size_t c = 0; c < c_size; c++) {
        for (size_t r = 0; r < csv->values->rows; r++) {
            mat_set(new_mat, r, new_mat_col, mat_get(csv->values, r, cols[c]));
        }
        new_mat_col++;
    }

    return new_mat;
}
