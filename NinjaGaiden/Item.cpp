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
}

Item::~Item()
{
}


void Item::StopFall(int k)
{
	
}