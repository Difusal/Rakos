#pragma once

#include "stdIncludes.h"
#include "state.h"
#include "MouseCursor.h"
#include "Player.h"
#include "Portal.h"

class RPG {
public:
	static RPG *GetInstance();
	void ChangeState(int newState);

	void StartAllegro5();
	void CreateAllegroDisplay();
	void DisplayLoadingSplashScreen();
	void StartMouseCursor();
	void LoadFonts();
	void CreateTimers();
	void CreateEventQueue();
	void LoadSoundSamples();
	void InitializeVariables();
	void StartTimers();

	void LoadWeapons();
	void LoadShields();

	void StartGameControlCycle();
	void Initialize();
	void Update();
	void Draw();
	void Terminate();

	// Public Methods
	void CheckIfPlayerWantsToChat(vector<LivingBeing*> &livingBeings, ALLEGRO_KEYBOARD_STATE keyState);
	void CheckIfPlayerAttackedSomething(vector<LivingBeing*> &livingBeings, ALLEGRO_KEYBOARD_STATE keyState);
	bool RemoveDeadLivingBeingsFromVector(vector<LivingBeing*> &livingBeings);

	bool livingBeingCollidingWithMap(LivingBeing *being, const vector<vector<int> > &worldMap, const vector<int> &unaccessibleTiles);
	void UpdateLivingBeingsCollisions(LivingBeing *a, LivingBeing *b);
	void LoadAccessibleTiles(vector<int> &Level1AccessibleTiles, vector<int> &Level2AccessibleTiles);

	void UpdateAnimationsFrame(vector<LivingBeing*> &livingBeings);
	void UpdateAnimationsFrame(vector<Portal*> &portals);
	void UpdateWeaponAndShieldPositions(vector<LivingBeing*> &livingBeings);
	void UpdateWeaponAttackAnimations(vector<LivingBeing*> &livingBeings);
	void UpdateCamera(vector<vector<int> > &worldMap, vector<LivingBeing*> &livingBeings);

	ALLEGRO_DISPLAY *GetDisplay() { return display; }
	ALLEGRO_TIMER *GetTimer(TimerType Timer) { return timers[Timer]; }
	ALLEGRO_TRANSFORM *GetCamera() { return &camera; }

	ALLEGRO_BITMAP *GetTileSet() { return tileSet; }
	void SetTileSet (ALLEGRO_BITMAP *png) { tileSet = png; }
	ALLEGRO_BITMAP *GetSeaBitmap() { return seaAnimation; }

	Player *GetPlayer() { return player; }
	Weapon *GetWeapon(WeaponType Weapon) { return weapons[Weapon]; }
	Shield *GetShield(ShieldType Shield) { return shields[Shield]; }


	// Public Variables
	Language LanguageBeingUsed;

	ALLEGRO_FONT *big_font;
	ALLEGRO_FONT *medium_font;
	ALLEGRO_FONT *small_font;
	ALLEGRO_FONT *tiny_font;

	MouseCursor *Mouse;
	float cameraPosition[2];
	int prevCameraX;
	int prevCameraY;

private:
	static RPG *instance;
	vector<State*> states;
	int state;

	vector<ALLEGRO_TIMER*> timers;
	ALLEGRO_TIMER *timer;
	ALLEGRO_TIMER *playerMoveTimer;
	ALLEGRO_TIMER *NPCMoveTimer;
	ALLEGRO_TIMER *slowCreatureMoveTimer;
	ALLEGRO_TIMER *mouseAnimTimer;
	ALLEGRO_TIMER *drawTimer;
	ALLEGRO_TIMER *playerAnimTimer;
	ALLEGRO_TIMER *weaponAnimTimer;
	ALLEGRO_TIMER *portalAnimTimer;

	vector<ALLEGRO_FONT*> fonts;

	ALLEGRO_BITMAP *loading_background;
	ALLEGRO_BITMAP *tileSet;
	ALLEGRO_BITMAP *seaAnimation;

	Player *player;
	LivingBeing *previousNPCWhoTalkedToPlayer;

	vector<Weapon*> weapons;
	Weapon *no_weapon;
	Weapon *knife;
	Weapon *wand;
	Weapon *sword;

	vector<Shield*> shields;
	Shield *no_shield;
	Shield *woodenShield;

	Language DefaultLanguage;
	bool done, draw;

	ALLEGRO_DISPLAY *display;
	
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_EVENT ev;
	ALLEGRO_TRANSFORM camera;
};