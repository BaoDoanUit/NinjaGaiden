#pragma once


#define SPIRITUAL2_TIMEDISPLAYMAX 3000
#define SPIRITUAL2_GRAVITY 0.25f




#include "Item.h"
class Spiritual2 : public Item
{
public:
	Spiritual2(float X, float Y);

	//virtual void Draw(Camera * camera);

	virtual ~Spiritual2();
};
