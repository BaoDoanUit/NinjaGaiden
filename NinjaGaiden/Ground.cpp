#include "Ground.h"



Ground::Ground(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->w = width;
	this->h = height;
	Health = 1;
}


Ground::~Ground()
{
}
