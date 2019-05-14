#include "Enemy2.h"




Enemy2::Enemy2(int x1, int y1, int w1, int h1)
{
	x = x1;
	y = y1;
	h = h1;
	w = w1;
	GTObject = new Texture("./Resources/enemy/enemy2.png", 3, 1, 3);
	GSObject = new Sprite(GTObject, 120);
	IsFalling = 1;
	Trend = -1;
}

Box Enemy2::GetBox(Camera * camera)
{
	D3DXVECTOR2 pos = camera->Transform(this->x - this->w / 2, this->y + this->h / 2);
	return Box(pos.x, pos.y, this->w, this->h, Vx, -Vy);
}

void Enemy2::Update(int t)
{
	if (IsFalling == 1)
	{
		y += Vy;
		Vy = Vy - ENEMY_GRAVITY;
	}
	else
	{
		BaseObject::Update(t);
		this->Vx = 0.18 * Trend;
		x += Vx * t;
		if (x < 0 || x > 3072 && x < 4112)
			Trend = 1;
	}
}

void Enemy2::Draw(Camera * cam)
{
	D3DXVECTOR2 pos = cam->Transform(x, y);
	if (Trend == 1) GSObject->DrawFromCenter(pos.x, pos.y);
	if (Trend == -1) GSObject->DrawFlipX(pos.x, pos.y);
}

void Enemy2::StopFall(float y)
{
	IsFalling = 0;
	this->Go();
	Vy = -1;
}

void Enemy2::Go()
{
	if (IsJumping == 1 || IsFalling == 1) return;
	BaseObject::Go();
}

Enemy2::~Enemy2()
{
}