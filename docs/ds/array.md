# Array

#### Structure

```c
typedef struct {
    size_t size;
    float *arr;
} Array;
```

Array is LinearML way of storing both the C array and the number of elements at the
same time.

### Examples

#### 1. Creating a simple Array

```c
#include "ds/array.h"

int main(void) {
    // create an array with 3 values
    Array *arr = arr_create(3);

    ARR_AT(arr, 0) = 1;  // set arr[0] = 1
    ARR_AT(arr, 1) = 4;  // set arr[1] = 4
    ARR_AT(arr, 2) = 5;  // set arr[2] = 5

    arr_print(arr);

    // free Array crated using arr_crate
    arr_free(arr);

    return 0;
}
```

```console
[ 1.00 4.00 5.00 ]
```

#### 2. Create an Array using existing C array

```c
#include "ds/array.h"

int main(void) {
    float arr_vals[] = {1, 2, 3, 4};

    // use an existing C array with 4 values
    Array *arr = arr_init(arr_vals, 4);

    ARR_AT(arr, 0) = 5;  // set arr[0] = 5
    arr_print(arr);

    // free Array crated using arr_init
    arr_init_free(arr);
    return 0;
}
```

```console
[ 5.00 2.00 3.00 4.00 ]
```

#### 3. Changing the float precision during printing

```c
#include "ds/array.h"

int main(void) {
    // create an array with 3 values
    Array *arr = arr_create(3);

    ARR_AT(arr, 0) = 1;  // set arr[0] = 1
    ARR_AT(arr, 1) = 4;  // set arr[1] = 4
    ARR_AT(arr, 2) = 5;  // set arr[2] = 5

    // use arr_printp instead of arr_print
    arr_printp(arr, 0);

    // free Array crated using arr_crate
    arr_free(arr);

    return 0;
}
```

```console
[ 1 4 5 ]
```

#### 4. Map a function over the Array

```c
#include "ds/array.h"

float add_three(float val) {
    return val + 3;
}

int main(void) {
    // create an array with 3 values
    Array *arr = arr_create(3);

    ARR_AT(arr, 0) = 1;  // set arr[0] = 1
    ARR_AT(arr, 1) = 4;  // set arr[1] = 4
    ARR_AT(arr, 2) = 5;  // set arr[2] = 5

    // the function will return the same array back for
    // convenience reasons
    arr_print(arr_map(arr, add_three));

    // free Array crated using arr_crate
    arr_free(arr);

    return 0;
}
```

```console
[ 4.00 7.00 8.00 ]
```

#### 5. Array stats

```c
#include <stdio.h>

#define INCLUDE_ARRAY_STATS
#include "ds/array.h"


int main(void) {
    // create an array with 3 values
    Array *arr = arr_create(3);

    ARR_AT(arr, 0) = 1;  // set arr[0] = 1
    ARR_AT(arr, 1) = 4;  // set arr[1] = 4
    ARR_AT(arr, 2) = 5;  // set arr[2] = 5

    arr_print(arr);

    printf("Mean: %.2f\n", arr_mean(arr));
    printf("Max: %.2f\n", arr_max(arr));
    printf("Min: %.2f\n", arr_min(arr));

    // free Array crated using arr_crate
    arr_free(arr);

    return 0;
}
```

```console
[ 1.00 4.00 5.00 ]
Mean: 3.33
Max: 5.00
Min: 1.00
```
