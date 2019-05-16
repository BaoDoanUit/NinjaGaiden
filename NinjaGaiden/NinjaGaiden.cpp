#include "NinjaGaiden.h"

NinjaGaiden::NinjaGaiden(float x1, float y1, int trend)
{
	x = x1;
	y = y1;
	Trend = trend;
	Vx = NINJAGAIDEN_VX_GO;
	NinjaGaiden_vx = NINJAGAIDEN_VX_GO;
	GTObject = new Texture("./Resources/ninjaGaiden.png", 8, 3, 24);
	GSObject = new Sprite(GTObject, NINJAGAIDEN_FRAME);
	GTObject2 = new Texture("./Resources/simondeath.png", 1, 1, 1);
	GSObject2 = new Sprite(GTObject2, 10);
	EndHurt = 1;
}

NinjaGaiden::~NinjaGaiden()
{

}

void NinjaGaiden::Draw() {
	GSObject->DrawFromCenter(x, y);
}
void NinjaGaiden::Draw(Camera * cam)
{
	D3DXVECTOR2 pos = cam->Transform(x, y);
	if (IsHurting)
	{
		IsHurting--;
		if (!IsDie)
		{
			IsDie = true;
			return;
		}
		else
		{
			IsDie = false;
		}
	}
	else EndHurt = 1;
	if (Trend == -1)
	{
		if (isNinjaGaidenDie == true)GSObject2->DrawFromCenter(pos.x, pos.y);
		else GSObject->DrawFromCenter(pos.x, pos.y);
	}
	else {
		if (isNinjaGaidenDie == true)GSObject2->DrawFlipX(pos.x, pos.y);
		else GSObject->DrawFlipX(pos.x, pos.y);
	}
}
///////////////////////////
//Thêm vào hàm khi ninja di chuyển thì đổi frame

void NinjaGaiden::Update(Camera *camera, int t)
{
	if (IsOnStair == 1)
	{
		if (IsAttacking == 1)
		{
			GSObject->Update(t);
			if (Trend*stairTrend == -1)
			{
				if (GSObject->_index == 0)
				{
					GSObject->SelectIndex(12);
					IsAttacking = 0;
				}
			}
			else
				if (GSObject->_index == 21)
				{
					GSObject->SelectIndex(10);
					IsAttacking = 0;
				}
		}
		else
			if (IsGoing == 1)
			{
				x += Vx * t;
				y += Vy * t;
				GSObject->Update(t);

				if (Trend*stairTrend == -1)
				{
					GSObject->_index = GSObject->_index % 2 + 12;
				}
				else
				{
					GSObject->_index = GSObject->_index % 2 + 10;
				}

				if ((Trend*stairTrend == -1))
				{
					if (y - yStairUp >= 26 && Auto == 1) // leo lên 1 bậc thì dừng.
					{
						this->Stop();
						Auto = 0;
					}
				}
				else
				{
					if (yStairDown - y >= 0 && Auto == 1)
					{
						this->Stop();
						Auto = 0;
					}
				}
			}
			else
			{
				if (Trend*stairTrend == -1) GSObject->SelectIndex(12);
				else GSObject->SelectIndex(10);
			}
		return;
	}
	if (IsAttacking == 1) {
		GSObject->Update(t);
		if (IsSitting == 1)					//Tấn công khi đang ngồi
		{
			if (GSObject->_index > 17)
			{
				IsAttacking = 0;
				this->Sit();
			}
		}
		else if (IsJumping == 1) //Tấn công khi đang bay
		{
			Vx *= IsGoing;
			x += Vx * t;
			y += Vy;
			Vy = Vy - NINJAGAIDEN_GRAVITY;
			if (GSObject->_index > 7)
			{
				IsAttacking = 0;
				this->Fall();
			}
		}
		else
			if (GSObject->_index > 7)
			{
				GSObject->SelectIndex(NINJAGAIDEN_STOP_IMAGE);
				IsAttacking = 0;
			}
	}
	else {
		if (IsJumping == 1)
		{
			if (EndHurt) Vx *= IsGoing; else Vx = Vx_Hurt*HTrend*(Prevent == 0);
			y += Vy;
			x += Vx * t;
			Vy = Vy - NINJAGAIDEN_GRAVITY;
			GSObject->SelectIndex(NINJAGAIDEN_SIT_IMAGE);
			if (!EndHurt) GSObject->SelectIndex(NINJAGAIDEN_HURT_IMAGE);
			if (Vy == 0)
			{
				this->Fall();
			}
		}
		else if (IsFalling == 1)
		{
			if (EndHurt) Vx *= IsGoing; else Vx = Vx_Hurt*HTrend*(Prevent == 0);
			x += Vx * t;
			y += Vy;
			Vy = Vy - NINJAGAIDEN_GRAVITY;
			GSObject->SelectIndex(NINJAGAIDEN_STOP_IMAGE);
		}
		else if (IsGoing == 1)
		{
			x += Vx * t;
			GSObject->_end = 3;
			GSObject->Update(t);
			if (IsFalling == 0 && IsJumping == 0) GSObject->_index = GSObject->_index % 4;
		}
		else if (IsSitting == 1)
		{
			GSObject->SelectIndex(NINJAGAIDEN_SIT_IMAGE);
		}
		else {
			GSObject->SelectIndex(NINJAGAIDEN_STOP_IMAGE);//rơi tự do khi va chạm với gạch thì đổi index frame
		}
	}


	//Khi simon ra khỏi đầu cam
	if (x - 15 < camera->viewport.x) {
		x = camera->viewport.x + 16;
	}
	//Khi simon ra khỏi cuối cam
	if (x + 15 > camera->viewport.x + G_ScreenWidth) {
		x = camera->viewport.x + G_ScreenWidth - 15;
	}
}


