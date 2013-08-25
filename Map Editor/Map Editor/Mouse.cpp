#include "Mouse.h"
#include "Editor.h"

MouseCursor::MouseCursor(void) {
	cout << "Creating mouse cursor..." << endl;

	x = Editor::GetInstance()->ScreenWidth;
	y = Editor::GetInstance()->ScreenHeight;
	
	xDraggingDisplacement = 0;
	yDraggingDisplacement = 0;

	leftMouseButtonHasJustBeenPressed = false;
	leftMouseButtonPressed = false;
	leftMouseButtonReleased = false;

	rightMouseButtonPressed = false;
	rightMouseButtonReleased = false;

	possible_double_press = false;
	double_press_counter = 0;
}

bool MouseCursor::Update(ALLEGRO_EVENT *ev) {
	// initializing return value
	bool draw = false;

	// controlling left mouse button double press
	if (possible_double_press && double_press_counter < FPS*1.5/4)
		double_press_counter++;
	else if (possible_double_press)	{
		possible_double_press = false;
		double_press_counter = 0;
	}

	// tracking mouse position
	if (ev->type == ALLEGRO_EVENT_MOUSE_AXES) {
		x = ev->mouse.x + Editor::GetInstance()->cameraPosition[0];
		y = ev->mouse.y + Editor::GetInstance()->cameraPosition[1];

		prevMouseRawX = ev->mouse.x;
		prevMouseRawY = ev->mouse.y;

		draw = true;
	}

	// checking if left mouse button was being pressed before
	if (leftMouseButtonHasJustBeenPressed)
		leftMouseButtonHasJustBeenPressed = false;

	// tracking button presses
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (ev->mouse.button &1) {
			//cout << "* Left mouse button pressed *" << endl;
			leftMouseButtonPressed = true;
			leftMouseButtonHasJustBeenPressed = true;
			leftMouseButtonReleased = false;
			draw = true;
		}
		if (ev->mouse.button &2) {
			//cout << "* Right mouse button pressed *" << endl;
			rightMouseButtonPressed = true;
			rightMouseButtonReleased = false;
			draw = true;
		}
	}

	// tracking button releases
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		if (ev->mouse.button &1) {
			if (possible_double_press) {
				cout << "* Left mouse button released(pressed) twice *" << endl;
				leftMouseButtonPressedTwice = true;
			}
			else
				cout << "* Left mouse button released *" << endl;

			possible_double_press = true;
			leftMouseButtonPressed = false;
			leftMouseButtonReleased = true;

			draw = true;
		}
		if (ev->mouse.button &2) {
			cout << "* Right mouse button released *" << endl;
			rightMouseButtonPressed = false;
			rightMouseButtonReleased = true;

			draw = true;
		}
	}

	// registering mouse dragging distances
	if (leftMouseButtonHasJustBeenPressed) {
		clickSourceX = x;
		clickSourceY = y;
	}
	if (leftMouseButtonPressed) {
		xDraggingDisplacement = x - clickSourceX;
		yDraggingDisplacement = y - clickSourceY;
	}
	else {
		xDraggingDisplacement = 0;
		yDraggingDisplacement = 0;
	}

	return draw;
}

bool MouseCursor::CorrectMousePosition() {
	x = prevMouseRawX + Editor::GetInstance()->cameraPosition[0];
	y = prevMouseRawY + Editor::GetInstance()->cameraPosition[1];

	return true;
}

void MouseCursor::SetAllReleaseValuesToFalse() {
	leftMouseButtonReleased = false;
	leftMouseButtonPressedTwice = false;
	rightMouseButtonReleased = false;
}

MouseCursor::~MouseCursor(void) {
	// nothing to destroy here
}