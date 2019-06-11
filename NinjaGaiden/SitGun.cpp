#include "SitGun.h"



SitGun::SitGun(int x1, int y1, int w1, int h1)
{
	x = x1;
	y = y1;
	h = h1;
	w = w1;
	Health = 1;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::SITGUN);
	GSObject = new Sprite(GTObject, 120);
	/*IsFalling = 1;*/
	Trend = -1;
}

void SitGun::Update(int t)
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

void SitGun::Draw(Camera * cam)
{
	D3DXVECTOR2 pos = cam->Transform(x, y);
	if (Trend == 1) GSObject->DrawFromCenter(pos.x, pos.y);
	if (Trend == -1) GSObject->DrawFlipX(pos.x, pos.y);	
}

void SitGun::StopFall(float y)
{
	IsFalling = 0;
	this->Go();
	Vy = -1;
}


void SitGun::Go()
{
	if (IsJumping == 1 || IsFalling == 1) return;
	BaseObject::Go();
}

SitGun::~SitGun()
{
}
