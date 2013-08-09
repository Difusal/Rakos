#pragma once

#include "stdIncludes.h"
#include "State.h"
#include "Weapon.h"
#include "Player.h"
#include "NPC.h"
#include "Rabbit.h"
#include "Portal.h"
#include "Switch.h"
#include "TextBox.h"

class TutorialState: public State
{
public:
	void InitializeLivingBeings();
	void InitializeDialogs();
	void MoveLivingBeings(ALLEGRO_EVENT *ev);
	void UpdateDialogs();
	void UpdateSwitches();
	void DrawDialogs();

	virtual void Initialize();
	bool Update (ALLEGRO_EVENT *ev);
	virtual void Draw();
	virtual void Terminate();

private:
	vector<vector<int> > worldMap;
	vector<int> unaccessibleTiles;

	vector<LivingBeing*> livingBeings;
	Player *player;
	NPC *Steve;
	NPC *WhiteKnight;
	NPC *Sorcerer;
	NPC *Warrior;
	Rabbit *rabbit;

	vector<Switch*> switches;
	Switch *tutorialSwitch;

	vector<Portal*> portals;
	Portal *tutorialPortal;

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_BITMAP *sideBar;

	vector<TextBox*> dialogs;
	TextBox *tutorialDialog1;
	TextBox *tutorialDialog2;
	ALLEGRO_BITMAP *steveDialog1;
	ALLEGRO_BITMAP *steveDialog2;

	bool playerHasTalkedToSteve;
	bool showSteveDialog1;
	bool showSteveDialog2;
};