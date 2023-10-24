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
#define INCLUDE_MAT_CONVERSIONS
#include "ds/mat.h"
#include "ml/logisticregress.h"
#include "model/metrics.h"
#include "model/train_test_split.h"
#include "parsers/csv.h"

int main(void) {
    CSV *csv_reader = csv_init(569, 31, ',');
    csv_parse(csv_reader, "data/bcancer.csv");

    Mat *X = csv_get_mat_slice(csv_reader, (Slice){1, 31});
    Mat *Y = csv_get_mat_slice(csv_reader, (Slice){0, 1});
    Mat *X_train, *X_test, *Y_train, *Y_test;

    train_test_split(X, Y, &X_train, &X_test, &Y_train, &Y_test, 0.3, 101);

    logregress_set_max_iter(2000);
    LogisticRegressionModel *model = logregress_init();
    logregress_fit(model, X_train, Y_train);

    Array *preds = logregress_predict_many(model, X_test);
    Array *true = mat_get_col_arr(Y_test, 0);

    logregress_print(model);

    printf("confusion matrix: \n");
    Mat *conf_mat = model_confusion_matrix(true, preds);
    mat_print(conf_mat);

    arr_free(true);
    arr_free(preds);
    logregress_free(model);
    mat_free_many(7, X, Y, X_test, X_train, Y_test, Y_train, conf_mat);
    csv_free(csv_reader);
}
```

<details>
  <summary>Output</summary>

```console
LogisticRegressionModel(bias: 0.5159147, loss: -12.4263621, weights: 0x5556e8a732c0)
weights:
1546.6922009
1139.6829595
8552.1648900
2522.0044946
11.8724211
-19.3345598
-44.9646156
-18.4984994
23.8378678
10.1676564
0.2338315
103.3839701
-139.7864354
-4498.8563443
0.2662770
-6.5798244
-8.6158697
-1.6938180
1.6508702
-0.3857419
1650.7843571
1445.0283208
8312.7672485
-4024.9280673
13.2972726
-72.4527931
-111.8298475
-26.6204266
28.0612275
5.4099162
confusion matrix:
  57.00   10.00
  2.00   101.00

```

</details>

The dataset used can be found [here](https://gitlab.com/adwaithrajesh/linear-ml-test/-/blob/main/data/bcancer.csv?ref_type=heads). which is a modified version of [this](https://www.kaggle.com/datasets/uciml/breast-cancer-wisconsin-data) dataset

### Docs

Docs for LinearML can be found [here](https://adwaith-rajesh.github.io/LinearML/)

## Bye...
