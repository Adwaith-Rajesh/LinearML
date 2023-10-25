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

#ifndef ML_LINREGRESS_H
#define ML_LINREGRESS_H

#include <stddef.h>

#include "ds/mat.h"

typedef struct {
    // y = ax + b
    double slope;
    double intercept;
    double rvalue;  // corelation value
} LinearRegressionModel;

/*
Initialize the simple linear regression model
*/
LinearRegressionModel *linregress_init();

/*
Free the linear regression model
*/
void linregress_free(LinearRegressionModel *model);

/*
Fit the linear regression model with the values
*/
LinearRegressionModel *linregress_fit(LinearRegressionModel *model, double *x, double *y, size_t len);

/*
Predict new values with the linear regression model
*/
double linregress_predict(LinearRegressionModel *model, double x);

/*
Score/test the linear regression model based on known x and y values
*/
double linregress_score(LinearRegressionModel *model, double *x_test, double *y_test, size_t len);

/*
Display the model details

fmt - the format string used to print the double values
*/
void linregress_print(LinearRegressionModel *model);

LinearRegressionModel *linregress_fit_mat(LinearRegressionModel *model, Mat *X, Mat *Y);

double linregress_score_mat(LinearRegressionModel *model, Mat *x_test, Mat *y_test);

#endif
