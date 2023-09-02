#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *malloc_with_check(size_t size) {
    void *p = malloc(size);
    if (p == NULL) {
        fprintf(stderr, "Could not allocate memory of size: %zu\n: %s\n", size, strerror(errno));
        exit(1);
    }
    return p;
}
