#include "Sweet_AABB.h"
#include <cmath>
#include <limits>
#include <algorithm>

// returns true if the boxes are colliding (velocities are not used)
bool AABBCheck(Box b1, Box b2)
{
	return !(b1.x + b1.w < b2.x || b1.x > b2.x + b2.w || b1.y + b1.h < b2.y || b1.y > b2.y + b2.h);
}
// returns true if the boxes are colliding (velocities are not used)
// moveX and moveY will return the movement the b1 must move to avoid the collision
bool AABB(Box b1, Box b2, float& moveX, float& moveY)
{
	moveX = moveY = 0;

	float l = b2.x - (b1.x + b1.w);
	float r = (b2.x + b2.w) - b1.x;
	float t = b2.y - (b1.y + b1.h);
	float b = (b2.y + b2.h) - b1.y;

	// check that there was a collision
	if (l > 0 || r < 0 || t > 0 || b < 0) return false;

	// find the offset of both sides
	moveX = abs(l) < r ? l : r;
	moveY = abs(t) < b ? t : b;

	// only use whichever offset is the smallest
	if (abs(moveX) < abs(moveY))
		moveY = 0;
	else
		moveX = 0;

	return true;
}


// returns a box the spans both a current box and the destination box
Box GetSweptBroadphaseBox(Box b)
{
	float x = b.vx > 0 ? b.x : b.x + b.vx;
	float y = b.vy > 0 ? b.y : b.y + b.vy;
	float w = b.w + abs(b.vx);
	float h = b.h + abs(b.vy);
	return Box(x, y, w, h, 0, 0);
}

// performs collision detection on moving box b1 and static box b2
// returns the time that the collision occured (where 0 is the start of the movement and 1 is the destination)
// getting the new position can be retrieved by box.x = box.x + box.vx * collisiontime
// normalx and normaly return the normal of the collided surface (this can be used to do a response)
float SweptAABB(Box b1, Box b2, float& normalx, float& normaly)
{
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// find the distance between the objects on the near and far sides for both x and y
	if (b1.vx > 0)
	{
		xInvEntry = b2.x - (b1.x + b1.w);
		xInvExit = (b2.x + b2.w) - b1.x;
	}
	else
	{
		xInvEntry = (b2.x + b2.w) - b1.x;
		xInvExit = b2.x - (b1.x + b1.w);
	}

	if (b1.vy > 0)
	{
		yInvEntry = b2.y - (b1.y + b1.h);
		yInvExit = (b2.y + b2.h) - b1.y;
	}
	else
	{
		yInvEntry = (b2.y + b2.h) - b1.y;
		yInvExit = b2.y - (b1.y + b1.h);
	}

	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
	float xEntry, yEntry;
	float xExit, yExit;

	if (b1.vx == 0)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / b1.vx;
		xExit = xInvExit / b1.vx;
	}

	if (b1.vy == 0)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / b1.vy;
		yExit = yInvExit / b1.vy;
	}

	// find the earliest/latest times of collision
	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	// if there was no collision
	if (entryTime > exitTime || xEntry < 0 && yEntry < 0 || xEntry > 1 || yEntry > 1)
	{
		normalx = 0;
		normaly = 0;
		return 1;
	}
	else // if there was a collision
	{
		// calculate normal of collided surface
		if (xEntry > yEntry)
		{
			if (xInvEntry < 0)
			{
				normalx = 1;
				normaly = 0;
			}
			else
			{
				normalx = -1;
				normaly = 0;
			}
		}
		else
		{
			if (yInvEntry < 0)
			{
				normalx = 0;
				normaly = 1;
			}
			else
			{
				normalx = 0;
				normaly = -1;
			}
		}

		// return the time of collision
		return entryTime;
	}
}


int Collide(Box &box, Box &block, float &collisiontime, float &x, float &y)
{
	// box is the moving box
	// block is the static box
	if (AABBCheck(GetSweptBroadphaseBox(box), block))
	{
		float normalx, normaly;
		collisiontime = SweptAABB(box, block, normalx, normaly);
		if (collisiontime < 1)
		{
			x = normalx;
			y = normaly;
			if (normaly == 1) return 3;
			if (normalx == -1) return 2;
			if (normalx == 1) return 1;
			if (normaly == -1) return 4;// 4 hướng theo va chạm, ngược chiều kim đồng hồ.
		}
		else
			if (AABBCheck(box, block)) return 5;
	}
	return 0;
}