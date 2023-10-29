#include "ds/str.h"

#include <stdio.h>
#include <string.h>

#include "utils/mem.h"

unsigned long str_charp_hash(const char *str) {
    unsigned long hash = 5381;
    int c = 0;  // store the current char
    int count = 0;

    for (c = *str; (count < MAX_STR_LEN) && (*str != 0); str++, count++) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

Str *str_create_from_charp(char *str) {
    Str *new_str = malloc_with_check(sizeof(Str));
    strncpy(new_str->str, str, MAX_STR_LEN - 1);
    new_str->str[MAX_STR_LEN - 1] = '\0';
    new_str->hash = str_charp_hash(new_str->str);
    return new_str;
}

void str_print(Str *str) {
    if (str == NULL) return;
    printf("Str(str: '%s', hash: %lu)\n", str->str, str->hash);
}

void str_free(Str *str) {
    if (str == NULL) return;
    free(str);
}
