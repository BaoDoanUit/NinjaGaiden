#include "NinjaGaiden.h"


NinjaGaiden::NinjaGaiden(float x1, float y1, int trend)
{
	x = x1;
	y = y1;
	Trend = trend;
	Vx = NINJAGAIDEN_VX_GO;
	NinjaGaiden_vx = NINJAGAIDEN_VX_GO;
	GTObject = TextureManager::GetInstance()->GetTexture(eType::NINJAGAIDEN);
	GSObject = new Sprite(GTObject, NINJAGAIDEN_FRAME);
	GTObject2 = TextureManager::GetInstance()->GetTexture(eType::NINJAGAIDEN_DEADTH);
	GSObject2 = new Sprite(GTObject2, NINJAGAIDEN_FRAME);
	EndHurt = true;
	//IsFalling = true;
	Blood = 10;
}

NinjaGaiden::~NinjaGaiden()
{

}

void NinjaGaiden::Draw() {
	GSObject->DrawFromCenter(x, y);
}
void NinjaGaiden::Draw(Camera * cam)
{
	D3DXVECTOR2 pos = cam->Transform(x - 15, y + GTObject->FrameHeight / 2);
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
	if (Trend == 1)
	{
		if (isNinjaGaidenDie)GSObject2->DrawFromCenter(pos.x, pos.y);
		else GSObject->DrawFromCenter(pos.x, pos.y);
	}
	else {
		if (isNinjaGaidenDie)GSObject2->DrawFlipX(pos.x, pos.y);
		else GSObject->DrawFlipX(pos.x, pos.y);
	}
	//RenderBoundingBox(cam);
}
///////////////////////////
//Thêm vào hàm khi simon di chuyển thì đổi frame

void NinjaGaiden::Update(Camera *camera, int t)
{
	if (IsClimbing) {

	}
	if (IsAttacking) {
		GSObject->Update(t);
		if (IsSitting)					//Tấn công khi đang ngồi
		{
			if (GSObject->_index > NINJAGAIDEN_END_SIT_ATK_IMAGE)
			{
				IsAttacking = 0;
				this->Sit();
			}
		}
		else if (IsJumping) //Tấn công khi đang bay
		{
			Vx *= IsGoing;
			x += Vx * t;
			y += Vy;
			Vy = Vy - NINJAGAIDEN_GRAVITY;
			if (GSObject->_index > NINJAGAIDEN_END_ATK_IMAGE)
			{
				IsAttacking = 0;
				this->Fall();
			}
		}
		else
			if (GSObject->_index > NINJAGAIDEN_END_ATK_IMAGE)
			{
				GSObject->SelectIndex(NINJAGAIDEN_STOP_IMAGE);
				IsAttacking = 0;
			}
	}
	else {
		if (IsJumping)
		{
			if (EndHurt) Vx *= IsGoing;
			else Vx = Vx_Hurt*HTrend*(Prevent == 0);
			y += Vy;
			x += Vx * t;
			Vy = Vy - NINJAGAIDEN_GRAVITY;
			GSObject->_end = NINJAGAIDEN_END_JUMP;	
			GSObject->Update(t);
			if (!EndHurt) GSObject->SelectIndex(NINJAGAIDEN_HURT_IMAGE);
			if (Vy == 0)
			{
				this->Fall();
			}
		}
		else if (IsFalling)
		{
			if (EndHurt) Vx *= IsGoing; 
			else Vx = Vx_Hurt*HTrend*(Prevent == 0);
			x += Vx * t;
			y += Vy;
			Vy = Vy - NINJAGAIDEN_GRAVITY;
		}
		else if (IsGoing)
		{
			x += Vx * t;
			GSObject->_end = NINJAGAIDEN_END_GO;
			GSObject->Update(t);			
		}
		else if (IsSitting)
		{
			GSObject->SelectIndex(NINJAGAIDEN_SIT_IMAGE);
		}
		else {
			GSObject->SelectIndex(NINJAGAIDEN_STOP_IMAGE);//rơi tự do khi va chạm với gạch thì đổi index frame
		}
	}


	//Khi ninja ra khỏi đầu cam
	if (x - 15 < camera->viewport.x) {
		x = camera->viewport.x + 16;
	}
	//Khi ninja ra khỏi cuối cam
	if (x + 15 > camera->viewport.x + G_ScreenWidth) {
		x = camera->viewport.x + G_ScreenWidth - 15;
	}
}


void NinjaGaiden::setIndexNinjaGaiden() {
	GSObject->SelectIndex(1);
}

Box NinjaGaiden::GetBox(Camera *camera)
{ 
	D3DXVECTOR2 pos = camera->Transform(x - 15, y + GTObject->FrameHeight / 2);
	return Box(pos.x, pos.y, GTObject->FrameWidth - 28, GTObject->FrameHeight, Vx, -Vy);
}

void NinjaGaiden::StopFall(float y) {
	if (IsAttacking == 1)return;
	IsAttacking = false;
	IsFalling = false;
	if (!IsSitting) {
		this->y = y - NINJAGAIDEN_Y_STOP_FALL;//Thay y = y - 8
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
		if (!IsSitting) y = y - NINJAGAIDEN_Y_SIT;
		GSObject->SelectIndex(NINJAGAIDEN_SIT_IMAGE);
		BaseObject::Sit();
	}
}

void NinjaGaiden::StandUp()
{
	if (IsSitting) y = y + NINJAGAIDEN_Y_SIT;
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
			GSObject->SelectIndex(NINJAGAIDEN_START_JUMP);
			if (EndHurt == 0)
			{
				GSObject->SelectIndex(NINJAGAIDEN_HURT_IMAGE);
				Vx = Vx*HTrend;
			}
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
			GSObject->SelectIndex(NINJAGAIDEN_STOP_IMAGE);		
			BaseObject::Fall();
		}
	}
}

void NinjaGaiden::Go()
{
	if (IsJumping|| IsFalling) return;
	if (!IsAttacking)
	{
		if (IsSitting) this->StandUp();
		this->Vx = NinjaGaiden_vx*Trend;
		GSObject->SelectIndex(NINJAGAIDEN_START_GO);
		BaseObject::Go();
		Prevent = 0;
		return;
	}
}

void NinjaGaiden::Stop()
{
	if (IsClimbing && !IsAttacking)
	{
		BaseObject::Stop();
		return;
	}
	if (!IsAttacking)
	{
		if (IsSitting) {
			this->StandUp();
		}
		BaseObject::Stop();
		return;
	}
}

void NinjaGaiden::Hurt(int HTrend)
{
	if (IsHurting == 0)
	{
		this->HTrend = HTrend > 0 ? 1 : -1;
		IsHurting = 30;
		EndHurt = false;
		NinjaGaidenFall = 0;
		Vx_Hurt = NinjaGaiden_vx;
		if (!IsClimbing)
			this->Jump();
	}
}

D3DXVECTOR2 * NinjaGaiden::getPos()
{
	return new D3DXVECTOR2(this->x, this->y);;
}

void NinjaGaiden::Attack(Weapon* weapon) {
	if (IsAttacking) return;

	if (IsFalling) return;

	if (IsSitting)
		GSObject->SelectIndex(NINJAGAIDEN_START_SIT_ATK_IMAGE);
	else
		GSObject->SelectIndex(NINJAGAIDEN_START_ATK_IMAGE);
	BaseObject::Attack(weapon);

}


//stair

