#ifndef _SWEET_AABB_H
#define _SWEET_AABB_H

using namespace std;

extern struct Box
{
	Box(float _x, float _y, float _w, float _h, float _vx, float _vy)
	{
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		vx = _vx;
		vy = _vy;
	}
	float x, y; // tọa độ
	float w, h; // dài, rộng
	float vx, vy; // Vận tốc 
};
extern bool AABBCheck(Box b1, Box b2);
extern bool AABB(Box b1, Box b2, float& moveX, float& moveY);
extern Box GetSweptBroadphaseBox(Box b);
extern float SweptAABB(Box b1, Box b2, float& normalx, float& normaly);
extern int Collide(Box &box, Box &block, float &collisiontime, float &x, float &y);
#endif 

//extern : hiệu quả trong việc nhiều file .cpp sử dụng lại nó(global)