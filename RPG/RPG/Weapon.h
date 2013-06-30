#pragma once

#include "stdIncludes.h"
#include "StateControl.h"

class Weapon
{
public:
	Weapon();
	Weapon(string name, int minAttack, int maxAttack);

	string getName() { return name; }
	int Damage();

	~Weapon(void);

private:
	string name;
	int min_attack;
	int max_attack;
};