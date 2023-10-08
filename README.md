![LinearML Logo](/docs/assets/linear_ml_banner.png)

A Linear Algebra and Machine Learning "Library" in C

---

# Why.....

Well, I'm currently doing my bachelors in AI&DS so it just appropriate that I try out
every machine learning algo I learn. And not just try these algorithms but also package
them in such a way that I can use these Algo's instead of third-party ones.

This package, even if I try for the next 10 years, will not be anywhere close to the the
third party packages. This is just a learning experience for me. This package is meant
to grow with me as I learn new Machine Learning Algo or anything similar

## Some goals

- All the algo will be written in C
- There will be compilation options to
  - Compile everything to a single shared object file.
  - Compile individual packages. eg just the Vec package, ML ..etc
- Have nice API's to interact with Python

### Example

```c
#include "ds/mat.h"
#include "ml/linregress.h"
#include "model/serializer.h"
#include "model/train_test_split.h"
#include "parsers/csv.h"

int main(void) {
    CSV *csv_reader = csv_init(1000, 3, ',');
    csv_parse(csv_reader, "data/placement.csv");

    Mat *X = csv_get_mat(csv_reader, (int[]){0}, 1);
    Mat *Y = csv_get_mat(csv_reader, (int[]){2}, 1);

    Mat *X_train, *X_test, *Y_train, *Y_test;
    train_test_split(X, Y, &X_train, &X_test, &Y_train, &Y_test, 0.3, 100);

    LinearRegressionModel *model = linregress_init();
    linregress_fit_mat(model, X_train, Y_train);
    // model_deserialize(model, LinearRegression, "placement.model");

    printf("score: %lf\n", linregress_score_mat(model, X_test, Y_test));
    printf("slope: %lf\n", model->slope);
    printf("intercept: %lf\n", model->intercept);
    printf("rvalue: %lf\n", model->rvalue);

    model_serialize(model, LinearRegression, "placement.model");

    linregress_free(model);
    mat_free_many(6, X, Y, X_train, X_test, Y_train, Y_test);
    csv_free(csv_reader);
}
```

The dataset used can be found [here](https://www.kaggle.com/datasets/mayurdalvi/simple-linear-regression-placement-data)
This dataset should no be trained on a Linear Regression Model. As of writing this README,
Logistic Regression is not yet implemented so we are stuck with this.

### Docs

Docs for LinearML can be found [here](https://adwaith-rajesh.github.io/LinearML/)

## Bye...
