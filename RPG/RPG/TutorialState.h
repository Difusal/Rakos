#pragma once

#include "State.h"
#include "Weapon.h"
#include "Player.h"
#include "NPC.h"
#include "Rabbit.h"
#include "stdIncludes.h"

class TutorialState: public State
{
public:
	virtual void Initialize();
	bool Update (ALLEGRO_EVENT * ev);
	virtual void Draw();
	virtual void Terminate();

	void LoadWeapons();
	bool mapCollision(int Dir, const vector<int> &tiles);

	void updateMovingObjectsCollisions(MovingObject &a, MovingObject &b);
	void updateAnimationFrame(MovingObject &obj);
	void moveObject(MovingObjectSon &obj);

private:
	vector<vector<int> > world_map;
	vector<int> unaccessible_tiles;
	vector<MovingObject*> movingStuff;
	vector<MovingObjectSon*> movingCreaturesAndNpcs;

	Player *player;
	NPC *steve;
	NPC *knight;
	NPC *sorcerer;
	NPC *warrior;
	Rabbit *rabbit;
	
	Weapon *no_weapon;
	Weapon *knife;
	
	int attack_cooldown;
	bool player_can_attack;
	int switch_cooldown;
	bool switch_pressed;

	bool show_tutorial_dialog_1;
	bool show_tutorial_dialog_2;
	bool show_steve_dialog_1;
	bool show_steve_dialog_2;
	bool player_has_talked_to_steve;

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_BITMAP * side_bar;
	ALLEGRO_BITMAP * tutorial_dialog_1;
	ALLEGRO_BITMAP * tutorial_dialog_2;
	ALLEGRO_BITMAP * steve_dialog_1;
	ALLEGRO_BITMAP * steve_dialog_2;
};