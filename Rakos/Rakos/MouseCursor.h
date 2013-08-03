#pragma once

#include "stdIncludes.h"

class MouseCursor
{
public:
	MouseCursor(void);

	bool Update(ALLEGRO_EVENT *ev);
	bool CorrectMousePosition();
	void Draw();
	void SetAllReleaseValuesToFalse();

	~MouseCursor(void);

	unsigned int mouse_x, mouse_y;
	bool left_mouse_button_pressed;
	bool left_mouse_button_released;
	bool left_mouse_button_pressed_twice;
	bool right_mouse_button_pressed;
	bool right_mouse_button_released;

private:
	float prevMouseRawX;
	float prevMouseRawY;

	bool playAnim;
	int animFrame;

	bool possible_double_press;
	unsigned int double_press_counter;

	ALLEGRO_BITMAP *bitmap;
};