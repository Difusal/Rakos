#pragma once

#include "stdIncludes.h"
#include "state.h"
#include "MouseCursor.h"
#include "Player.h"

class RPG
{
public:
	static RPG *GetInstance();
	void ChangeState(int newState);

	void LoadWeapons();

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

	void Initialize();
	void start_game();
	void Terminate();

	ALLEGRO_DISPLAY *GetDisplay() { return display; }
	MouseCursor *Mouse;
	ALLEGRO_TIMER *GetTimer(TimerType Timer) {
		switch (Timer)
		{
		default:
		case _RegularTimer: { return timer; break; }
		case _MouseAnimTimer: { return mouseAnimTimer; break; }
		case _DrawTimer: { return drawTimer; break; }
		case _PlayerAnimTimer: { return playerAnimTimer; break; }
		}
	}
	void SetTileSet (ALLEGRO_BITMAP *png) { tileSet = png; }
	ALLEGRO_BITMAP *GetTileSet() { return tileSet; }

	float cameraPosition[2];
	ALLEGRO_TRANSFORM *GetCamera() { return &camera; }

	Player *GetPlayer() { return player; }
	Weapon *GetWeapon(WeaponType Weapon);

	ALLEGRO_FONT *big_font;
	ALLEGRO_FONT *medium_font;
	ALLEGRO_FONT *small_font;
	ALLEGRO_FONT *tiny_font;

private:
	static RPG *instance;
	vector<State*> states;
	int state;

	vector<ALLEGRO_TIMER*> timers;
	vector<ALLEGRO_FONT*> fonts;

	ALLEGRO_BITMAP *loading_background;

	Player *player;

	Weapon *no_weapon;
	Weapon *knife;

	int scroll_time_pause;
	bool background_going_left;
	int background_mask;

	bool done, draw;

	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer;
	ALLEGRO_TIMER *mouseAnimTimer;
	ALLEGRO_TIMER *drawTimer;
	ALLEGRO_TIMER *playerAnimTimer;
	ALLEGRO_BITMAP *tileSet;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_EVENT ev;
	ALLEGRO_TRANSFORM camera;
};