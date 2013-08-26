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

	unsigned int x, y;
	bool leftMouseButtonHasJustBeenPressed;
	bool leftMouseButtonWasBeingPressedBefore;
	bool leftMouseButtonPressed;
	bool leftMouseButtonReleased;
	bool leftMouseButtonPressedTwice;
	bool rightMouseButtonPressed;
	bool rightMouseButtonReleased;

private:
	float prevMouseRawX;
	float prevMouseRawY;

	bool playAnim;
	int animFrame;

	bool possible_double_press;
	unsigned int double_press_counter;

	ALLEGRO_BITMAP *bitmap;
};