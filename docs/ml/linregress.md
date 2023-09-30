# Linear Regression

## The math

Well, what is Linear Regression or Simple Linear Regression?

Acco.To Wiki

> "linear regression is a linear approach for modelling the relationship between a scalar response and one or more explanatory variables (also known as dependent and independent variables)"

or in other words use one variable to predict the value of another.

Now, how do you do that?

A simple linear regression model defines the relationship between two variables $x$ and $y$
using a line defined by an equation in the following form:

$$
y = \alpha + \beta x
$$

In order to determine the optimal estimates of $\alpha$ and $\beta$, an estimation method known
as [_Ordinary Least Squares_](https://en.wikipedia.org/wiki/Ordinary_least_squares#Simple_linear_regression_model) is used.

Now after a lot of derivation and other math stuff, which I won't go over here, we will end up
with two nice formulas for finding $\alpha$ and $\beta$

$$
\beta = { Cov(x, y) \over Var(x)}
$$

$$
\alpha = \overline{y} - \beta \overline{x}
$$

Where

$$
Cov(x, y) = {1 \over n - 1} \sum_{i=1}^{n} (x_i - \overline{x}) \ (y_i - \overline{y})
$$

$$
Var(x) = {1 \over n - 1} \sum_{i=1}^{n} (x_i - \overline{x})^2
$$

- $x_i$ , the value of x.
- $y_i$ , the values of y.
- $n$ is the number of samples.
- $\overline x$, $\overline y$ are the mean of $x$ and $y$.

## The Code

This is a really stupid example.. but it shows it's working.

```c
#include <stdio.h>

#include "ds/array.h"
#include "ml/linregress.h"

int main(void) {
    float x_vals[] = {1, 2, 3, 4, 5};
    float y_vals[] = {2, 4, 6, 8, 10};

    LinearRegressionModel *model = linregress_init();
    linregress_fit(model, x_vals, y_vals, 5);

    printf("Slope: %f\n", model->slope);
    printf("Intercept: %f\n", model->intercept);
    printf("R value: %f\n", model->rvalue);

    printf("prediction (20): %f\n", linregress_predict(model, 20));

    linregress_free(model);

    return 0;
}
```

Run the code, instructions [here](https://adwaith-rajesh.github.io/LinearML/#testing-the-install)

```console
Slope: 2.000000
Intercept: 0.000000
R value: 1.000000
prediction (20): 40.000000
```

## List of functions

```c

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
LinearRegressionModel *linregress_fit(LinearRegressionModel *model, float *x, float *y, size_t len);

/*
Predict new values with the linear regression model
*/
float linregress_predict(LinearRegressionModel *model, float x);

/*
Score/test the linear regression model based on known x and y values
*/
float linregress_score(LinearRegressionModel *model, float *x_test, float *y_test, size_t len);

// Mat version of all the funcs
#ifdef INCLUDE_LINREGRESS_MAT_FUNC

#define linregress_fit_mat(model, mat) linregress_fit(model, &mat->elems[0], &mat->elems[mat->rows], mat->rows)

#define linregress_score_mat(model, mat) linregress_score(model, &mat->elems[0], &mat->elems[mat->rows], mat->rows)

#endif

// Array version of all the functions
#ifdef INCLUDE_LINREGRESS_ARR_FUNC

#include "ds/array.h"

#define linregress_fit_arr(model, x_arr, y_arr) linregress_fit(model, (x_arr)->arr, (y_arr)->arr, (x_arr)->size);

#define linregress_score_arr(model, x_arr, y_arr) linregress_score(model, (x_arr)->arr, (y_arr)->arr, (x_arr)->size);

Array *linregress_predict_arr(LinearRegressionModel *model, Array *x_vals) {
    Array *pred_arr = arr_create(x_vals->size);

    for (size_t i = 0; i < x_vals->size; i++) {
        ARR_AT(pred_arr, i) = linregress_predict(model, ARR_AT(x_vals, i));
    }

    return pred_arr;
}

#endif
```

If you have any issues, queries feel free to contact me through the socials given below
