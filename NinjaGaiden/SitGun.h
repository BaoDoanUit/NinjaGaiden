#pragma once
#include "BaseObject.h"
#define ENEMY_GRAVITY 1
class SitGun : public BaseObject
{
public:
	SitGun(int x1, int y1, int w1, int h1);
	virtual void Update(int t);
	virtual void Draw(Camera * cam);
	virtual void StopFall(float y);
	virtual void Go();
	~SitGun();
};

