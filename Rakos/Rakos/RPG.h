#pragma once

#include "stdIncludes.h"
#include "state.h"
#include "MouseCursor.h"
#include "Player.h"
#include "Portal.h"

class RPG
{
public:
	// Public Methods
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
	Weapon *GetWeapon(WeaponType Weapon);

	void CheckIfPlayerWantsToChat(vector<LivingBeing*> &livingBeings, ALLEGRO_KEYBOARD_STATE keyState);
	void RemoveDeadLivingBeingsFromVector(vector<LivingBeing*> &livingBeings);

	bool livingBeingCollidingWithMap(int Dir, const vector<vector<int> > &worldMap, const vector<int> &unaccessibleTiles);
	void UpdateLivingBeingsCollisions(LivingBeing *a, LivingBeing *b);

	void UpdateAnimationsFrame(vector<LivingBeing*> &livingBeings);
	void UpdateAnimationsFrame(vector<Portal*> &portals);
	void UpdateCamera(vector<vector<int> > &worldMap);

	void Initialize();
	void Update();
	void Draw();
	void StartGameControlCycle();
	void Terminate();

	ALLEGRO_DISPLAY *GetDisplay() { return display; }
	ALLEGRO_TIMER *GetTimer(TimerType Timer);
	ALLEGRO_TRANSFORM *GetCamera() { return &camera; }

	ALLEGRO_BITMAP *GetTileSet() { return tileSet; }
	void SetTileSet (ALLEGRO_BITMAP *png) { tileSet = png; }

	Player *GetPlayer() { return player; }


	// Public Variables
	ALLEGRO_FONT *big_font;
	ALLEGRO_FONT *medium_font;
	ALLEGRO_FONT *small_font;
	ALLEGRO_FONT *tiny_font;

	MouseCursor *Mouse;
	float cameraPosition[2];

private:
	static RPG *instance;
	vector<State*> states;
	int state;

	vector<ALLEGRO_TIMER*> timers;
	vector<ALLEGRO_FONT*> fonts;

	ALLEGRO_BITMAP *loading_background;

	Player *player;
	LivingBeing *previousNPCWhoTalkedToPlayer;

	Weapon *no_weapon;
	Weapon *knife;

	bool done, draw;

	ALLEGRO_DISPLAY *display;

	ALLEGRO_TIMER *timer;
	ALLEGRO_TIMER *mouseAnimTimer;
	ALLEGRO_TIMER *drawTimer;
	ALLEGRO_TIMER *playerAnimTimer;
	ALLEGRO_TIMER *portalAnimTimer;

	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_EVENT ev;
	ALLEGRO_BITMAP *tileSet;
	ALLEGRO_TRANSFORM camera;
};