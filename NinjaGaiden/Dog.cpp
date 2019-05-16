#include "Dog.h"



Dog::~Dog()
{
}

Dog::Dog(int x1, int y1, int h1, int w1)
{
	x = x1;
	y = y1;
	h = h1;
	w = w1;
	GTObject = new Texture("./Resources/enemy/dog.png", 2, 1, 2);
	GSObject = new Sprite(GTObject, 120);
	Vx = Vy = 0;
	Trend = -1;
	timeFall = 0;
}

void Dog::Fall()
{
	if (IsJumping == 1 && IsFalling == 0)
	{
		if (IsFalling == 0)
		{
			Vy = -DOG_FALL;
			GSObject->SelectIndex(DOG_FALL_IMAGE);
			BaseObject::Fall();
		}
	}
}

void Dog::Go()
{
	BaseObject::Go();
	Vx = DOG_VX * Trend;
}

void Dog::Jump()
{
	if (IsJumping == 0 && IsFalling == 0)
	{
		if (IsJumping == 0)
		{
			Vy = DOG_FALL;
			BaseObject::Jump();
		}
	}
}

void Dog::Update(int t)
{
	if (IsJumping == 1)
	{
		Vx *= IsGoing;
		y += Vy;
		x += Vx * t;
		Vy = Vy - DOG_GRAVITY;
		GSObject->SelectIndex(DOG_FALL_IMAGE);
		if (Vy <= 0)
		{
			this->Fall();
		}
	}
	else
		if (IsFalling == 1)
		{
			Vx *= IsGoing;
			x += Vx * t;
			y += Vy;
			Vy = Vy - DOG_GRAVITY;
			GSObject->SelectIndex(DOG_FALL_IMAGE);
		}
		else
			if (IsGoing == 1)
			{
				x += Vx * t;
				timeFall += Vx * t;
				GSObject->Update(t);
				if (GSObject->_index == 0) GSObject->_index++;
			}
			else GSObject->SelectIndex(DOG_STOP_IMAGE);
}

void Dog::Draw(Camera * cam)
{
	D3DXVECTOR2 pos = cam->Transform(x, y);
	if (Trend == -1)
		GSObject->DrawFromCenter(pos.x, pos.y);
	else GSObject->DrawFlipX(pos.x, pos.y);
}
