#pragma once

#include "stdIncludes.h"
#include "State.h"
#include "SideBar.h"
#include "Weapon.h"
#include "Player.h"
#include "NPC.h"
#include "Rabbit.h"
#include "Portal.h"
#include "BasicPortal.h"
#include "Switch.h"
#include "TextBox.h"
#include "SideBarWindow.h"
#include "ConfirmationDialog.h"

class TutorialState: public State {
public:
	void InitializeLivingBeings();
	void InitializeDialogs();
	void InitializeConfirmationDialogs();
	virtual void Initialize();

	void MoveLivingBeings(ALLEGRO_EVENT *ev);
	void UpdateSwitches();
	void UpdateDialogs();
	bool CheckIfPlayerChoseAVocation(ALLEGRO_EVENT *ev);
	bool Update (ALLEGRO_EVENT *ev);

	virtual void Draw();
	virtual void Terminate();

private:
	vector<vector<vector<int> >*> worldMapLevels;
	vector<vector<int> > worldMapLevel1;
	vector<vector<int> > worldMapLevel2;
	vector<vector<int>*> levelsAccessibleTiles;
	vector<int> level1AccessibleTiles;
	vector<int> level2AccessibleTiles;
	unsigned int seaAnimationFrame;

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
	BasicPortal *portalToRakos;

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

	vector<ConfirmationDialog*> confirmationDialogs;
	ConfirmationDialog *mageConfirmation;
	ConfirmationDialog *warriorConfirmation;

	bool playerHasTalkedToSteve;
};