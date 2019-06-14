#include "Katana1.h"

Katana1::Katana1()
{
	TypeWeapon = eType::KATANA1;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::KATANA1);
	GSObject = new Sprite(GTObject, 70);
	dx = 0;
}

Katana1::~Katana1()
{
}

void Katana1::Update(Camera *camera, int t)
{
	Weapon::Update(camera, t);
	
	IsFinish = GSObject->GetIndex() == 3;
	int StartFrame = 0;  
	int EndFrame = 3;
	
	if (StartFrame <= GSObject->GetIndex() && GSObject->GetIndex() < EndFrame)
		GSObject->Update(t);
	else
	{
		GSObject->SelectIndex(StartFrame);
	}
}

void Katana1::Create(float ninjaGaiden_x, float ninjaGaiden_y, int sm_trend)
{
	Weapon::Create(ninjaGaiden_x, ninjaGaiden_y + 45, sm_trend);
	Vx = KATANA_VX*Trend;
}
