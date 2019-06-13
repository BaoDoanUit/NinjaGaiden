#include "Spiritual2.h"


Spiritual2::Spiritual2(float X, float Y)
{
	type = eType::SPIRITUAL2;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::SPIRITUAL2);
	GSObject = new Sprite(GTObject, 0);

	this->x = X;
	this->y = Y;

	Vx = 0;

	Vy = SPIRITUAL2_GRAVITY;
	TimeDisplayMax = SPIRITUAL2_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

}

//void Spiritual2::Draw(Camera * camera)
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

Spiritual2::~Spiritual2()
{
}
