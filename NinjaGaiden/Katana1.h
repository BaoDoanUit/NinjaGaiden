#ifndef _SWORD_H_
#define _SWORD_H_
#include "Weapon.h"
#include "TextureManager.h"
#define KATANA_VX 0.33f

class Katana1 : public Weapon
{
public:
	Katana1();
	~Katana1();
	virtual void Update(Camera *camera, int t);
	virtual void Create(float ninjaGaiden_x, float ninjaGaiden_y, int ninjaGaiden_trend);
};
#endif