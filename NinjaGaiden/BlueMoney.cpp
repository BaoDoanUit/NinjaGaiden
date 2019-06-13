#include "BlueMoney.h"


BlueMoney::BlueMoney(float X, float Y)
{
	type = eType::BLUEMONEY;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::BLUEMONEY);
	GSObject = new Sprite(GTObject, 0);

	this->x = X;
	this->y = Y;

	Vx = 0;

	Vy = BLUEMONEY_GRAVITY;
	TimeDisplayMax = BLUEMONEY_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

}

//void BlueMoney::Draw(Camera * camera)
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

BlueMoney::~BlueMoney()
{
}
