#include <stdio.h>
#include <stdlib.h>

void *malloc_with_check(size_t size) {
    void *p = malloc(size);
    if (p == NULL) {
        fprintf(stderr, "Could not allocate memory of size: %zu\n", size);
        exit(1);
    }
    return p;
}
