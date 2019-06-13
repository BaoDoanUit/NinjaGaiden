#pragma once


#define BLUEMONEY_TIMEDISPLAYMAX 3000
#define BLUEMONEY_GRAVITY 0.25f




#include "Item.h"
class BlueMoney : public Item
{
public:
	BlueMoney(float X, float Y);

	//virtual void Draw(Camera * camera);

	virtual ~BlueMoney();
};

