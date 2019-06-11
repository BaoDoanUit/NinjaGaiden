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
	Vy = EAGLE_SPEED_Y;
	Vx = EAGLE_SPEED_X * Trend;
	Health = 1;
}

void Eagle::Update(int t)
{
	if (y - yBackup >= DeltaY)
	{
		Vy = -EAGLE_SPEED_Y;
	}
	else
		if (y - yBackup <= -DeltaY)
		{
			Vy = EAGLE_SPEED_Y;
		}
	BaseObject::Update(t); // Update dt, dx, dy
	y += dy;
	x += dx;

	GSObject->Update(t);
	if (GSObject->GetIndex() == 0)
		GSObject->Update(t);
}

//void Eagle::Draw(Camera * cam)
//{
//	D3DXVECTOR2 pos = cam->Transform(x, y);
//	if (Trend == 1) GSObject->DrawFromCenter(pos.x, pos.y);
//	if (Trend == -1) GSObject->DrawFlipX(pos.x, pos.y);
//}

Eagle::~Eagle()
{
}
