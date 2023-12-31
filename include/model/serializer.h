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

#ifndef MODEL_SERIALIZER_H
#define MODEL_SERIALIZER_H

typedef enum {
    LinearRegression,
    MLinearRegression
} model_type;

/*
Serialize the given model into a binary file
*/
void model_serialize(void *model, model_type type, const char *filepath);

/*
Deserialize the model from the binary file
*/
void model_deserialize(void *model, model_type type, const char *filepath);

#endif
