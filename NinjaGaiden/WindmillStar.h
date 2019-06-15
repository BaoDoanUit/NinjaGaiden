#pragma once
#ifndef __WPWINDMILLSTAR_H__
#define __WPWINDMILLSTAR_H__


#include "Weapon.h" 
#define WPWINDMILLSTAR_GRAVITY 0.008f
#define DELTAX 200
#define DELTAY 100

class WindmillStar : public Weapon
{
private:
	static WindmillStar *Instance;
	//int xNinja, yNinja;
	float v = 0;
	float delta = 0;
	float index = 0;
	float flag = 0;
	float BackupX;
	float BackupY;
	int BackupTrend;
public:
	float yNinja, xNinja, xStart;
	bool isReturn;
	WindmillStar();
	virtual void Update(Camera *camera, int t);
	virtual void Create(float ninjaGaiden_x, float ninjaGaiden_y, int ninjaGaiden_trend);

};




#endif#pragma once

