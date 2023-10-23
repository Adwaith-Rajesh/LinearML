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

#ifndef LINEAR_ML_VEC_H
#define LINEAR_ML_VEC_H

typedef struct {
    int dim;
    float *elems;
} Vec;

#define Vec2(...) vec_create(2, (float[]){__VA_ARGS__})

/*
Set the precision for printing the elements in the vector
*/
void set_vec_print_prec(int prec);

/*
Allocates a new Vec pointer.

dim - The dimension of the vector
elems - Each scalar value that makes the N dimensional vector
*/
Vec *vec_create(int dim, float *elems);

/*
Frees the allocated Vec*

It will not free the elem

vec - The vector to be freed
*/
void vec_free(Vec *vec);

/*
Free the Vec along with the Vec->elem
*/
void vec_free_elem(Vec *vec);

/*
Display the Vec in a nice manner.

vec - The vector to be displayed
*/
void vec_print(Vec *vec);

// Basic operations

/*
Add Vector v2 to v1 and returns v1
On error return NULL and sets the error message
*/
Vec *vec_add(Vec *v1, Vec *v2);

/*
Subtracts vector v2 from v1 and returns v1
On error return NULL and sets the error message
*/
Vec *vec_sub(Vec *v1, Vec *v2);

/*
Multiply a scalar value to the vector and returns it
On error return NULL and sets the error message
*/
Vec *vec_scalar_multiply(Vec *vec, float scalar_val);

/*
Find the norm of a vector

Return -1 on error and sets the error msg
*/
float vec_norm(Vec *vec);

/*
Find the dot product of two vectors
*/
float vec_dot(Vec *v1, Vec *v2);

/*
Find the cross product of a 3D vector and returns a new
Vec which need to be freed
On error return NULL and sets the error message
*/
Vec *vec_cross(Vec *v1, Vec *v2);

/*
Convert the given vector to a unit vector
On error return NULL and sets the error message
*/
Vec *vec_to_unit(Vec *vec);

/*
Get the angle between two vectors in radians
*/
float vec_get_angle(Vec *v1, Vec *v2);

#endif
