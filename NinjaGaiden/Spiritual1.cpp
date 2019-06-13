#include "Spiritual1.h"


Spiritual1::Spiritual1(float X, float Y)
{
	type = eType::SPIRITUAL1;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::SPIRITUAL1);
	GSObject = new Sprite(GTObject, 0);

	this->x = X;
	this->y = Y;

	Vx = 0;

	Vy = SPIRITUAL1_GRAVITY;
	TimeDisplayMax = SPIRITUAL1_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

}

//void Spiritual1::Draw(Camera * camera)
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

Spiritual1::~Spiritual1()
{
}
