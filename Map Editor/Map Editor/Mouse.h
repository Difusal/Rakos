#pragma once

#include "stdIncludes.h"

class MouseCursor {
public:
	MouseCursor(void);

	bool Update(ALLEGRO_EVENT *ev);
	bool CorrectMousePosition();
	void SetAllReleaseValuesToFalse();

	~MouseCursor(void);


	// Public Variables
	unsigned int x, y;

	int xDraggingDisplacement, yDraggingDisplacement;

	bool leftMouseButtonPressed;
	bool leftMouseButtonHasJustBeenPressed;
	bool leftMouseButtonReleased;
	bool leftMouseButtonPressedTwice;

	bool rightMouseButtonPressed;
	bool rightMouseButtonReleased;

private:
	float prevMouseRawX;
	float prevMouseRawY;

	unsigned int clickSourceX, clickSourceY;

	bool possible_double_press;
	unsigned int double_press_counter;
};