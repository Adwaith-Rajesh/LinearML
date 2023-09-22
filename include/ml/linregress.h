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

#ifndef ML_H
#define ML_H

typedef struct {
    // y = ax + b
    float slope;
    float intercept;
    float rvalue;  // corelation value
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
LinearRegressionModel *linregress_fit(LinearRegressionModel *model, float *x, float *y, int len);

/*
Predict new values with the linear regression model
*/
float linregress_predict(LinearRegressionModel *model, float x);

/*
Score/test the linear regression model based on known x and y values
*/
float linregress_score(LinearRegressionModel *model, float *x_test, float *y_test, int len);

#endif