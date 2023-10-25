/*
LinearML - A Linear Algebra and Machine Learning "Library" in C
Copyright (c) 2023 Adwaith Rajesh <adwaithrajesh3180[at]gmail[dot]com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef PREPROCESSING_SCALERS_H
#define PREPROCESSING_SCALERS_H

#include <stddef.h>

#include "ds/mat.h"

struct _SSData {
    double mean;
    double std;
};

typedef struct {
    int with_mean;
    int with_std;
    size_t _n_cols;
    struct _SSData *col_vals;  // mean, std for each cols
} StandardScaler;

/*
initialize the standard scaler with parameters
*/
StandardScaler *standard_scaler_initp(int with_mean, int with_std);

/*
Initialize the standard scalers with default parameters
*/
StandardScaler *standard_scaler_init() {
    return standard_scaler_initp(1, 1);
}

/*
Fit the Scaler with the data
*/
StandardScaler *standard_scaler_fit(StandardScaler *scaler, Mat *data);

/*
Transform the dataset,returns the transformed data
*/
Mat *standard_scaler_transform(StandardScaler *scaler, Mat *data);

/*
Free the Standard Scaler
*/
void standard_scaler_free(StandardScaler *scaler);

#endif
