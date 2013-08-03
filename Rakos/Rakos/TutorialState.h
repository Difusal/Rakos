#pragma once

#include "stdIncludes.h"
#include "State.h"
//#include "LivingBeing.h"
#include "Weapon.h"
#include "Player.h"
#include "NPC.h"
#include "Rabbit.h"
#include "Portal.h"

class TutorialState: public State
{
public:
	void InitializeLivingBeings();
	void CheckIfAnyLivingBeingWasKilled();
	void UpdateAnimations(ALLEGRO_EVENT *ev);

	virtual void Initialize();
	bool Update (ALLEGRO_EVENT *ev);
	virtual void Draw();
	virtual void Terminate();

private:
	vector<vector<int> > worldMap;
	vector<int> unaccessibleTiles;

	vector<LivingBeing*> livingBeings;
	Player *player;
	NPC *steve;
	NPC *knight;
	NPC *sorcerer;
	NPC *warrior;
	Rabbit *rabbit;

	Portal *portal1;

	int switch_cooldown;
	bool switch_pressed;

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_BITMAP *side_bar;
	ALLEGRO_BITMAP *tutorial_dialog_1;
	ALLEGRO_BITMAP *tutorial_dialog_2;
	ALLEGRO_BITMAP *steve_dialog_1;
	ALLEGRO_BITMAP *steve_dialog_2;
};