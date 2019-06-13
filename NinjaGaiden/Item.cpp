#include "Item.h"



Item::Item()
{
	TimeDisplayed = 0;
	TimeWaitMax = 0;
	TimeDisplayMax = 0;
	TimeWaited = 0;
	isFinish = 0;
}


void Item::Update(int t)
{
	y -= Vy * t;
	if (y <= 80)
		Vy = 0;
}

Item::~Item()
{
}


