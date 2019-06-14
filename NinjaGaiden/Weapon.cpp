#include "Weapon.h"

Weapon::Weapon()
{
	IsFinish = 1;
}

Weapon::~Weapon()
{
	delete GTObject;
	delete GSObject;
}

void Weapon::Update(Camera * camera, int t) {

}
void Weapon::Create(float ninjaGaiden_x, float ninjaGaiden_y, int ninjaGaiden_trend)
{
	this->x = ninjaGaiden_x;
	this->y = ninjaGaiden_y;
	Trend = ninjaGaiden_trend;
	IsFinish = 0;
	GSObject->Reset();
}

void Weapon::Draw(Camera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x, y);
	if (Trend == 1) GSObject->DrawFromCenter(pos.x, pos.y);
	else GSObject->DrawFlipX(pos.x, pos.y);
}

int Weapon::GetTrend()
{
	return Trend;
}

void Weapon::SetTrend(int a)
{
	Trend = a;
}

Box Weapon::GetBox(Camera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x - GTObject->FrameWidth / 2, y + GTObject->FrameHeight / 2);
	return Box(pos.x, pos.y, GTObject->FrameWidth, GTObject->FrameHeight, Vx, -Vy);
}

void Weapon::SetXY(float x, float y)
{
	this->x = x;
	this->y = y;
}
int Weapon::GetFinish()
{
	return IsFinish;
}

int Weapon::getcurentFrame()
{
	return GSObject->_index;
}

eType Weapon::getType()
{
	return TypeWeapon;
}