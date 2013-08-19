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
	height = font->height - 0.2*font->height;

	// setting button coords
	switch (Position) {
	case _Left:
		x = sideBarWidth/2.0 - sideBarWidth/2.0/2.0;
		break;
	case _Center:
		x = sideBarWidth/2.0;
		break;
	case _Right:
		x = sideBarWidth/2.0 + sideBarWidth/2.0/2.0;
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
}

void Button::Draw() {
	// drawing button background
	al_draw_filled_rectangle(realX - width/2.0, realY, realX + width/2.0, realY + height, White);
	al_draw_rectangle(realX - width/2.0, realY, realX + width/2.0, realY + height, DarkGray, 1.0);

	// printing label
	al_draw_text(font, Black, realX, realY, ALLEGRO_ALIGN_CENTER, label.c_str());
}


Button::~Button( void ) {

}