#pragma once

#include "stdIncludes.h"
#include "state.h"
#include "Player.h"

static float cameraPosition[2] = { 0, 0 };

class RPG
{
public:
	static RPG *GetInstance();
	void ChangeState(int newState);

	void CreateAllegroDisplay();
	void LoadFonts();
	void LoadWeapons();
	void Initialize();
	void TrackMouse();
	void start_game();
	void Terminate();

	ALLEGRO_DISPLAY *GetDisplay() { return display; }
	ALLEGRO_TIMER *GetTimer(TimerType Timer) {
		switch (Timer)
		{
		default:
		case _RegularTimer: { return timer; break; }
		case _DrawTimer: { return drawTimer; break; }
		case _PlayerAnimTimer: { return playerAnimTimer; break; }
		}
	}
	void SetTileSet (ALLEGRO_BITMAP *png) { tileSet = png; }
	ALLEGRO_BITMAP *GetTileSet() { return tileSet; }
	ALLEGRO_TRANSFORM *GetCamera() { return &camera; }

	Player *GetPlayer() { return player; }
	Weapon *GetWeapon(WeaponType Weapon);

	ALLEGRO_FONT *big_font;
	ALLEGRO_FONT *medium_font;
	ALLEGRO_FONT *small_font;
	ALLEGRO_FONT *tiny_font;

	unsigned int mouse_x, mouse_y;
	bool left_mouse_button_pressed;
	bool left_mouse_button_released;
	bool left_mouse_button_pressed_twice;
	bool right_mouse_button_pressed;
	bool right_mouse_button_released;

private:
	static RPG *instance;
	vector<State*> states;
	int state;

	ALLEGRO_BITMAP *mouse;
	ALLEGRO_BITMAP *loading_background;

	Player *player;

	Weapon *no_weapon;
	Weapon *knife;

	int scroll_time_pause;
	bool background_going_left;
	int background_mask;

	bool possible_double_press;
	unsigned int double_press_counter;
	bool done, draw;

	ALLEGRO_DISPLAY *display;
	ALLEGRO_TIMER *timer;
	ALLEGRO_TIMER *drawTimer;
	ALLEGRO_TIMER *playerAnimTimer;
	ALLEGRO_BITMAP *tileSet;
	ALLEGRO_EVENT_QUEUE *event_queue;
	ALLEGRO_EVENT ev;
	ALLEGRO_TRANSFORM camera;
};