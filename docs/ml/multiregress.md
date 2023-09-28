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
