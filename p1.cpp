/**
 * p1.cpp
 * A program to find edgepoints
 */

#include "hw3.hpp"

int main(int argc, char *argv[])
{
	int rows, cols, **lapl;
	float max, d, **edges;
   char *input, *output;
	Image im;
	short s;

	if (argc < 3) {
  		fprintf(stderr, "usage: %s input output\n", argv[0]);
	}
	
	input = argv[1];
	output = argv[2];

	readImage(&im, input);
	rows = getNRows(&im);
	cols = getNCols(&im);

	edges = new float * [rows];
	for (int i = 0; i < rows; ++i)
		edges[i] = new float[cols];

	lapl = new int * [rows];
	for (int i = 0; i < rows; ++i) {
		lapl[i] = new int[cols];
		for (int j = 0; j < cols; ++j)
			lapl[i][j] = laplacian(&im, j, i);
	}

	for (int i = 0; i < rows; ++i) {
    	for (int j = 0; j < cols; ++j) {
			// check the Laplacian to see if there is an edge crossing
			if (isCrossing(lapl, j, i)) { 
				d = gradient(&im, j, i); // calculate magnitude of gradient
				edges[i][j] = d; // set edge intensity
				if (edges[i][j] > max)  // track maximum intensity for scaling
					max = edges[i][j];
			} else edges[i][j] = 0.0f; // zero non-crossings
     	}
	}
	
	// scale the edge intensities
	for (int i = 0; i < rows; ++i) {
   	for (int j = 0; j < cols; ++j) {
			s = 255*edges[i][j]/max;
			setPixel(&im, i, j, s);
		}
	}

	setColors(&im, 255);
	writeImage(&im, output);

	// deallocate stuff
	for (int i = 0; i < rows; ++i)
		delete [] edges[i];
	delete [] edges;
	free(im.data);

	return 0;
}
