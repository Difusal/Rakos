#include "Weapon.h"


Weapon::Weapon()
{
	name = "none";
	min_attack = 0;
	max_attack = 0;
}

Weapon::Weapon(string Name, int minAttack, int maxAttack)
{
	name = Name;
	min_attack = minAttack;
	max_attack = maxAttack;
}

int Weapon::Damage()
{
	return ((rand() % ((max_attack+1)-min_attack)) + min_attack);
}

Weapon::~Weapon(void)
{
}