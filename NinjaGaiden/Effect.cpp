#include "Effect.h"


Effect::Effect(float X, float Y)
{
	x = X;
	y = Y;
	type = eType::EFFECT;
	GTObject = TextureManager::GetInstance()->GetTexture(type);
	GSObject = new Sprite(GTObject, 70);
	isFinish = false;
}

Effect::~Effect()
{
}


void Effect::Update(DWORD dt)
{
	if (GSObject->GetIndex() > 2)
		isFinish = true;
	GSObject->Update(dt);

}

void Effect::Render(Camera * camera)
{

	D3DXVECTOR2 pos = camera->Transform(x, y);
	GSObject->DrawFromCenter(pos.x, pos.y);
}
