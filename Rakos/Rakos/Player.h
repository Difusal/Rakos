#pragma once

#include "LivingBeing.h"
#include "Weapon.h"
#include "globalEnums.h"

class Player: public LivingBeing {
public:
	Player(string Name, Weapon *weapon, double X, double Y);

	void CheckIfRunning(ALLEGRO_KEYBOARD_STATE keyState);
	void UpdatePosition(ALLEGRO_KEYBOARD_STATE keyState, const vector<vector<int> > &worldMap);
	void Move(ALLEGRO_KEYBOARD_STATE keyState, const vector<vector<int> > &worldMap);
	void CorrectPositionIfCollidingWithMapLimits(const vector<vector<int> > &worldMap, const vector<int> &unaccessibleTiles);
	void ControlAttackRate();
	void UpdateFeetCoords();

	bool CanAttack() { return playerCanAttack; }
	void CanNotAttackNow() { playerCanAttack = false; }

	Weapon *getWeapon() { return weapon; }
	void setWeapon(Weapon *newWeapon) { weapon = newWeapon; }

	bool getRunningState() { return running; }
	void setRunningState(bool newState) { running = newState; }

	double getFeetX() { return feet_x; }
	double getFeetY() { return feet_y; }

	~Player(void);


	bool show_tutorial_dialog_1;
	bool show_tutorial_dialog_2;
	bool player_has_talked_to_steve;
	bool show_steve_dialog_1;
	bool show_steve_dialog_2;

private:
	Weapon *weapon;
	int attackCooldown;
	bool playerCanAttack;

	bool running;
	double feet_x, feet_y;
};