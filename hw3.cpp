#include "hw3.h"

float gradient(Image *im, int x, int y)
{
	x--; y--;
	int grad[] = {0, 0};
	for (int i = 0; i < OP_SIZE; ++i) {
		for (int j = 0; j < OP_SIZE; ++j) {
			grad[0] += GRAD_X[i][j]*getPixel(im, y+j, x+i);
			grad[1] += GRAD_Y[i][j]*getPixel(im, y+j, x+i);
		}
  	}
	
	grad[0] *= pow(OP_EPS, -2);
	grad[1] *= pow(OP_EPS, -2);
	
	return sqrt(pow(grad[0], 2)+pow(grad[1], 2));
}

int rho(int theta, int x, int y, int rScale, int tScale, float diag)
{
   float t = (PI/tScale)*theta - PI/2;
   float r = (y*cos(t) - x*sin(t));
   return (rScale/(2*diag))*(r + diag);
}

int inImage(Image * im, int x, int y)
{
   return (x >= 0 && y >= 0 && x < getNCols(im) && y < getNRows(im));
}
