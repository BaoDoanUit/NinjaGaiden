
#include "SceneMain.h"



SceneMain::SceneMain(int nCmdShow) : Game(nCmdShow)
{

}


SceneMain::~SceneMain(void)
{
}
void SceneMain::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	//sound->PlayMusicChoose(soundNow);
	minT++;
	if (minT > 30)
	{
		//score->Calculator1Sec();
		minT = -1;
	}
	/*
	if (eatOrb) {// xu ly an trứng simon delay 1 khoan thoi gian tinh diem chuan bi chuyen sang man khac
		minC++;
		if (minC > 60) {
			minS++;
			if (minS > 0) {
				score->CalculatorOrb();
				minS = -1;
				simon->Stop();
				stopsimon = true;
			}
			minC = 61;
		}
	}
	if (simondied) {// simon chết nằm 1 lát sau reset lại màn khác
		stopsimon = true;
		simon->Stop();
		minD++;
		if (minD > 100) {
			countSimondied = true;// biến reset simon màn khác
			minD = 0;
		}
	}*/
	d3ddv->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
	G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	//maps->DrawMap(cam, State);
	if (State == -1) {
		//RenderMenu(t);
	}
	else if (State == 0) {
		//RenderIntro(t);
	}
	else {
		//Simon va chạm với cục đung đưa cho nó auto
		
		//if (simon->getisOnbrick9() && simon->getIsGoing() == 0)
		//	simon->AutoGoOnBrick9(); //^^^
		//if (EndingScene == 1 || stepOpenTheGate == 2)//Kiểm tra khi va chạm cổng màn 1 thì tự động di chuyển vào cổng không cần nhấn nút
		//	simon->Go();
		//Kiểm tra khi simon va chạm item là IWhip thì vẽ màu sắc mới cho simon
		if (CollectMorningStar == 0)
			ninjaGaiden->Update(cam, t);
		else
		{
			CollectMorningStar++;
			if (CollectMorningStar == 21) CollectMorningStar = 0;
		}
		
		RenderStage(d3ddv, State);
		UpdateObject(cam, t);
	}
	G_SpriteHandler->End();
}


void SceneMain::RenderStage(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	ninjaGaiden->Draw(cam);
	G_SpriteHandler->End();
}

void SceneMain::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	//LoadOther();
	switch (State)
	{
	case -1:
		//maps = new Map(State);
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
	AutoFit = 0; //Sử dụng biến này khi viewport.y của màn 2 khác với width của màn hình nên tọa độ item cộng thêm AutoFit
	ninjaGaiden = new NinjaGaiden(G_ScreenWidth, 76, 1);
	ninjaGaiden->setx(20);
	ninjaGaiden->sety(100);
	cam = new Camera(ninjaGaiden->getx(), 1);
	cam->SetSizeMap(0, 1536);
	ninjaGaiden->Go();
}

void SceneMain::LoadMap2() {
}

void SceneMain::LoadMap3() {

}
void SceneMain::OnKeyDown(int KeyCode)
{
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
				//maps = new Map(State);
				ninjaGaiden = new NinjaGaiden(G_ScreenWidth - 10, 370, -1);
			}
			else PostMessage(G_hWnd, WM_QUIT, 0, 0);
		}
	}
}


void SceneMain::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	if (IsKeyDown(DIK_1)) { State = 1; LoadMap1(); }
	if (IsKeyDown(DIK_2)) { State = 2; LoadMap2(); }

	if (stopNinjaGaiden == false)
	{	
		if (IsKeyDown(DIK_RIGHT))
		{
			ninjaGaiden->MoveRight();
			ninjaGaiden->Go();
		}
		if (IsKeyDown(DIK_LEFT))
		{
			ninjaGaiden->MoveLeft();
			ninjaGaiden->Go();
		}
		if (!IsKeyDown(DIK_LEFT) && !IsKeyDown(DIK_RIGHT) && !(ninjaGaiden->Auto)) // simon->autu == 0
		{
			ninjaGaiden->Stop();
		}
		if (IsKeyDown(DIK_SPACE) && !IsKeyDown(DIK_DOWN)) {
			ninjaGaiden->Jump();
		}
		if (!IsKeyDown(DIK_SPACE) && IsKeyDown(DIK_DOWN)) {
			ninjaGaiden->Sit();
		}

		if (IsKeyDown(DIK_UP)) {
			if (PreUpStair == 0) {
				ninjaGaiden->isUpStair = 1;
			}
		}
		else {
			ninjaGaiden->isUpStair = 0;
		}
		if (IsKeyDown(DIK_DOWN)) {
			if (PreDownStair == 0) {
				ninjaGaiden->isDownStair = 1;
			}
		}
		else {
			ninjaGaiden->isDownStair = 0;
		}
	}



}


void SceneMain::UpdateObject(Camera * cam, int t) {

	if (State != 0 && !isOpenTheGate) {
		cam->SetFolowPos(ninjaGaiden->getx(), ninjaGaiden->gety());
		if (PreUpStair)
			cam->SetVCam(ninjaGaiden->getTrend()*0.13* t, ninjaGaiden->GetVy());//Xét khi mà va chạm cầu thang để chuẩn bị lên cầu thang
		else {
			cam->SetVCam(ninjaGaiden->getVx() * t, ninjaGaiden->GetVy());
		}	
		cam->UpdateCamera();
	
		//Updated weapons of ninjaGaiden

		//Updated weaponsEnemy
	}

}
