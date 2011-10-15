/**
 * p3.cpp
 */

#include "hw3.hpp"

int main(int argc, char *argv[])
{
	int threshold, rh, theta, rows, cols, rScale, tScale;
   char *inputo, *inputh, *outputl;
	float r, t, diag, x, y;
	Image io, ih;

	if (argc < 5) {
    	fprintf(stderr, "usage: %s <input original scene image> <input hough image> <hough threshold> <line-detected output image>\n", argv[0]);
		exit(0);
 	}

	inputo = argv[1];
	inputh = argv[2];
	if (sscanf(argv[3], "%d", &threshold) != 1) {
    	fprintf(stderr, "error: threshold not an integer\n");
		exit(1);
 	}
	outputl = argv[4];

	readImage(&io, inputo);
	readImage(&ih, inputh);

	rows = getNRows(&io);
	cols = getNCols(&io);
	diag = sqrt(pow(rows, 2) + pow(cols, 2));
	rScale = getNRows(&ih);
	tScale = getNCols(&ih);

	for (rh = 0; rh < rScale; ++rh)
		for (theta = 0; theta < tScale; ++theta)
			if (getPixel(&ih, rh, theta) >= threshold) {
				r = ((2*diag)/rScale)*rh - diag;
				t = (PI/tScale)*theta - PI/2;
				x = r*cos(t + PI/2);
				y = r*sin(t + PI/2);
				line(&io, y - diag*sin(t), x - diag*cos(t), y + diag*sin(t), x + diag*cos(t), 255);
			}

	setColors(&io, 255);
	writeImage(&io, outputl);

	free(io.data);
	free(ih.data);
}
