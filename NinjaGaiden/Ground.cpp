#include "Ground.h"



Ground::Ground(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->w = width;
	this->h = height;
	Health = 1;
	type = eType::GROUND;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::RENDERBBOX);
	GSObject = new Sprite(GTObject);
}


Ground::~Ground()
{
}

void Ground::Draw(Camera* cam)
{
	RenderBoundingBox(cam);
	return;
}
