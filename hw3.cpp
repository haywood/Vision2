#include "hw3.hpp"

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

int laplacian(Image *im, int x, int y)
{
   x--; y--;
	int s = 0;
	for (int i = 0; i < OP_SIZE; ++i)
		for (int j = 0; j < OP_SIZE; ++j)
			s += getPixel(im, y+i, x+j)*LAP_OP[i][j];
	return s*pow(OP_EPS, -2);
}

int isNeg(int n) { return (n < 0) ? 1 : 0; }

int isCrossing(int ** lapl, int x, int y)
{
   int n [] = {
      x > 0 ? lapl[y][x-1] : 0,
		x > 0 && y > 0 ? lapl[y-1][x-1] : 0,
		y > 0 ? lapl[y-1][x] : 0
   };

	for (int i = 0; i < 3; ++i)
		if (isNeg(lapl[y][x]) != isNeg(n[i]))
			return true;

	return false;
}

int rho(int theta, int x, int y, int rScale, int tScale, float diag)
{
   float t = (PI/tScale)*theta - PI/2;
	float r = (y*cos(t) - x*sin(t));
	return (rScale/(2*diag))*(r + diag);
}
