#include "Eagle.h"





Eagle::Eagle(int x1, int y1, int w1, int h1)
{
	x = x1;
	y = y1;
	h = h1;
	w = w1;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::EAGLE);
	GSObject = new Sprite(GTObject, 120);
	/*IsFalling = 1;*/
	Trend = -1;

	this->yBackup = y;
	Vx = SPEED_X;
	Vy = SPEED_Y;
	ax = ACCELERATION_X;
	Health = 1;
	type = eType::EAGLE;
}

void Eagle::Update(int t)
{
	if (Health)
		GSObject->Update(t);

	if (GSObject == NULL || !Health)
		return;

	if (x < ninja->x - 80 && y < ninja->y + 20) {
		Vx = 0;
		Vy = SPEED_Y;
		
	}
	else if (x < ninja->x - 80 && y > ninja->y + 20) {
		Vx = SPEED_X;
		Trend = 1;
		Vy = -SPEED_Y;

	}
	else if (x >= ninja->x + 80 && y > ninja->y + 20) {
		Vx = -SPEED_X;
		Trend = -1;
		Vy = -SPEED_Y;
	}
	else if (x >= ninja->x + 80 && y < ninja->y + 20) {
		Vx = 0;
		Vy = SPEED_Y;
	}


	x += Vx * t + 1 / 2 * ax*t*t;
	y += Vy * t;
}

void Eagle::setPositionNinja(D3DXVECTOR2 * ninja)
{
	this->ninja = ninja;
}

void Eagle::SetActive()
{
}



Eagle::~Eagle()
{
}
