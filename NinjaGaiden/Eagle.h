#pragma once
#include "BaseObject.h"
#define ENEMY_GRAVITY 1
#define DeltaY 20 // Biên giao động trục y
#define EAGLE_SPEED_X 0.1f 
#define EAGLE_SPEED_Y 0.05f
class Eagle :public BaseObject
{
private:
	float yBackup; // vị trí của y ban dầu
	int status;
public:
	Eagle(int x1, int y1, int w1, int h1);
	virtual void Update(int t);
	//virtual void Draw(Camera * cam);
	// virtual void StopFall(float y);
	// virtual void Fly();
	~Eagle();
};

