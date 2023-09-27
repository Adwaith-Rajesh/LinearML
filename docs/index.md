![LinearML banner](/assets/linear_ml_banner.png)

A learning project where I try to build a ML library from scratch in C.

## Building LinearML

LinearML uses [BuildMe](https://github.com/Adwaith-Rajesh/buildme) as it's build system. It's a build system that I made. It is still WIP.

Install the BuildMe with the command

```console
pip3 install buildme
```

Clone the repo

```console
git clone --depth=1 -b master https://github.com/Adwaith-Rajesh/LinearML.git
```

Compile the `liblinearml.so`

```console
cd ./LinearML
chmod +x buildme
```

```console
./buildme all
```

This will create a `build` folder where the shared object will be present in the `build/lib` folder

## Testing the install

Let's create a simple Array and print it to check whether everything works

```console
touch test_lm.c
```

```c
// test_lm.c

#define INCLUDE_ARRAY_STATS
#include "ds/array.h"

int main(void) {
    Array *arr = arr_create(3);

    ARR_AT(arr, 0) = 1;
    ARR_AT(arr, 1) = 4;
    ARR_AT(arr, 2) = 5;

    arr_print(arr);
    arr_free(arr);

    return 0;
}
```

Compile

```console
gcc -o test_lm test_lm.c -I./include -L./build/lib -llinearml -lm
```

Run

```console
$ LD_LIBRARY_PATH=./build/lib ./test_lm
[ 1.00 4.00 5.00 ]
```
