/**
* p4.cpp
*/

#include "hw3.h"

int main(int argc, char *argv[])
{
	int threshold, rh, theta, rows, cols, rScale, tScale, hitImage;
	char *inputo, *inputh, *inpute, *outputl;
	float r, t, diag, x, y, x0, y0, x1, y1, c, s;
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
			c = cos(t);
			s = sin(t);
			
			x = -r*s; // cos(t + pi/2) = -sin(t)
			y = r*c; // sin(t + pi/2) = cos(t)
			x0 = x - diag*c;
			y0 = y - diag*s;
			x1 = x + diag*c;
			y1 = y + diag*s;
			
			hitImage = 0;
			while (!hitImage || inImage(&io, x0, y0)) {
				if (getPixel(&ie, y0, x0)) {
					setPixel(&io, y0, x0, 255);
				}
				x0 += c;
				y0 += s;
				if (inImage(&io, x0, y0) && !hitImage)
					hitImage = 1;
			}
    		}
    		
    		setColors(&io, 255);
    		writeImage(&io, outputl);
    		
    		free(io.data);
    		free(ih.data);
    		free(ie.data);
}
