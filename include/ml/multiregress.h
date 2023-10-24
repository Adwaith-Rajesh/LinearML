/*
LinearML - A Linear Algebra and Machine Learning "Library" in C
Copyright (c) 2023 Adwaith Rajesh <adwaithrajesh3180[at]gmail[dot]com>

LICENSE: MIT

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ML_MULTI_REGRESS_H
#define ML_MULTI_REGRESS_H

#include "ds/array.h"
#include "ds/mat.h"

// refer: https://adwaith-rajesh.github.io/LinearML/ml/multiregress/

typedef struct {
    Mat *coefs;  // the coefficients
    double intercept;
    // float rvalue;  // corelation value
} MLinearRegressionModel;

/*
Initialize the multiple linear regression model
*/
MLinearRegressionModel *mlinregress_init();

/*
Free the Multiple linear regression model
*/
void mlinregress_free(MLinearRegressionModel *model);

/*
Fit the multiple linear regression model with the values
*/
MLinearRegressionModel *mlinregress_fit(MLinearRegressionModel *model, Mat *x, Mat *y);

/*
Predict new values with the multiple regression model
*/
double mlinregress_predict(MLinearRegressionModel *model, double *x_vals, size_t len);

/*
Display the model details

fmt - the format string used to print the double values
*/
void mlinregress_print(MLinearRegressionModel *model);

#endif
