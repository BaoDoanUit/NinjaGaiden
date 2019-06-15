#include "WindmillStar.h"

WindmillStar * WindmillStar::Instance = NULL;

WindmillStar::WindmillStar()
{
	GTObject = TextureManager::GetInstance()->GetTexture(eType::WINDMILLSTAR);
	GSObject = new Sprite(GTObject, 100);
	TypeWeapon = eType::WINDMILLSTAR;
	BackupX = x;
	BackupY = y;
	BackupTrend = Trend;
	GSObject->SelectIndex(0);
}



void WindmillStar::Update(Camera* camera, int t)
{
	//if (!camera->CHECK_OBJECT_IN_CAMERA(this)) // ra khỏi cam thì kết thúc
	//{
	//	isFinish = true;
	//	return;
	//}
	if (IsFinish)
		return;
	//DebugOut(L"STAR backupX =%f\t backupY = %f\n", BackupX, backupY);
	if (abs(x - xNinja) >= DELTAX && abs(x - xNinja) < DELTAX + 15)
	{
		xStart = x;
		Trend *= -1;
		Vx *= Trend;
		Vy = 0;
	}
	else
	{

		if (BackupTrend == 1)
		{
			if (x < BackupX && Trend == -1 && y > BackupY)
			{
				Vy -= 0.0008f * t;
			}
			else if (x > BackupX && Trend == 1 && y < BackupY)
			{
			
				Vy += 0.0008f * t;

			}
			else if (y < BackupY - 100)
			{
				Vy += 0.0008f * t;

			}
		}
		else
		{
			if (x > BackupX && Trend == 1 && y > BackupY)
			{
				Vy -= 0.0008f * t;
			}
			else if (x < BackupX && Trend == -1 && y < BackupY)
			{
				Vy += 0.0008f * t;
			}
			else if (y < BackupY - 100)
			{
				Vy += 0.0008f * t;

			}
		}
	}

	x += Vx;
	y += Vy;
	int StartFrame = 0; 
	int EndFrame = 2;

	if (StartFrame <= GSObject->GetIndex() && GSObject->GetIndex() < EndFrame)
		GSObject->Update(t);
	else
	{
		GSObject->SelectIndex(StartFrame);

	}


}

void WindmillStar::Create(float ninjaGaiden_x, float ninjaGaiden_y, int sm_trend)
{
	Weapon::Create(ninjaGaiden_x, ninjaGaiden_y + 45, sm_trend);
	xNinja = ninjaGaiden_x;
	yNinja = ninjaGaiden_y;
	Vx = WPWINDMILLSTAR_GRAVITY*Trend;
}



