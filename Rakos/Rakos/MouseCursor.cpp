#include "MouseCursor.h"
#include "RPG.h"

MouseCursor::MouseCursor(void) {
	cout << "Creating mouse cursor..." << endl;

	mouse_x = ScreenWidth;
	mouse_y = ScreenHeight;

	left_mouse_button_pressed = false;
	left_mouse_button_released = false;
	right_mouse_button_pressed = false;
	right_mouse_button_released = false;

	playAnim = false;
	animFrame = 0;

	possible_double_press = false;
	double_press_counter = 0;

	bitmap = al_load_bitmap(MouseCursorPng);
}

bool MouseCursor::Update(ALLEGRO_EVENT *ev) {
	// initializing return value
	bool draw = false;

	/* --- controlling left mouse button double press --- */
	if (possible_double_press && double_press_counter < FPS*1.5/4)
		double_press_counter++;
	else if (possible_double_press)	{
		possible_double_press = false;
		double_press_counter = 0;
	}

	/* --- tracking mouse position --- */
	if (ev->type == ALLEGRO_EVENT_MOUSE_AXES) {
		mouse_x = ev->mouse.x + RPG::GetInstance()->cameraPosition[0];
		mouse_y = ev->mouse.y + RPG::GetInstance()->cameraPosition[1];

		prevMouseRawX = ev->mouse.x;
		prevMouseRawY = ev->mouse.y;

		draw = true;
	}
	else {
		mouse_x = prevMouseRawX + RPG::GetInstance()->cameraPosition[0];
		mouse_y = prevMouseRawY + RPG::GetInstance()->cameraPosition[1];

		draw = true;
	}

	/* --- tracking button presses/releases --- */
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (ev->mouse.button &1) {
			//cout << "* Left mouse button pressed *" << endl;
			left_mouse_button_pressed = true;
			left_mouse_button_released = false;
			draw = true;
		}
		if (ev->mouse.button &2) {
			//cout << "* Right mouse button pressed *" << endl;
			right_mouse_button_pressed = true;
			right_mouse_button_released = false;
			draw = true;
		}
	}
	if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		if (ev->mouse.button &1) {
			if (possible_double_press) {
				cout << "* Left mouse button released(pressed) twice *" << endl;
				left_mouse_button_pressed_twice = true;
			}
			else
				cout << "* Left mouse button released *" << endl;

			possible_double_press = true;
			left_mouse_button_pressed = false;
			left_mouse_button_released = true;

			playAnim = true;
			animFrame = 0;

			draw = true;
		}
		if (ev->mouse.button &2) {
			cout << "* Right mouse button released *" << endl;
			right_mouse_button_pressed = false;
			right_mouse_button_released = true;

			playAnim = true;
			animFrame = 0;

			draw = true;
		}
	}

	// controlling animation
	if (ev->timer.source == RPG::GetInstance()->GetTimer(_MouseAnimTimer) && playAnim) {
		animFrame++;
		if (animFrame > 3) {
			playAnim = false;
			animFrame = 0;
		}

		draw = true;
	}

	return draw;
}

void MouseCursor::Draw() {
	double size = al_get_bitmap_height(bitmap);
	al_draw_bitmap_region(bitmap, animFrame*size, 0, size, size, mouse_x-size/2.0, mouse_y-size/2.0, NULL);
}

void MouseCursor::SetAllReleaseValuesToFalse() {
	left_mouse_button_released = false;
	left_mouse_button_pressed_twice = false;
	right_mouse_button_released = false;
}

MouseCursor::~MouseCursor(void) {
	al_destroy_bitmap(bitmap);
}