#include "MenuButton.h"
#include "Editor.h"

MenuButton::MenuButton( string Label, unsigned int Y ) {
	// setting label
	label = Label;

	// setting font
	font = al_load_font(CalibriTTF, 26, ALLEGRO_ALIGN_CENTER);
	if (!font) {
		al_show_native_message_box(Editor::GetInstance()->GetDisplay(), "Error", "Could not load font file.", "Have you included the resources in the same directory of the program?", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	// setting button width and height
	width = 200;
	height = 1.5*font->height;

	// setting button coords
	x = ScreenWidth/2.0;
	y = Y;

	// initializing bool values
	beingHovered = false;
	released = false;
}

void MenuButton::Update() {
	// setting bool variables to their default value
	beingHovered = false;
	released = false;

	// checking if button is being hovered
	if (x-width/2.0 < Editor::GetInstance()->Mouse->x && Editor::GetInstance()->Mouse->x < x+width/2.0 &&
		y < Editor::GetInstance()->Mouse->y && Editor::GetInstance()->Mouse->y < y+height) {
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

void MenuButton::Draw() {
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
	al_draw_filled_rectangle(x - width/2.0, y, x + width/2.0, y + height, buttonColor);

	// drawing button contour
	al_draw_rectangle(x - width/2.0, y, x + width/2.0, y + height, DarkGray, 1.0);

	// printing label
	al_draw_text(font, Black, x, y + 0.3*font->height, ALLEGRO_ALIGN_CENTER, label.c_str());
}

MenuButton::~MenuButton(void) {
	// destroying font
	al_destroy_font(font);
}