#include "SceneMain.h"

SceneMain::SceneMain(int nCmdShow) : Game(nCmdShow) {}

SceneMain::~SceneMain(void) {}

void SceneMain::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t) {

	d3ddv->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

	if (State == -1) {
		// RenderMenu(t);
	}
	else if (State == 0) {
		// RenderIntro(t);
	}
	else {
		ninjaGaiden->Update(cam, t);
		RenderStage(d3ddv, State);
		UpdateObject(cam, t);
	}
	G_SpriteHandler->End();
}

void SceneMain::RenderStage(LPDIRECT3DDEVICE9 d3ddv, int t) {
	if (pMap) {
		pMap->Render2(cam);
	}
	ClearListObject();

	gridGame->GetListObject(listObj, cam);
	//TODO Draw ListObj GridGame
	for (UINT i = 0; i < listObj.size(); i++)
	{
		switch (listObj[i]->GetType())
		{
		case eType::GROUND:
			listGround.push_back(listObj[i]);
			break;
		default:
			listObj[i]->setPositionNinja(ninjaGaiden->getPos());
			listEnemy.push_back(listObj[i]);
			break;
		}
		listObj[i]->Draw(cam);
	}
	ninjaGaiden->Draw(cam);
	G_SpriteHandler->End();
}
void SceneMain::LoadComponent()
{
	gridGame = new Grid();
}

void SceneMain::ClearListObject()
{
	listObj.clear();
	listEnemy.clear();
	listGround.clear();
	listItem.clear();
}

void SceneMain::LoadResources(LPDIRECT3DDEVICE9 d3ddv) {
	LoadComponent();
	switch (State) {
	case -1:
		// maps = new Map(State);
		ninjaGaiden = new NinjaGaiden(G_ScreenWidth, 76, -1);
		break;
	case 1:
		LoadMap1();
		break;
	case 2:
		LoadMap2();
		break;
	case 3:
		LoadMap3();
		break;
	default:
		break;
	}
}

void SceneMain::LoadMap1() {
	AutoFit = 0; // Sử dụng biến này khi viewport.y của màn 2 khác với width của
				 // màn hình nên tọa độ item cộng thêm AutoFit
	ninjaGaiden = new NinjaGaiden(120, 120, 1);
	cam = new Camera(ninjaGaiden->getx(), 1);
	cam->SetSizeMap(0, 4096);
	ninjaGaiden->Go();
	gridGame->SetFile("./Resources/maps/map2.txt");
	gridGame->ReloadGrid();
	SAFE_DELETE(pMap);

	pMap = new Map("./Resources/maps/3-1.json");
	



}

void SceneMain::LoadMap2() {}

void SceneMain::LoadMap3() {}
void SceneMain::OnKeyDown(int KeyCode) {
	if (lockKeyboard == 0) {
		if (IsKeyDown(DIK_UP)) {
			isPlay_Exit = true;
		}
		if (IsKeyDown(DIK_DOWN)) {
			isPlay_Exit = false;
		}
		if (IsKeyDown(DIK_RETURN)) {
			if (isPlay_Exit) {
				State = 0;
				// maps = new Map(State);
				ninjaGaiden = new NinjaGaiden(G_ScreenWidth - 10, 370, -1);
			}
			else
				PostMessage(G_hWnd, WM_QUIT, 0, 0);
		}
	}
}

void SceneMain::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta) {
	if (IsKeyDown(DIK_1)) {
		State = 1;
		LoadMap1();
	}
	if (IsKeyDown(DIK_2)) {
		State = 2;
		LoadMap2();
	}

	if (stopNinjaGaiden == false) {
		if (IsKeyDown(DIK_RIGHT)) {
			ninjaGaiden->MoveRight();
			ninjaGaiden->Go();
		}
		if (IsKeyDown(DIK_LEFT)) {
			ninjaGaiden->MoveLeft();
			ninjaGaiden->Go();
		}
		if (!IsKeyDown(DIK_LEFT) && !IsKeyDown(DIK_RIGHT) &&
			!(ninjaGaiden->Auto)) // ninjaGaiden->autu == 0
		{
			ninjaGaiden->Stop();
		}
		if (IsKeyDown(DIK_SPACE) && !IsKeyDown(DIK_DOWN)) {
			ninjaGaiden->Jump();
		}
		if (!IsKeyDown(DIK_SPACE) && IsKeyDown(DIK_DOWN)) {
			ninjaGaiden->Sit();
		}

		if (IsKeyDown(DIK_T)) {
			if (ninjaGaiden->getAttacking() == 0) {
				//ninjaGaiden->Attack(weapons.at(0));
				ninjaGaiden->Attack();

				//ninjaGaiden->PlaySoundChoose(18);
			}
		}
	}
}

