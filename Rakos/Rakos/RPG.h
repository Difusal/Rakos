#pragma once

#include "stdIncludes.h"
#include "state.h"

enum GameState {
	Tutorial
};

enum Direction {
	DOWN,
	LEFT,
	RIGHT,
	UP
};

enum LivingBeingType {
	_Player,
	_NPC,
	_Creature
};

enum TimerType {
	RegularTimer,
	DrawTimer,
	PlayerAnimTimer
};

class RPG
{
public:
	static RPG *GetInstance();
	void ChangeState(int newState);

	void CreateAllegroDisplay();
	void LoadFonts();
	void Initialize();
	void TrackMouse();
	void start_game();
	void Terminate();

	ALLEGRO_DISPLAY *GetDisplay() { return display; }
	ALLEGRO_TIMER *GetTimer(int timerID) {
		switch (timerID)
		{
		default:
		case 0: { return timer; break; }
		case 1: { return drawTimer; break; }
		case 2: { return playerAnimTimer; break; }
		}
	}

	ALLEGRO_FONT *big_font;
	ALLEGRO_FONT *medium_font;
	ALLEGRO_FONT *small_font;
	ALLEGRO_FONT *tiny_font;

	void SetTileSet (ALLEGRO_BITMAP *png) { tileSet = png; }
	ALLEGRO_BITMAP *GetTileSet() { return tileSet; }

	ALLEGRO_TRANSFORM *GetCamera() { return &camera; }

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