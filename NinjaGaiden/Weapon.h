#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Sprite.h"
#include "Camera.h"
#include "Sweet_AABB.h"
#include "TextureManager.h"
class Weapon
{
protected:
	float Vx;	// Vận tốc theo trục X
	float Vy;	// Vận tốc theo trục Y
	int Trend;		// Phương hướng, trái = -1, phải = 1;
	int IsFinish;
	eType TypeWeapon;
	int dx;

public:
	float x;	// Vị trí theo trục X
	float y;	// Vị trí theo trục Y#pragma once
	Weapon();
	~Weapon();							// Hàm hủy Weapon

	Texture *GTObject;
	Sprite *GSObject;

	int GetTrend();
	void SetTrend(int a);

	virtual void Create(float ninjaGaiden_x, float ninjaGaiden_y, int ninjaGaidenTrend);
	virtual void Update(Camera*camera, int t);
	virtual Box GetBox(Camera *camera);
	virtual void Draw(Camera *camera);
	virtual void SetXY(float x, float y);
	virtual int GetFinish();
	virtual int getcurentFrame();
	eType getType();
};

#endif
