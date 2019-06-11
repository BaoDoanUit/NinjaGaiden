#pragma once
#include "BaseObject.h"
class ObjectHidden : public BaseObject
{
private:
	int width;
	int height;

public:
	ObjectHidden(float X, float Y, int W, int H);
	~ObjectHidden();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera * camera);

};

