#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Sprite.h"
#include "Camera.h"
#include "Sweet_AABB.h"

class Weapon
{
protected:
	float Vx;	// Vận tốc theo trục X
	float Vy;	// Vận tốc theo trục Y
	int Trend;		// Phương hướng, trái = -1, phải = 1;
	int IsFinish;
	int TypeWeapon;

public:
	float x;	// Vị trí theo trục X
	float y;	// Vị trí theo trục Y#pragma once
	Weapon();
	~Weapon();							// Hàm hủy Weapon

	Texture *GTObject;
	Sprite *GSObject;
};

#endif
