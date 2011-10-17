/*
* p2.cpp
*/

#include "hw3.h"

int main(int argc, char *argv[])
{
	char *inpute, *outpute, *outputh;
	int threshold, rows, cols, rh, theta, rScale, tScale, max, **a;
	Image ie, oh;
	float diag;
	
	if (argc < 5) {
		fprintf(stderr, "usage: %s <input edge image> <edge threshold> <output thresholded edge image> <output hough image>\n", argv[0]);
		exit(0);
	}
	
	inpute = argv[1];
	if (sscanf(argv[2], "%d", &threshold) != 1) {
		fprintf(stderr, "error: threshold not an integer\n");
		exit(1);
 	}
	outpute = argv[3];
	outputh = argv[4];
	
	if (readImage(&ie, inpute) == -1) {
		std::cerr << "Error reading file " << inpute << "\n";
		exit(1);
	}
	
	rows = getNRows(&ie);
	cols = getNCols(&ie);
	diag = sqrt(pow(rows, 2) + pow(cols, 2));
	rScale = diag;
	tScale = 50;
	setSize(&oh, rScale, tScale);
	a = new int * [rScale];
	for (int i = 0; i < rScale; ++i) {
		a[i] = new int[tScale];
		for (int j = 0; j < tScale; ++j)
			a[i][j] = 0;
	}
	
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
		if (getPixel(&ie, i, j) >= threshold) {
			setPixel(&ie, i, j, 1);
			for (theta = 0; theta < tScale; ++theta) {
				
				rh = rho(theta, j, i, rScale, tScale, diag);
				
				a[rh][theta]++;
				
				if (a[rh][theta] > max)
					max = a[rh][theta];
			}
		} else setPixel(&ie, i, j, 0);
		
		if (max == 0) max = 1; // avoid divide by zero
		
		for (int i = 0; i < rScale; ++i) {
			for (int j = 0; j < tScale; ++j)
				setPixel(&oh, i, j, (255*a[i][j])/max);
			delete [] a[i];
		}
		delete [] a;
		
		setColors(&oh, 255);
		setColors(&ie, 1);
		
		if (writeImage(&ie, outpute) == -1) {
			std::cerr << "Error writing file " << outpute << "\n";
		} else if (writeImage(&oh, outputh) == -1) {
			std::cerr << "Error writing file " << outpute << "\n";
		}
		
		free(ie.data);
		free(oh.data);
		
		return 0;
}
