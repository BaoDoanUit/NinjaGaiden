#pragma once
#include "BaseObject.h"
#define SPEED_X 0.2f
#define SPEED_Y 0.1f
#define ACCELERATION_X 0.01f
#define MAX_HEIGHT 250.0f
class Eagle :public BaseObject
{
private:
	float yBackup; // vị trí của y ban dầu
	int status;
	float _speedX;
	D3DXVECTOR2  *ninja;
public:
	Eagle(int x1, int y1, int w1, int h1);
	virtual void Update(int t);
	void setPositionNinja(D3DXVECTOR2  *ninja);
	void SetActive();
	~Eagle();
};

