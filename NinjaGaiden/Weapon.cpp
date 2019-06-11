#include "Weapon.h"



Weapon::Weapon()
{
	IsFinish = 1;
}

Weapon::~Weapon()
{
	delete GTObject;
	delete GSObject;
}
