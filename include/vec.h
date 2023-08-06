/*
LinearML - A Linear Algebra and Machine Learning "Library" in C
Copyright (c) 2023 Adwaith Rajesh <adwaithrajesh3180[at]gmail[dot]com>

LICENSE: MIT

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef VEC_H
#define VEC_H

typedef struct {
    int dim;
    double *elems;
} Vec;

#define Vec2(...) Vec_create(2, (double[]){__VA_ARGS__})

/*
Allocates a new Vec pointer.

dim - The dimension of the vector
elems - Each scalar value that makes the N dimensional vector
*/
Vec *Vec_create(int dim, double *elems);

/*
Frees the allocated Vec*

It will not free the elem

vec - The vector to be freed
*/
void Vec_free(Vec *vec);

/*
Display the Vec in a nice manner.

vec - The vector to be displayed
*/
void Vec_display(Vec *vec);

// Basic operations

/*
Add Vector v1 to v2 and returns v2
*/
Vec *Vec_add(Vec *v1, Vec *v2);

/*
Subtracts vector v1 from v2 and returns v2
*/
Vec *Vec_sub(Vec *v1, Vec *v2);

/*
Multiply a scalar value to the vector and returns it
*/
Vec *Vec_scalar_multiply(Vec *vec, double scalar_val);

/*
Find the norm of a vector
*/
double *Vec_norm(Vec *vec);

/*
Find the dot product of two vectors
*/
double *Vec_dot_product(Vec *v1, Vec *v2);

/*
Find the cross product of a 3D vector
*/
Vec *Vec_cross_product(Vec *v1, Vec *v2);

/*
Convert the given vector to a unit vector
*/
Vec *Vec_to_unit(Vec *vec);

/*
Get the angle between two vectors
*/
float *Vec_get_angle(Vec *v1, Vec *v2);

#endif
