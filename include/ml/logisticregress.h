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

#ifndef ML_LOGISTICREGRESS_H
#define ML_LOGISTICREGRESS_H

#include <gsl/gsl_vector.h>
#include <stddef.h>

#include "ds/array.h"
#include "ds/mat.h"

typedef struct {
    double bias;
    double loss;
    gsl_vector *weights;
} LogisticRegressionModel;

/*
Set the maximum amount of iterations (default 100)
*/
void logregress_set_max_iter(size_t iter);

/*
Initialize the simple logistic regression model
*/
LogisticRegressionModel *logregress_init();

/*
Free the logistic regression model
*/
void logregress_free(LogisticRegressionModel *model);

/*
Fit the logistic regression model with the values
*/
LogisticRegressionModel *logregress_fit(LogisticRegressionModel *model, Mat *X, Mat *Y);

/*
Predict new values with the logistic regression model
*/
double logregress_predict(LogisticRegressionModel *model, double *x, size_t len);

/*
returns an Array of predictions for multiple x
*/
Array *logregress_predict_many(LogisticRegressionModel *model, Mat *x);

/*
Display the model details

fmt - the format string used to print the double values
*/
void logregress_print(LogisticRegressionModel *model);

#endif
