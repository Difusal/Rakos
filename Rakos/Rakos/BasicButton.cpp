#include "BasicButton.h"
#include "RPG.h"

void BasicButton::Update() {
	// if button is not active, do nothing
	if (!active)
		return;

	// setting bool variables to their default value
	beingPressed = false;
	beingHovered = false;
	released = false;

	// checking if button is being hovered
	if (x+RPG::GetInstance()->cameraPosition[0] < RPG::GetInstance()->Mouse->x && RPG::GetInstance()->Mouse->x < x+RPG::GetInstance()->cameraPosition[0]+width &&
		y+RPG::GetInstance()->cameraPosition[1] < RPG::GetInstance()->Mouse->y && RPG::GetInstance()->Mouse->y < y+RPG::GetInstance()->cameraPosition[1]+height) {
			beingHovered = true;

			// checking if button was released
			if (RPG::GetInstance()->Mouse->leftMouseButtonPressed) {
				beingPressed = true;
			}

			// checking if button was released
			if (RPG::GetInstance()->Mouse->leftMouseButtonReleased) {
				cout << label << " button was released." << endl;
				released = true;
			}
	}
	else {
		beingPressed = false;
		beingHovered = false;
	}
}

BasicButton::~BasicButton(void) {
	al_destroy_font(font);
}