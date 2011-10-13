/**
 * hw3.hpp
 * Header for hw3 files.
 */

#ifndef HW3_H_
#define HW3_H_

#include <cstdlib>
#include <iostream>
#include "vision_utilities.h"

#define DIM 2
#define OP_SIZE 3
#define OP_EPS (1+OP_SIZE/2)

static const int LAP_OP[OP_SIZE][OP_SIZE] = {
	{0,	1, 	0},
	{1,	-4, 	1},
	{0, 	1, 	0}
};

static const int GRAD_X[OP_SIZE][OP_SIZE] = {
	{-1, 0, 1},
	{-2, 0, 2},
	{-1, 0, 1},
};

static const int GRAD_Y[OP_SIZE][OP_SIZE] = {
	{	1, 	2, 	1},
	{	0, 	0, 	0},
	{	-1, 	-2, 	-1},
};

#include "Laplacian.h"

float gradient(Image *, int, int);

int rho(int, int, int, int, int, float);

#endif /* HW3_H_ */
