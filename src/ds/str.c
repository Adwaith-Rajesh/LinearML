#include "ds/str.h"

#include <stdio.h>
#include <string.h>

#include "utils/mem.h"

double str_charp_hash(const char *str) {
    double hash = 5381;
    int c = 0;  // store the current char
    int count = 0;

    for (c = *str; (count < MAX_STR_LEN) && (*str != 0); str++, count++) {
        hash = ((hash * 32) + hash) + c;
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
    printf("Str(str: '%s', hash: %lf)\n", str->str, str->hash);
}

void str_free(Str *str) {
    if (str == NULL) return;
    free(str);
}

StrList *str_list_create() {
    StrList *new_str_list = malloc_with_check(sizeof(StrList));
    new_str_list->str = NULL;
    new_str_list->next = NULL;
    return new_str_list;
}

void str_list_print(StrList *str_list) {
    StrList *temp = str_list;
    while (temp != NULL) {
        if (temp->str != NULL) {
            str_print(temp->str);
        }
        temp = temp->next;
    }
}

StrList *str_list_add(StrList *str_list, Str *str, size_t *pos) {
    if (str_list == NULL) return NULL;

    size_t npos = 0;
    StrList *temp = str_list;

    if (temp->str == NULL) {
        if (pos != NULL) *pos = npos;
        temp->str = str;
        return str_list;
    }

    StrList *new_node = str_list_create();
    new_node->str = str;

    while (temp->next != NULL) {
        pos++;
        temp = temp->next;
    }

    if (pos != NULL) *pos = npos;
    temp->next = new_node;
    return str_list;
}

Str *str_list_get(StrList *str_list, double hash) {
    if (str_list == NULL) return NULL;

    StrList *temp = str_list;
    while (temp != NULL) {
        if (temp->str->hash == hash) {
            return temp->str;
        }
    }
    return NULL;
}

void str_list_free(StrList *str_list) {
    if (str_list == NULL) return;

    StrList *temp;
    while (str_list != NULL) {
        temp = str_list;
        str_list = str_list->next;
        free(temp);
    }
}

void str_list_free_all(StrList *str_list) {
    if (str_list == NULL) return;

    StrList *temp;
    while (str_list != NULL) {
        temp = str_list;
        str_list = str_list->next;

        if (temp->str != NULL) {
            str_free(temp->str);
        }
        free(temp);
    }
}
