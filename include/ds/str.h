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

#define MAX_STR_LEN 32  // max string len we allow

typedef struct {
    char str[MAX_STR_LEN];  // must be null terminated char*
    unsigned long hash;     // djb2 hash for the given string
} Str;

/*
Get the djb2 hash of the string
*/
unsigned long str_charp_hash(const char *str);

/*
Create a Str type for a char* (must be null terminated)
*/
Str *str_create_from_charp(const char *str);

/*
Display the Str type
*/
void str_print(Str *str);

/*
Free the Str
*/
void str_free(Str *str);

#endif