void SceneMain::UpdateObject(Camera *cam, int t) {
	if (State != 0 && !isOpenTheGate) {
		cam->SetFolowPos(ninjaGaiden->getx(), ninjaGaiden->gety());
		if (PreUpStair)
			cam->SetVCam(ninjaGaiden->getTrend() * 0.13 * t,
				ninjaGaiden->GetVy()); // Xét khi mà va chạm cầu thang để
									   // chuẩn bị lên cầu thang
		else {
			cam->SetVCam(ninjaGaiden->getVx() * t, ninjaGaiden->GetVy());
		}
		cam->UpdateCamera();

		// Updated weapons of ninjaGaiden

		// Updated weaponsEnemy
		for (UINT i = 0; i < listObj.size(); i++)
		{
			switch (listObj[i]->GetType())
			{
			case eType::GROUND:
				break;
			
			default:
				listObj[i]->Update(t);
				break;
			}
			
		}

	}
	CheckCollision();
}


void SceneMain::CheckCollision() {
	CheckCollisionGround();
	CheckCollisionEnemy();
	CheckCollisionItem();
}

void SceneMain::CheckCollisionEnemy() {
	
	float CollisionTime, nx, ny;
	for (UINT indexEnemy = 0; indexEnemy < listEnemy.size(); indexEnemy++)
	{
		IsCollision = Collide(ninjaGaiden->GetBox(cam), listEnemy[indexEnemy]->GetBox(cam), CollisionTime, nx, ny);
		if (IsCollision !=0)
		{
			switch (listEnemy[indexEnemy]->GetType())
			{
			case eType::EAGLE:
				listEnemy[indexEnemy]->SetHealth(0);
				break;
			default:
				break;
			}
		}
		
	}

}
void SceneMain::CheckCollisionGround() {
	int IsCollision;
	float CollisionTime, nx, ny;
	for (UINT indexGround = 0; indexGround < listGround.size(); indexGround++)
	{
#pragma region Check Ground with Ninja
		IsCollision = Collide(ninjaGaiden->GetBox(cam), listGround[indexGround]->GetBox(cam), CollisionTime, nx, ny);
		if (IsCollision == 5)
		{
			float k = listGround[indexGround]->gety() + listGround[indexGround]->geth() / 2 + ninjaGaiden->getHeight() / 2 + 5;
			ninjaGaiden->StopFall(k);	
		}
#pragma endregion
#pragma region Check Ground with Enemy
		for (UINT indexEnemy = 0; indexEnemy < listEnemy.size(); indexEnemy++) {
			BaseObject* enemy = dynamic_cast<BaseObject*> (listEnemy[indexEnemy]);
			
			IsCollision = Collide(enemy->GetBox(cam), listGround[indexGround]->GetBox(cam), CollisionTime, nx, ny);
			float k = listGround[indexGround]->gety() + listGround[indexGround]->geth() / 2 + listEnemy[indexEnemy]->getHeight() / 2 + 5;
			if (IsCollision == 5)
			{
				listEnemy[indexEnemy]->Stop();
			}
		}
#pragma endregion

#pragma region Check Ground with Item
		for (UINT indexItem = 0; indexItem < listItem.size(); indexItem++)
		{

			IsCollision = Collide(listItem[indexItem]->GetBox(cam), listGround[indexGround]->GetBox(cam), CollisionTime, nx, ny);
			if (IsCollision == 5)
			{
				float k = listGround[indexGround]->gety() + listGround[indexGround]->geth() / 2 + listItem[indexItem]->getHeight() / 2 + 5;
				listItem[indexItem]->Stop();
			}
		}
#pragma region 
	}


}

void SceneMain::CheckCollisionItem() {

}

