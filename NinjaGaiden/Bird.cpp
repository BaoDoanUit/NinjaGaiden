#include "Bird.h"



Bird::Bird(int x1, int y1, int h1, int w1)
{
	x = x1;
	y = y1;
	h = h1;
	w = w1;
	GTObject = new Texture("./Resources/enemy/bird.png", 2, 1, 2);
	GSObject = new Sprite(GTObject, 100);
}


Bird::~Bird()
{
}
