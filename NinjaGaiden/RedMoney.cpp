#include "RedMoney.h"


RedMoney::RedMoney(float X, float Y)
{
	type = eType::REDMONEY;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::REDMONEY);
	GSObject = new Sprite(GTObject, 0);

	this->x = X;
	this->y = Y;

	Vx = 0;

	Vy = REDMONEY_GRAVITY;
	TimeDisplayMax = REDMONEY_TIMEDISPLAYMAX; // set time hiển thị tối đa
	TimeDisplayed = 0;

}

//void RedMoney::Draw(Camera * camera)
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

RedMoney::~RedMoney()
{
}
