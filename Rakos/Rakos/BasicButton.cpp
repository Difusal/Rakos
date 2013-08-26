#include "BasicButton.h"
#include "RPG.h"

BasicButton::BasicButton( string Label, unsigned int X, unsigned int Y, unsigned int Width ) {
	// setting label
	label = Label;

	// setting font
	font = al_load_font(CalibriTTF, 15, ALLEGRO_ALIGN_CENTER);
	if (!font) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load font file.", "Have you included the resources in the same directory of the program?", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	// setting button position
	x = X;
	y = Y;

	// setting button width
	width = Width;

	// setting button height
	height = font->height - 0.1*font->height;

	// initializing bool values
	beingHovered = false;
	released = false;
}

void BasicButton::Update(unsigned int referencePointX, unsigned int referencePointY) {
	// updating real coords
	realX = referencePointX + x;
	realY = referencePointY + y;

	// setting bool variables to their default value
	beingHovered = false;
	released = false;

	// checking if button is being hovered
	if (realX-width/2.0 < RPG::GetInstance()->Mouse->x && RPG::GetInstance()->Mouse->x < realX+width/2.0 &&
		realY < RPG::GetInstance()->Mouse->y && RPG::GetInstance()->Mouse->y < realY+height) {
			beingHovered = true;

			// checking if button was pressed
			if (RPG::GetInstance()->Mouse->leftMouseButtonReleased) {
				cout << label << " button was pressed." << endl;
				released = true;
			}
	}
	else
		beingHovered = false;
}

void BasicButton::Draw(ALLEGRO_COLOR ButtonColor, ALLEGRO_COLOR ButtonColorWhenBeingHovered) {
	// if button is being hovered use a different button color
	ALLEGRO_COLOR buttonColor;
	switch (beingHovered) {
	case false:
		buttonColor = ButtonColor;
		break;
	case true:
		buttonColor = ButtonColorWhenBeingHovered;
		break;
	}

	// drawing button background
	al_draw_filled_rectangle(realX - width/2.0, realY, realX + width/2.0, realY + height, buttonColor);

	// drawing button contour
	al_draw_rectangle(realX - width/2.0, realY, realX + width/2.0, realY + height, Black, 1.0);

	// printing label
	al_draw_text(font, Black, realX, realY + 0.025*font->height, ALLEGRO_ALIGN_CENTER, label.c_str());
}

BasicButton::~BasicButton( void ) {
	al_destroy_font(font);
}