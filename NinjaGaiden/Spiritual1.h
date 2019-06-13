#pragma once


#define SPIRITUAL1_TIMEDISPLAYMAX 3000
#define SPIRITUAL1_GRAVITY 0.25f




#include "Item.h"
class Spiritual1 : public Item
{
public:
	Spiritual1(float X, float Y);

//	virtual void Draw(Camera * camera);

	virtual ~Spiritual1();
};

