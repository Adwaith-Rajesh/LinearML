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

#ifndef INCLUDE_LINEAR_ML_TRAIN_TEST_SPLIT
#define INCLUDE_LINEAR_ML_TRAIN_TEST_SPLIT

#include "ds/mat.h"

/*
Split the given X and Y matrix to training and testing set
The original Mat will be modified
*/
void train_test_split(Mat *X, Mat *Y, Mat **X_train, Mat **X_test, Mat **Y_train, Mat **Y_test,
                      double test_size, int rand_state);

#endif
