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

#ifndef ML_H
#define ML_H

#include <gsl/gsl_vector.h>
#include <stddef.h>

#include "ds/mat.h"

typedef struct {
    double intercept;
    gsl_vector *weights;
} LogisticRegressionModel;

/*
Set the maximum amount of iterations (default 100)
*/
void logregress_set_max_iter(size_t iter);
/*
Initialize the simple linear regression model
*/
LogisticRegressionModel *logregress_init();

/*
Free the linear regression model
*/
void logregress_free(LogisticRegressionModel *model);

/*
Fit the linear regression model with the values
*/
LogisticRegressionModel *logregress_fit(LogisticRegressionModel *model, Mat *X, Mat *Y);

/*
Predict new values with the linear regression model
*/
int logregress_predict(LogisticRegressionModel *model, double *x, size_t len);

/*
Score/test the linear regression model based on known x and y values
*/
double logregress_score(LogisticRegressionModel *model, Mat *x_test, Mat *y_test);

#endif
