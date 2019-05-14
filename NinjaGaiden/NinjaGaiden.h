﻿#include "BaseObject.h"
#include "Sweet_AABB.h"
#pragma once

#define NINJAGAIDEN_TREND 1
#define NINJAGAIDEN_FRAME 70
#define NINJAGAIDEN_STOP_IMAGE 0
#define NINJAGAIDEN_SIT_IMAGE 4
#define NINJAGAIDEN_ATK_IMAGE 5
#define NINJAGAIDEN_SITATK_IMAGE 15
#define NINJAGAIDEN_HURT_IMAGE 8

#define NINJAGAIDEN_VX_STAIR 0.13
#define NINJAGAIDEN_VY_STAIR 0.13
#define NINJAGAIDEN_VJUMP 12
#define NINJAGAIDEN_GRAVITY 1
#define NINJAGAIDEN_FALL 180
/////////////////////
//Thay thế số 8 trong hàm StopFall( y = y -8)
#define NINJAGAIDEN_Y_STOP_FALL 8
#define NINJAGAIDEN_Y_SIT 15
#define NINJAGAIDEN_VX_GO 0.33

class NinjaGaiden : public BaseObject
{
private:
	float NinjaGaiden_vx;
	int HTrend;
	Texture *GTObject2;
	Sprite *GSObject2;
	bool isNinjaGaidenDie = false;
	int trend = -1;
	//float Vx, Vy;
public:
	//Stair
	int IsOnStair;
	int Auto;
	int stairTrend;
	int xStairUp;
	int yStairUp;
	int xStairDown;
	int yStairDown;
	int isUpStair;
	int isDownStair;
	void UpStair();
	int GetOnStair();
	void OutStair();
	void DownStair();
	//stair
	//Tiền updated
	float Vx_Hurt;
	int Prevent;
	int NinjaGaidenFall = 0;
	void setIndexNinjaGaiden();
	void Update(Camera *camera, int t);
	//void UpdateIntro(int t, int &delay);
	void Draw(Camera * cam);
	void Draw();
	NinjaGaiden() {}
	NinjaGaiden(float x, float y, int trend);
	~NinjaGaiden();
	virtual Box GetBox(Camera *camera);
	virtual void StopFall(float y);
	virtual void Stop();
	virtual void Sit();
	virtual void StandUp();
	virtual void Fall();
	virtual void Jump();
	virtual void Go();
	/////////////////(Tiền updated)
	// void Attack(Weapon * weapon);
	void Hurt(int HTrend);
	void setNinjaGaidenDie(bool isdie) { isNinjaGaidenDie = isdie; };
};