void NinjaGaiden::setIndexNinjaGaiden() {
	GSObject->SelectIndex(0);
}

Box NinjaGaiden::GetBox(Camera *camera)
{
	D3DXVECTOR2 pos = camera->Transform(x - 15, y + GTObject->FrameHeight / 2);
	return Box(pos.x, pos.y, GTObject->FrameWidth - 28, GTObject->FrameHeight, Vx, -Vy);// xem lại
}

void NinjaGaiden::StopFall(float y) {
	if (IsAttacking == 1)return;
	IsAttacking = 0;
	IsFalling = 0;
	if (IsSitting == 0) {
		this->y = y - NINJAGAIDEN_Y_STOP_FALL;//Thay y = y - 8 bằng SIMON_STOP_FALL
	}
	if (NinjaGaidenFall) this->Sit();
	else
		if (IsGoing == 1) this->Go();
		else this->StandUp();
		Vy = 0;
}
void NinjaGaiden::Sit()
{
	if (IsJumping == 1 || IsFalling == 1) return;
	if (IsAttacking == 0)
	{
		GSObject->SelectIndex(NINJAGAIDEN_SIT_IMAGE);
		if (IsSitting == 0) y = y - NINJAGAIDEN_Y_SIT;
		GSObject->SelectIndex(NINJAGAIDEN_SIT_IMAGE);
		BaseObject::Sit();
	}
}

void NinjaGaiden::StandUp()
{
	if (IsSitting == 1) y = y + NINJAGAIDEN_Y_SIT;
	GSObject->SelectIndex(NINJAGAIDEN_STOP_IMAGE);
	BaseObject::StandUp();
}
void NinjaGaiden::Jump()
{
	if (IsAttacking == 0 && IsJumping == 0 && IsFalling == 0)
	{
		if (IsJumping == 0)
		{
			Vy = NINJAGAIDEN_VJUMP;
			GSObject->SelectIndex(NINJAGAIDEN_SIT_IMAGE);
			/*if (EndHurt == 0)
			{
			GSObject->SelectIndex(SIMON_HURT_IMAGE);
			Vx = Vx*HTrend;
			}*/
			BaseObject::Jump();
		}
	}
}
void NinjaGaiden::Fall()
{
	if (IsAttacking == 0 && IsJumping == 1 && IsFalling == 0)
	{
		if (IsFalling == 0)
		{
			Vy = -NINJAGAIDEN_VJUMP;
			//waterDie++;
			GSObject->SelectIndex(NINJAGAIDEN_STOP_IMAGE);
			BaseObject::Fall();
		}
	}
}

void NinjaGaiden::Go()
{
	if (IsJumping == 1 || IsFalling == 1) return;
	if (IsOnStair == 1 && IsAttacking == 0)
	{
		Vx = NINJAGAIDEN_VX_STAIR*Trend;
		Vy = -NINJAGAIDEN_VY_STAIR*Trend*stairTrend;
		BaseObject::Go();
		return;
	}
	if (IsAttacking == 0)
	{
		//if (IsSitting == 1) this->StandUp();
		this->Vx = NinjaGaiden_vx*Trend;
		BaseObject::Go();
		//Prevent = 0;
	}
}

void NinjaGaiden::Stop()
{
	if (IsOnStair == 1 && IsAttacking == 0)
	{
	BaseObject::Stop();
	return;
	}
	if (IsAttacking == 0)
	{
		if (IsSitting == 1) {
			this->StandUp();
		}
		BaseObject::Stop();
		return;
	}
}
// TODO: NinjaGaiden Attack
/*

*/


void NinjaGaiden::Hurt(int HTrend)
{
	if (IsHurting == 0)
	{
		this->HTrend = HTrend > 0 ? 1 : -1;
		IsHurting = 30;
		EndHurt = 0;
		NinjaGaidenFall = 0;
		Vx_Hurt = NinjaGaiden_vx;
		if (IsOnStair == 0)
			this->Jump();
	}
}

void NinjaGaiden::UpStair()
{
	IsSitting = 0;
	IsJumping = 0;
	IsFalling = 0;
	IsOnStair = 1;// Vị trí trên cầu thang
}

void NinjaGaiden::DownStair()
{
	Trend = stairTrend;
	IsSitting = 0;
	IsJumping = 0;
	IsFalling = 0;
	IsOnStair = 1;
}
void NinjaGaiden::OutStair()
{
	Vy = 0;
	Vx = NinjaGaiden_vx;
	IsOnStair = 0;
	/*if (IsGoing == 1)
	this->Go();
	else this->StandUp();*/
	this->GSObject->_timeAni = 70;
}
int NinjaGaiden::GetOnStair() {
	return IsOnStair;
}
//stair

