#pragma once
#include "BaseObject.h"
#define ENEMY_GRAVITY 1
class Enemy1 :public BaseObject
{
public:
	Enemy1(int x1, int y1, int w1, int h1, int borderLeft, int borderRight);
	virtual Box GetBox(Camera *camera);
	virtual void Update(int t);
	virtual void Draw(Camera * cam);
	virtual void StopFall(float y);
	virtual void Go();
	virtual void Attack(Weapon* weapon);
	~Enemy1();
};

