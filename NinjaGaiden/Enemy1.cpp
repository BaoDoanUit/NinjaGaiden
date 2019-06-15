#include "Enemy1.h"



#define THIEF_SPEED_X 0.07f
Enemy1::Enemy1(int x1, int y1, int w1, int h1, int borderLeft1, int borderRight1)
{
	x = x1;
	y = y1;
	h = h1;
	w = w1;
	borderLeft = borderLeft1;
	borderRight = borderRight1;
	Health = 1;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::ENEMY1);
	GSObject = new Sprite(GTObject, 120);
	/*IsFalling = 1;*/
	Trend = -1;
	type = eType::ENEMY1;
	Vx = THIEF_SPEED_X;
	IsCreateBullet = 0;
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
		if (x <= borderLeft || x >= borderRight)
		{
			Trend *= -1;
		}
		this->Vx = THIEF_SPEED_X * Trend;
		x += Vx * t;
		BaseObject::Update(t);
	}
	
}

void Enemy1::Attack(Weapon *weapon)
{
	IsCreateBullet = 1;
	if (weapon)
	{
		weapon->Create(x, y, Trend);
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
