#include "Bee.h"

Bee::Bee(int x1, int y1, int h1, int w1)
{
	x = x1;
	y = y1;
	h = h1;
	w = w1;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::BEE);
	GSObject = new Sprite(GTObject, 100);
	Health = 1;
}

Bee::~Bee()
{
}
