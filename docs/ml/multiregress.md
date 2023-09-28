# Multiple Linear Regression

## The Math

Definition can be found [here](https://en.wikipedia.org/wiki/Linear_regression#Simple_and_multiple_linear_regression).

In simple terms MLR can described as

"The case of one explanatory variable is called simple linear regression; for more than one, the process is called multiple linear regression."

The formula / model for MLR is

$$
y = \beta_0 + \beta_1x_1 + \dots + \beta_nx_n + \epsilon
$$

- $y$, is the predicted values
- $\beta_0$, is the y-intercept
- $\beta_1x_1$, is the first regression coefficient ($\beta_1$) of the first independent variable ($X_1$)
- $\dots$, do the same for all independent variables.
- $\beta_nx_n$, is the regression coefficient of the last independent variable
- $\epsilon$, is the model error.

The same formula in Matrix form can be represented as

$$
Y = \beta X + \epsilon
$$

$$
\begin{bmatrix}
y_1 \\
y_2 \\
\vdots \\
y_N
\end{bmatrix}
=
\begin{bmatrix}
x_{11} & x_{12} & \cdots & x_{1k} \\
x_{21} & x_{22} & \cdots & x_{2k} \\
\vdots & \ddots & \ddots & \vdots \\
x_{N1} & x_{N2} & \cdots & x_{Nk} \\
\end{bmatrix}
*
\begin{bmatrix}
\beta_0 \\
\beta_1 \\
\vdots \\
\beta_k
\end{bmatrix}
+
\begin{bmatrix}
\epsilon_1 \\
\epsilon_2 \\
\vdots \\
\epsilon_N \\
\end{bmatrix}
$$

Our goal is to find $\beta$ (coefficients / parameters) and to minimize $\epsilon^2$.
The methods used to do so is called the [Least Squared Method](https://en.wikipedia.org/wiki/Least_squares).

Now, the least squared estimator for the given model is

$$
\beta = {(X^TX)}^{-1}(X^TY)
$$

The proof for this derivation can be found [here](https://www.youtube.com/watch?v=fBaXhzlSO18).

## The Code

Here is an example of training the Multiple Linear Regression Model with an example data.

Data

$$
\begin{array}{|c|c|c|}
\hline
    \text{${x_1}$} & \text{${x_2}$} & \text{${y}$} \\
\hline
    1 & 1 & 3.25 \\
\hline
    1 & 2 & 6.5 \\
\hline
    2 & 2 & 3.5 \\
\hline
    0 & 1 & 5.0 \\
\hline
\end{array}
$$

When fitting the `MLinearRegressionModel` using the function `mlinregress_fit`, the $X$ matrix must be

$$
X =
\begin{bmatrix}
1 & 1 \\
1 & 2 \\
2 & 2 \\
0 & 1 \\
\end{bmatrix}
$$

The $1^{st}$ column are the values of $x_1$ and $2^{nd}$ columns are the values of $x_2$.

The $Y$ matrix will look like the following

$$
Y =
\begin{bmatrix}
3.25 \\
6.5 \\
3.5 \\
5.0 \\
\end{bmatrix}
$$

In code

```c
#include <stdio.h>

#include "ds/array.h"
#include "ml/multiregress.h"

int main(void) {
    float x_vals[] = {
        1, 1,
        1, 2,
        2, 2,
        0, 1};

    float y_vals[] = {
        3.25,
        6.5,
        3.5,
        5.0};

    Mat *x_mat = mat_create_from_array(x_vals, 4, 2);
    Mat *y_mat = mat_create_from_array(y_vals, 4, 1);

    MLinearRegressionModel *model = mlinregress_init();
    mlinregress_fit(model, x_mat, y_mat);

    printf("coefficients:\n");
    mat_print(model->coefs);
    printf("intercept: %f\n", model->intercept);

    // Array *arr = arr_create(2);
    // ARR_AT(arr, 0) = 4;
    // ARR_AT(arr, 1) = 3;

    printf("predicted: %f\n", mlinregress_predict(model, (float[]){4, 3}, 2));
    // printf("predicted: %f\n", mlinregress_predict_arr(model, arr));

    mat_free_no_array(x_mat);
    mat_free_no_array(y_mat);
    mlinregress_free(model);
}
```

Run the code, instructions [here](https://adwaith-rajesh.github.io/LinearML/#testing-the-install)

```console
coefficients:
  -2.38
  3.25
intercept: 2.062500
predicted: 2.312500
```
