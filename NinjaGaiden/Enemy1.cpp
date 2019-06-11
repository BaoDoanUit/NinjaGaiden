#include "Enemy1.h"




Enemy1::Enemy1(int x1, int y1, int w1, int h1)
{
	x = x1;
	y = y1;
	h = h1;
	w = w1;
	Health = 1;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::ENEMY1);
	GSObject = new Sprite(GTObject, 120);
	/*IsFalling = 1;*/
	Trend = -1;
	type = eType::ENEMY1;
}

Box Enemy1::GetBox(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(this->x - this->w / 2, this->y + this->h / 2);
	return Box(pos.x, pos.y, this->w, this->h, Vx, -Vy);
}

void Enemy1::Update(int t)
{
	if (Health == 1)
	{
		BaseObject::Update(t);
		this->Vx = 0.18 * Trend;
		x += Vx * t;
		if (x < 0 || x > 3072 && x < 4112)
			Trend = 1;
		else if (x > 900 && x <1000)
			Trend = -1;
	}
	else
	{
		
	}
}

void Enemy1::Draw(Camera * cam)
{
	D3DXVECTOR2 pos = cam->Transform(x, y);
	if (Trend == 1) GSObject->DrawFromCenter(pos.x, pos.y);
	if (Trend == -1) GSObject->DrawFlipX(pos.x, pos.y);
}

void Enemy1::StopFall(float y)
{
	BaseObject::StopFall(y);
	this->Go();
	Vy = -1;
}

void Enemy1::Go()
{
	if (IsJumping == 1 || IsFalling == 1) return;
	BaseObject::Go();
}

Enemy1::~Enemy1()
{
}
