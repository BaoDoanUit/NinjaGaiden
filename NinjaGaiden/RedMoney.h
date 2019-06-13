#pragma once


#define REDMONEY_TIMEDISPLAYMAX 3000
#define REDMONEY_GRAVITY 0.25f




#include "Item.h"
class RedMoney : public Item
{
public:
	RedMoney(float X, float Y);

	//virtual void Draw(Camera * camera);

	virtual ~RedMoney();
};
