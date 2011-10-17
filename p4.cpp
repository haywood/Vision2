/**
 * p4.cpp
 */

#include "hw3.h"

int main(int argc, char *argv[])
{
	int threshold, rh, theta, rows, cols, rScale, tScale, hitImage;
	char *inputo, *inputh, *inpute, *outputl;
	float r, t, diag, x, y, c, s;
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

	if (readImage(&io, inputo) == -1) {
		std::cerr << "Error reading file " << inputo << "\n";
		exit(1);
	} else if (readImage(&ih, inputh) == -1) {
		std::cerr << "Error reading file " << inputh << "\n";
		exit(1);
	} else if (readImage(&ie, inpute) == -1) {
		std::cerr << "Error reading file " << inpute << "\n";
		exit(1);
	}	
	rows = getNRows(&io);
	cols = getNCols(&io);
	diag = sqrt(pow(rows, 2) + pow(cols, 2));
	rScale = getNRows(&ih);
	tScale = getNCols(&ih);

	for (rh = 0; rh < rScale; ++rh) {
		for (theta = 0; theta < tScale; ++theta) {
			if (getPixel(&ih, rh, theta) >= threshold) {
				r = ((2*diag)/rScale)*rh - diag;
				t = (PI/tScale)*theta - PI/2;
				c = cos(t);
				s = sin(t);

				x = -r*s - diag*c; // cos(t + pi/2) = -sin(t)
				y = r*c - diag*s; // sin(t + pi/2) = cos(t)

				hitImage = 0;
				while (!hitImage || inImage(&io, x, y)) {
					if (!hitImage && inImage(&io, x, y))
						hitImage = 1;
					if (hitImage && getPixel(&ie, y, x)) {
						setPixel(&io, y, x, 255);
					}
					x += c;
					y += s;
				}
			}
		}
	}

	setColors(&io, 255);
	if (writeImage(&io, outputl) == -1) {
		std::cerr << "Error writing file " << outputl << "\n";
	}
	free(io.data);
	free(ih.data);
	free(ie.data);
}







