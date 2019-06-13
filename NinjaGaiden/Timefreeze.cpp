#include "Timefreeze.h"


Timefreeze::Timefreeze(float X, float Y)
{
	type = eType::TIMEFREEZE;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::TIMEFREEZE);
	GSObject = new Sprite(GTObject, 0);

	this->x = X;
	this->y = Y;

	Vx = 0;

	Vy = TIMEFREEZE_GRAVITY;
	TimeDisplayMax = TIMEFREEZE_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

}

//void Timefreeze::Draw(Camera * camera)
//{
//	if (isFinish)
//		return;
//
//	GSObject->SelectIndex(0);
//
//	D3DXVECTOR2 pos = camera->Transform(x, y);
//	GSObject->DrawFromCenter(pos.x, pos.y);
//
//	//RenderBoundingBox(camera);
//}

Timefreeze::~Timefreeze()
{
}
