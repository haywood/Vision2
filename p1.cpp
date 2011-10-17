/**
 * p1.cpp
 * A program to find edgepoints
 */

#include "hw3.h"

int main(int argc, char *argv[])
{
	float max, d, **edges;
   char *input, *output;
	int rows, cols;
	Image im;
	short s;

	if (argc < 3) {
  		fprintf(stderr, "usage: %s input output\n", argv[0]);
		exit(0);
	}
	
	input = argv[1];
	output = argv[2];

	readImage(&im, input);
	rows = getNRows(&im);
	cols = getNCols(&im);

	edges = new float * [rows];
	for (int i = 0; i < rows; ++i)
		edges[i] = new float[cols];

	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j) {
			d = gradient(&im, j, i); // calculate magnitude of gradient
			edges[i][j] = d; // set edge intensity
			if (edges[i][j] > max)  // track maximum intensity for scaling
				max = edges[i][j];
		}
	
	// scale the edge intensities
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			s = 255*edges[i][j]/max;
			setPixel(&im, i, j, s);
		}
		delete [] edges[i];
	}
	delete [] edges;

	setColors(&im, 255);
	writeImage(&im, output);
	free(im.data);

	return 0;
}
