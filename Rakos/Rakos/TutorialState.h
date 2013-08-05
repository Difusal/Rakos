#pragma once

#include "stdIncludes.h"
#include "State.h"
#include "Weapon.h"
#include "Player.h"
#include "NPC.h"
#include "Rabbit.h"
#include "Portal.h"
#include "Switch.h"

class TutorialState: public State
{
public:
	void InitializeLivingBeings();
	void UpdateSwitches();

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

	vector<Portal*> portals;
	Portal *tutorialPortal;

	vector<Switch*> switches;
	Switch *tutorialSwitch;

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_BITMAP *side_bar;
	ALLEGRO_BITMAP *tutorial_dialog_1;
	ALLEGRO_BITMAP *tutorial_dialog_2;
	ALLEGRO_BITMAP *steve_dialog_1;
	ALLEGRO_BITMAP *steve_dialog_2;
};