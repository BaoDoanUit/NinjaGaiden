#pragma once
#include"BaseObject.h"
#define DOG_STOP_IMAGE 0
#define DOG_FALL_IMAGE 3

#define DOG_VX 0.43

#define DOG_GRAVITY 2
#define DOG_FALL 9
class Dog :public BaseObject
{
public:
	Dog(int x, int y, int h, int w);
	virtual void Fall();
	virtual void Go();
	virtual void Jump();
	virtual void StopFall(float y);
	virtual void Update(int t);
	void Draw(Camera * cam);
	int timeFall;
	~Dog();
};

