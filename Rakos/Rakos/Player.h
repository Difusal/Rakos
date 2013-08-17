#pragma once

#include "LivingBeing.h"
#include "globalEnums.h"
#include "globalFunctions.h"

class Player: public LivingBeing {
public:
	Player(string Name, Weapon *weapon, Shield *shield, double X, double Y);

	void CheckIfRunning(ALLEGRO_KEYBOARD_STATE keyState);
	void UpdatePosition(ALLEGRO_KEYBOARD_STATE keyState, const vector<vector<int> > &worldMap);
	void Move(ALLEGRO_KEYBOARD_STATE keyState, const vector<vector<int> > &worldMap, const vector<int> &unaccessibleTiles);
	void CorrectPositionIfCollidingWithMapLimits(const vector<vector<int> > &worldMap, const vector<int> &unaccessibleTiles);
	void ControlAttackRate();
	void UpdateFeetCoords();

	bool CanAttack() { return playerCanAttack; }
	void CanNotAttackNow() { playerCanAttack = false; }

	Vocation getVocation() { return vocation; }
	void setVocation(Vocation PlayerVocation) { vocation = PlayerVocation; }

	Weapon *getWeapon() { return weapon; }
	void setWeapon(Weapon *newWeapon);

	Shield *getShield() { return shield; }
	void setShield(Shield *newShield);


	unsigned int getMP() { return mp; }
	unsigned int getMaxMP() { return maxMp; }

	void addExperience(unsigned int Experience) { experience += Experience; }
	void addGold(unsigned int Gold) { gold->addGoldCoins(Gold); }
	unsigned int getLevel() { return level; }
	void updateLevel() { level = computeLevel(experience); }


	bool getRunningState() { return running; }
	void setRunningState(bool newState) { running = newState; }

	double getFeetX() { return feet_x; }
	double getFeetY() { return feet_y; }

	~Player(void);

private:
	Vocation vocation;

	unsigned int mp;
	unsigned int maxMp;

	unsigned int level;

	int attackCooldown;
	bool playerCanAttack;

	bool running;
	unsigned int feet_x, feet_y;
};