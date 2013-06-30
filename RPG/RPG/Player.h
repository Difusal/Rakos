#pragma once

#include "MovingObject.h"
#include "stdIncludes.h"
#include "Weapon.h"

class Player: public MovingObject
{
public:
	Player(void);

	Weapon * getWeapon() { return weapon; }
	void setWeapon(Weapon * newWeapon) { weapon = newWeapon; }

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