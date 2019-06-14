#include "Camera.h"
#include "Sprite.h"
#include "Sweet_AABB.h"
#include "Weapon.h"
#include "Global.h"
#include "TextureManager.h"
#pragma once


class BaseObject
{
protected:
	float x;			 //Vị trí obj
	float y;
	int w;
	int h;
	int borderLeft;
	int borderRight;
	bool IsGoing;		// Đang di chuyển = true; Đứng yên = false;
	bool IsAttacking;
	bool IsStopping;		
	bool IsJumping;
	bool IsSitting;
	bool IsFalling;
	int DefaultTrend;
	int Trend;		// Phương hướng, trái = -1, phải = 1;
	int PreAtk;
	int IsHurting;
	bool EndHurt; //  false bị thương, true kết thúc bị thương
	bool IsDie = 0; 
	int Health;
	int id;
	eType type;
	bool dropItem;

public:
	Texture *GTObject;
	Sprite *GSObject;
	float Vx;	// Vận tốc theo trục X
	float Vy;	// Vận tốc theo trục Y
	float ax;

	float dx;
	float dy;

	float GetVx();
	float GetVy();

	float		getx() { return this->x; }
	void		setx(float x1) { x = x1; }

	float		gety() { return this->y; }
	void		sety(float x1) { y = x1; }

	int			getw() { return this->w; }
	void		setw(int x1) { w = x1; }

	int			geth() { return this->h; }
	void		seth(int x1) { h = x1; }

	float		getVx() { return this->Vx; }
	void		setVX(int x1) { this->Vx = x1; }

	float		getVy() { return this->Vy; }
	void		setVy(int y1) { this->Vy = y1; }

	int			getIsHurrting() { return this->IsHurting; }
	int GetHealth();
	void SetHealth(int h);
	//danh cho 
	int getHeight() { return GTObject->FrameHeight; }
	int getWidth() { return GTObject->FrameWidth; }
	int getTrend() { return Trend; }
	void setTrend(int trend) { Trend = trend; }

	int			getIsDie() { return this->IsDie; }
	void		setIsDie(bool a) { IsDie = a; }
	bool			getAttacking() { return this->IsAttacking; }
	bool getIsJumping() { return IsJumping; };
	bool getIsFalling() { return IsFalling; };


	bool getIsGoing() { return IsGoing; };

	virtual void Update(int t);
	virtual void UpdateFollowNinja(int t, D3DXVECTOR2 * ryupos);
	virtual void Draw(Camera * cam);

	BaseObject();
	BaseObject(float x, float y, int w, int h);
	~BaseObject();
	virtual Box GetBox(Camera *camera);
	virtual void RenderBoundingBox(Camera* camera);
	virtual void StopFall(float y);
	virtual void Stop();
	virtual void Sit();
	virtual void StandUp();
	virtual void Fall();
	virtual void Jump();
	virtual void Go();
	virtual void MoveLeft();
	virtual void MoveRight();
	///////////////////
	virtual void Attack(Weapon * weapon);

	virtual int CreateWeapon();
	int GetHurt();
	void SetHurt(int i = 30);
	int water;
	void BaseObject::SetAnimation(float Vx, float Vy, int Frame);
	virtual void GetSMPositionForBoss(float x, float y, int Trend);
	void SetTrend(int d);
	int GetTrend();
	void SetId(int ID);
	int GetId();
	eType GetType();
	bool getDropItem();
	void setDropItem(bool dropItem);
	virtual void setPositionNinja(D3DXVECTOR2* pos);
	void GetBoundingBox(float & left, float & top, float & right, float & bottom);
};
