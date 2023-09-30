# CSV

LinearML has it's own simple CSV parser.

Here is an example code on how to use it. Will be working on the code of Multiple Linear
Regression mentioned [here](../ml/multiregress.md).

Here, instead of the data being explicitly passed using Arrays, we will use CSV files.

### Example

`data.csv`

| 1   | 1   | 3.25 |
| --- | --- | ---- |
| 1   | 2   | 6.5  |
| 2   | 2   | 3.5  |
| 0   | 1   | 5.0  |

```c
#include <stdio.h>

#include "ds/mat.h"
#include "ml/multiregress.h"
#include "parsers/csv.h"

int main(void) {
    // initialize the reader for 4 row 3 col CSV file,
    // using ',' as the delimiter
    CSV *csv_reader = csv_init(4, 3, ',');

    // parse the CSV file
    csv_parse(csv_reader, "data.csv");

    // select the cols needed for X and Y values
    Mat *X = csv_get_mat(csv_reader, (int[]){0, 1}, 2);
    Mat *Y = csv_get_mat(csv_reader, (int[]){2}, 1);

    // initialize the model
    MLinearRegressionModel *model = mlinregress_init();

    // fit/train the model
    mlinregress_fit(model, X, Y);

    // print the properties.
    mat_printp(model->coefs, 7);
    printf("Intercept: %f\n", model->intercept);

    // free everything.
    mlinregress_free(model);
    mat_free(X);
    mat_free(Y);
    csv_free(csv_reader);
}

```

### Limitations of the parser

- CSV file should not have a header
- all values must exists
- all values must be floats / ints
