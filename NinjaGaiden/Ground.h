#pragma once
#include "Global.h"
#include "BaseObject.h"
#include "TextureManager.h"

class Ground : public BaseObject
{
public:
	Ground(int x, int y, int width, int height);
	~Ground();
};

