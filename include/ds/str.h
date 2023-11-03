/*
LinearML - A Linear Algebra and Machine Learning "Library" in C
Copyright (c) 2023 Adwaith Rajesh <adwaithrajesh3180[at]gmail[dot]com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

// Str type just holds the char* and the it's hash
// used for CSV parsing that contains the string

#ifndef DS_STR_H
#define DS_STR_H

#include <stddef.h>

#define MAX_STR_LEN 16  // max string len we allow

typedef struct {
    char str[MAX_STR_LEN];  // must be null terminated char*
    double hash;            // djb2 hash for the given string
} Str;

// easy way to keep track of the original string and the associated
// has. A "not a hashtable" for Str types
typedef struct _str_list {
    Str *str;
    struct _str_list *next;
} StrList;

/*
Get the djb2 hash of the string

return values is a double so as to be compatible with the whole package
*/
double str_charp_hash(const char *str);

/*
Create a Str type for a char* (must be null terminated)
*/
Str *str_create_from_charp(char *str);

/*
Display the Str type
*/
void str_print(Str *str);

/*
Free the Str
*/
void str_free(Str *str);

/*
Initialize the StrList
*/
StrList *str_list_create();

/*
Display the StrList
*/
void str_list_print(StrList *str_list);

/*
Add a new Str to StrList and returns the original StrList

pos is set to the index position of the added Str. (can be NULL)
*/
StrList *str_list_add(StrList *str_list, Str *str, size_t *pos);

/*
Get the Str of a given hash
*/
Str *str_list_get(StrList *str_list, double hash);

/*
Free the StrList
*/
void str_list_free(StrList *str_list);

/*
Free StrList along with all the Str it holds
*/
void str_list_free_all(StrList *str_list);

#endif
