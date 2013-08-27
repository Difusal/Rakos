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

class RakosState: public State {
public:
	void InitializeLivingBeings();
	void InitializeDialogs();
	void MoveLivingBeings(ALLEGRO_EVENT *ev);
	void UpdateDialogs();
	void DrawDialogs();

	virtual void Initialize();
	bool Update (ALLEGRO_EVENT *ev);
	virtual void Draw();
	virtual void Terminate();

private:
	vector<vector<vector<int> >*> worldMapLevels;
	vector<vector<int> > worldMapLevel1;
	vector<vector<int> > worldMapLevel2;
	//vector<vector<int> > accessibleTilesWorldMap;
	vector<vector<int>*> levelsAccessibleTiles;
	vector<int> level1AccessibleTiles;
	vector<int> level2AccessibleTiles;
	unsigned int seaAnimationFrame;

	SideBar *sideBar;

	vector<LivingBeing*> livingBeings;
	Player *player;
// 	NPC *Steve;
// 	Rabbit *rabbit;

// 	vector<Switch*> switches;
// 	Switch *tutorialSwitch;

// 	vector<Portal*> portals;
// 	Portal *tutorialPortal;

	ALLEGRO_KEYBOARD_STATE keyState;

// 	vector<TextBox*> textBoxes;
// 	TextBox *tutorialDialog1;

// 	vector<SpeechBubble*> speechBubbles;
// 	SpeechBubble *steveDialog1;
};