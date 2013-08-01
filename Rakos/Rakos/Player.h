#pragma once

#include "LivingBeing.h"
#include "Weapon.h"
#include "globalEnums.h"

class Player: public LivingBeing {
public:
	Player(Weapon *weapon, double X, double Y);

	Weapon *getWeapon() { return weapon; }
	void setWeapon(Weapon *newWeapon) { weapon = newWeapon; }

	bool getRunningState() { return running; }
	void setRunningState(bool newState) { running = newState; }

	double getFeetX() { return feet_x; }
	double getFeetY() { return feet_y; }
	void updateFeetCoords();

	~Player(void);

private:
	Weapon *weapon;

	bool running;
	double feet_x, feet_y;
};