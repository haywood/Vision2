/**
 * p4.cpp
 */

#include "hw3.h"

int main(int argc, char *argv[])
{
	int threshold, rh, theta, rows, cols, rScale, tScale;
   char *inputo, *inputh, *inpute, *outputl;
	float r, t, diag, x, y, x0, y0, x1, y1;
	Image io, ih, ie;

	if (argc < 5) {
    	fprintf(stderr, "usage: %s <input original scene image> <input hough image> <input thresholded image> <hough threshold> <cropped line-detected output image>\n", argv[0]);
		exit(0);
 	}

	inputo = argv[1];
	inputh = argv[2];
	inpute = argv[3];
	if (sscanf(argv[4], "%d", &threshold) != 1) {
    	fprintf(stderr, "error: threshold not an integer\n");
		exit(1);
 	}
	outputl = argv[5];

	readImage(&io, inputo);
	readImage(&ih, inputh);
	readImage(&ie, inpute);

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
				x0 = x - diag*cos(t);
				y0 = y - diag*sin(t);
				x1 = x + diag*cos(t);
				y1 = y + diag*sin(t);

				while (!inImage(&io, x0, y0)) {
       			x0 += cos(t);
					y0 += sin(t);
    			}

				while (inImage(&io, x0, y0)) {
       			if (getPixel(&ie, y0, x0)) {
             		setPixel(&io, y0, x0, 255);
          		}
					x0 += cos(t);
					y0 += sin(t);
    			}
				
				//line(&io, y0, x0, y1, x1, 255);
			}

	setColors(&io, 255);
	writeImage(&io, outputl);

	free(io.data);
	free(ih.data);
	free(ie.data);
}
