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

#ifndef STATS_H
#define STATS_H

#include <stddef.h>

/*
Find the mean of an array
*/
double stats_mean(double *arr, size_t len);

/*
Find the variance
*/
double stats_var(double *arr, size_t len);

/*
Find the covariance of two matrix
*/
double stats_covar(double *arr1, double *arr2, size_t len);

/*
Returns the max value in the array
*/
double stats_max(double *arr, size_t len);

/*
Returns the min value in the array
*/
double stats_min(double *arr, size_t len);

#endif
