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

#ifndef MODEL_METRICS_PAIRWISE_H
#define MODEL_METRICS_PAIRWISE_H

#include <gsl/gsl_vector.h>

#include "ds/array.h"

typedef enum {
    cityblock = 1,
    cosine,
    euclidean,
    haversian,
    l1,
    l2,
    manhattan
} distance_metric_type;

/*
Computes the distance between two points provided as gsl_vectors
*/
double two_point_distance_gsl(gsl_vector *p1, gsl_vector *p2, distance_metric_type type);

/*
Computes the distance between two points provided as an Array
*/
double two_point_distance_arr(Array *p1, Array *p2, distance_metric_type type);

#endif
