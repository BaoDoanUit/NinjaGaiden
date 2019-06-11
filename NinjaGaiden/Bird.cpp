#include "Bird.h"

Bird::Bird(int x1, int y1, int h1, int w1)
{
	x = x1;
	y = y1;
	h = h1;
	w = w1;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::BIRD);
	GSObject = new Sprite(GTObject, 120);
	Health = 1;
	type = eType::BIRD;
}


Bird::~Bird()
{
}
