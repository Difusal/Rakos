#include "Button.h"
#include "Editor.h"

Button::Button(string Label, unsigned int Y, ButtonPosition Position, unsigned int sideBarWidth) {
	// setting label
	label = Label;

	// setting font
	font = al_load_font(CalibriTTF, 16, ALLEGRO_ALIGN_CENTER);
	if (!font) {
		al_show_native_message_box(Editor::GetInstance()->GetDisplay(), "Error", "Could not load font file.", "Have you included the resources in the same directory of the program?", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	// setting button width
	switch (Position) {
	case _Left:
	case _Right:
		width = 40;
		break;
	case _Center:
		width = 90;
		break;
	}

	// setting button height
	height = font->height - 0.1*font->height;

	// setting button coords
	switch (Position) {
	case _Left:
		x = sideBarWidth/2.0 - (sideBarWidth/2.0 - 5)/2.0;
		break;
	case _Center:
		x = sideBarWidth/2.0;
		break;
	case _Right:
		x = sideBarWidth/2.0 + (sideBarWidth/2.0 - 5)/2.0;
		break;
	}
	y = Y;
	
	// initializing bool values
	beingHovered = false;
	released = false;
}


void Button::Update(unsigned int sideBarX, unsigned int sideBarY) {
	realX = x + sideBarX;
	realY = y + sideBarY;

	// setting bool variables to their default value
	beingHovered = false;
	released = false;

	// checking if button is being hovered
	if (realX-width/2.0 < Editor::GetInstance()->Mouse->x && Editor::GetInstance()->Mouse->x < realX+width/2.0 &&
		realY < Editor::GetInstance()->Mouse->y && Editor::GetInstance()->Mouse->y < realY+height) {
			beingHovered = true;

			// checking if button was pressed
			if (Editor::GetInstance()->Mouse->leftMouseButtonReleased) {
				cout << label << " button was pressed." << endl;
				released = true;
			}
		}
	else
		beingHovered = false;
}

void Button::Draw() {
	// if button is being hovered use a different button color
	ALLEGRO_COLOR buttonColor;
	switch (beingHovered) {
	case false:
		buttonColor = White;
		break;
	case true:
		buttonColor = LightBlue;
		break;
	}

	// drawing button background
	al_draw_filled_rectangle(realX - width/2.0, realY, realX + width/2.0, realY + height, buttonColor);

	// drawing button contour
	al_draw_rectangle(realX - width/2.0, realY, realX + width/2.0, realY + height, DarkGray, 1.0);

	// printing label
	al_draw_text(font, Black, realX, realY + 1, ALLEGRO_ALIGN_CENTER, label.c_str());
}

void Button::DrawLockedButton() {
	// drawing different button contour
	al_draw_rectangle(realX - width/2.0, realY, realX + width/2.0, realY + height, Green, 1.0);
}


Button::~Button( void ) {
	// destroying font
	al_destroy_font(font);
}