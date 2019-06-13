#include "BaseObject.h"

BaseObject::BaseObject()
{

}
BaseObject::BaseObject(float x1, float y1, int w1, int h1)
{
	this->x = x1;
	this->y = y1;
	this->w = w1;
	this->h = h1;
}
BaseObject::~BaseObject()
{

}

void BaseObject::Draw(Camera * camera)
{
	D3DXVECTOR2 pos = camera->TransformObject(x, y);
	if (Trend == -1)
		GSObject->DrawFlipX(pos.x, pos.y);
	else
		GSObject->DrawFromCenter(pos.x, pos.y);

	//if (IS_DEBUG_RENDER_BBOX)
	RenderBoundingBox(camera);
}


void BaseObject::Update(int t)
{
	dx = Vx * t;
	dy = Vy * t;
	GSObject->Update(t);
}
void BaseObject::UpdateFollowNinja(int t, D3DXVECTOR2 * ryupos) {
	GSObject->Update(t);
}
void BaseObject::StopFall(float y)
{
	IsFalling = false;
}
Box BaseObject::GetBox(Camera *camera)
{
	D3DXVECTOR2 pos;
	switch (type)
	{
	case eType::GROUND:
		pos = camera->Transform(getx(), gety());
		return Box(pos.x, pos.y, getw(), geth(), 0, 0);
		break;
	default:
		pos = camera->Transform(x, y);
		return Box(pos.x, pos.y, GTObject->FrameWidth, GTObject->FrameHeight, Vx, -Vy);
	}
	
	
}

void BaseObject::MoveLeft()
{
	if (IsFalling || IsJumping) return;
	if (IsAttacking) return;
	Trend = -1;
}

void BaseObject::MoveRight()
{
	if (IsFalling || IsJumping) return;
	if (IsAttacking) return;
	Trend = 1;
}

void BaseObject::Stop()
{
	IsGoing = false;
	Vx = 0;
}

void BaseObject::Sit()
{
	IsSitting = true;
	IsFalling = false;
	IsJumping = false;
	IsGoing = false;
}

void BaseObject::StandUp()
{
	IsSitting = false;
	IsFalling = false;
	IsJumping = false;
	IsGoing = false;
}

void BaseObject::Fall()
{
	IsFalling = true;
	IsJumping = false;
	IsSitting = false;
	EndHurt = true;
}
void BaseObject::Jump()
{
	IsJumping = true;
	IsFalling = false;
	IsSitting = false;
}
void BaseObject::Go()
{
	IsSitting = false;
	IsFalling = false;
	IsJumping = false;
	IsGoing = true;
}

float BaseObject::GetVx()
{
	if (IsAttacking) return 0;
	if (IsGoing) return Vx;
	return 0;
}

float BaseObject::GetVy()
{
	if (IsAttacking) return 0;
	if (IsFalling|| IsJumping) return Vy;
	return 0;
}
//////////////////////////////////
//Tiền updated
//void BaseObject::Attack(Weapon *weapon)
//{
//	IsAttacking = 1;
//	if (weapon) weapon->Create(x, y, Trend);
//}
int BaseObject::GetHurt()
{
	if (IsHurting) return 1;
	return 0;
}

void BaseObject::SetAnimation(float Vx, float Vy, int Frame)
{
	this->Vx = Vx * Trend;
	this->Vy = Vy;
	this->GSObject->_timeAni = Frame;
}
void BaseObject::SetHurt(int i)
{
	IsHurting = i;
}
int BaseObject::CreateWeapon() {
	return 0;
}
void BaseObject::GetSMPositionForBoss(float x, float y, int Trend)
{
	
}

void BaseObject::Attack(Weapon *weapon)
{
	IsAttacking = true;
	//if (weapon) weapon->Create(x, y, Trend);
}

int BaseObject::GetHealth()
{
	return Health;
}

void BaseObject::SetHealth(int h)
{
	this->Health = h;
}

int BaseObject::GetTrend()
{
	return Trend;
}

void BaseObject::SetId(int ID)
{
	this->id = ID;
}
int BaseObject::GetId()
{
	return id;
}

eType BaseObject::GetType()
{
	return type;
}

bool BaseObject::getDropItem()
{
	return dropItem;
}

void BaseObject::setDropItem(bool dropItem)
{
	this->dropItem = dropItem;
}

void BaseObject::setPositionNinja(D3DXVECTOR2 * pos)
{
}

void BaseObject::SetTrend(int Trend)
{

	this->Trend = Trend;
}

void BaseObject::RenderBoundingBox(Camera* camera)
{
	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = (LONG)r - (LONG)l;
	rect.bottom = (LONG)b - (LONG)t;

	D3DXVECTOR2 pos = camera->TransformObject(l, t);
	GSObject->DrawRect(pos.x,pos.y, rect);	
}

void BaseObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{	
		left = x;
		top = y;
		right = left + getw();
		bottom = top + geth();
}