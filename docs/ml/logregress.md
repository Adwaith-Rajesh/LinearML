# Logistic Regression

## The math

The references that is used

- [Implementing logistic regression from scratch in Python](https://developer.ibm.com/articles/implementing-logistic-regression-from-scratch-in-python/)
- [Machine Learning using C++: A Beginner’s Guide to Linear and Logistic Regression](https://www.analyticsvidhya.com/blog/2020/04/machine-learning-using-c-linear-logistic-regression/)

The logistic regression that LinearML performs is a Binary Logistic Regression. i.e we can classify two
values

To perform a prediction, we use a bunch of values that include the weights(w), inputs(x) and bias(b).
which can be written using neural-network like formula.

$$
z = \left(\sum_{i=1}^n w_i x_i \right)
$$

We need an activation function to get our predictions, in case of binary logistic regression, it's called
the sigmoid which is usually denoted by $\sigma$ of $\hat y$, and is defined as follows.

$$
\hat y = \sigma(z) =
\begin{cases}
\frac{1}{1 + exp(-z)}, & \text{if $z$ $\geq$ 0} \\[2ex]
\frac{exp(z)}{1 + exp(z)}, & \text{otherwise}
\end{cases}
$$

In order to compute the loss we can use the following function.

$$
Loss(\hat y, y) = -\frac{1}{m} \sum_{i=1}^{m} y \log(\hat y) + (1 - y) \log(1 - \hat y)
$$

Now, to calculate the gradients to optimize your weights using gradient descent, you must calculate the derivative of your loss function

$$
\frac{\partial Loss(\hat y, y)}{\partial w} = \frac{1}{m}(\hat y - y)x_i^T
$$

$$
\frac{\partial Loss(\hat y, y)}{\partial b} = \frac{1}{m}(\hat y - y)
$$

When you have the final values from your derivative calculation, you can use it in the gradient descent equation and update the weights and bias.

## The code

Coming soon
