#pragma once

#include "stdIncludes.h"
#include "State.h"
#include "SideBar.h"
#include "Weapon.h"
#include "Player.h"
#include "NPC.h"
#include "Rabbit.h"
#include "Portal.h"
#include "Switch.h"
#include "TextBox.h"
#include "SideBarWindow.h"

class TutorialState: public State {
public:
	void InitializeLivingBeings();
	void InitializeDialogs();
	void MoveLivingBeings(ALLEGRO_EVENT *ev);
	void UpdateDialogs();
	void UpdateSwitches();
	bool CheckIfPlayerChoseAVocation(ALLEGRO_EVENT *ev);
	void DrawDialogs();

	virtual void Initialize();
	bool Update (ALLEGRO_EVENT *ev);
	virtual void Draw();
	virtual void Terminate();

private:
	vector<vector<int> > worldMap;
	unsigned int seaAnimationFrame;
	vector<int> accessibleTiles;

	SideBar *sideBar;

	vector<LivingBeing*> livingBeings;
	Player *player;
	NPC *Steve;
	NPC *WhiteKnight;
	NPC *Mage;
	NPC *Warrior;
	Rabbit *rabbit;

	vector<Switch*> switches;
	Switch *tutorialSwitch;

	vector<Portal*> portals;
	Portal *tutorialPortal;

	ALLEGRO_KEYBOARD_STATE keyState;

	vector<TextBox*> textBoxes;
	TextBox *tutorialDialog1;
	TextBox *tutorialDialog2;

	vector<SpeechBubble*> speechBubbles;
	SpeechBubble *steveDialog1;
	SpeechBubble *steveDialog2;
	SpeechBubble *whiteKnightDialog;
	SpeechBubble *mageDialog;
	SpeechBubble *mageDialogIfPlayerIsAMage;
	SpeechBubble *mageDialogIfPlayerIsNOTAMage;
	SpeechBubble *warriorDialog;
	SpeechBubble *warriorDialogIfPlayerIsAWarrior;
	SpeechBubble *warriorDialogIfPlayerIsNOTAWarrior;

	bool playerHasTalkedToSteve;
};