#pragma once

#include "stdIncludes.h"

int random_number (int min, int max);
static float cameraPosition[2] = { 0, 0 };
void CameraUpdate(vector<vector<int> > & worldMap, float * cameraPosition, float x, float y, int width, int height);
bool boxCollision(float x, float y, float ex, float ey, int width, int height);
float calculateDistance(float p1_x, float p1_y, float p2_x, float p2_y);

class State;
enum _screenState
{
	Tutorial
};

enum Direction { DOWN, LEFT, RIGHT, UP };
enum Type { playerType, npcType, creatureType };

class StateControl
{
public:
	void Initialize();
	void CreateAllegroDisplay();
	void LoadFonts();
	void start_game();
	void Terminate();

	static StateControl * GetInstance();
	void ChangeState(int newState);

	ALLEGRO_DISPLAY * GetDisplay() { return display; }
	ALLEGRO_TIMER * GetTimer(int timerID)
	{
		switch (timerID)
		{
		default:
		case 0: { return timer; break; }
		case 1: { return drawTimer; break; }
		case 2: { return playerAnimTimer; break; }
		}
	}
	ALLEGRO_BITMAP * GetTileSet() { return tileSet; }
	void SetTileSet (ALLEGRO_BITMAP * png) { tileSet = png; }
	ALLEGRO_TRANSFORM * GetCamera() { return &camera; }

	int mouse_x, mouse_y;

	bool left_mouse_button_pressed;
	bool left_mouse_button_released;
	bool left_mouse_button_pressed_twice;
	bool right_mouse_button_pressed;
	bool right_mouse_button_released;

	ALLEGRO_FONT * big_font;
	ALLEGRO_FONT * medium_font;
	ALLEGRO_FONT * small_font;
	ALLEGRO_FONT * tiny_font;

private:
	int scroll_time_pause;
	bool background_going_left;
	int background_mask;

	bool possible_double_press;
	unsigned int double_press_counter;
	bool done, draw;

	static StateControl * instance;

	int state;
	vector<State*> states;

	ALLEGRO_TRANSFORM camera;
	ALLEGRO_BITMAP * background;
	ALLEGRO_BITMAP * tileSet;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_EVENT ev;
	ALLEGRO_EVENT_QUEUE * event_queue;
	ALLEGRO_TIMER * timer;
	ALLEGRO_TIMER * drawTimer;
	ALLEGRO_TIMER * playerAnimTimer;
};