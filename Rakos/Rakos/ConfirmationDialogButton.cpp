#include "ConfirmationDialogButton.h"
#include "RPG.h"

ConfirmationDialogButton::ConfirmationDialogButton(string Label, unsigned int CenterX, unsigned int CenterY, unsigned int Width, unsigned int Height, unsigned int FontSize) {
	// default active value
	active = true;

	// setting button label
	label = Label;

	// setting button coordinates
	x = CenterX - Width/2.0;
	y = CenterY - Height/2.0;


	// setting button width and height
	width = Width;
	height = Height;


	// if font = 0, user did not specify font size, so use one according to the button height
	if (FontSize == 0)
		font = al_load_font(CalibriTTF, Height - 15, ALLEGRO_ALIGN_CENTER);
	else
		font = al_load_font(CalibriTTF, FontSize, ALLEGRO_ALIGN_CENTER);

	// checking if font was loaded correctly:
	if (!font) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load font file.", "Have you included the resources in the same directory of the program?", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}


	// initializing bool values
	beingHovered = false;
	beingPressed = false;
	released = false;
}

void ConfirmationDialogButton::Draw() {
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
	al_draw_filled_rectangle(x+RPG::GetInstance()->cameraPosition[0], y+RPG::GetInstance()->cameraPosition[1], x+RPG::GetInstance()->cameraPosition[0]+width, y+RPG::GetInstance()->cameraPosition[1]+height, buttonColor);

	// drawing button contour
	al_draw_rectangle(x+RPG::GetInstance()->cameraPosition[0], y+RPG::GetInstance()->cameraPosition[1], x+RPG::GetInstance()->cameraPosition[0]+width, y+RPG::GetInstance()->cameraPosition[1]+height, Black, 1.0);

	// printing label
	al_draw_text(font, Black, x+RPG::GetInstance()->cameraPosition[0] + width/2, y+RPG::GetInstance()->cameraPosition[1] + 0.025*font->height, ALLEGRO_ALIGN_CENTER, label.c_str());
}

ConfirmationDialogButton::~ConfirmationDialogButton( void ) {
	// nothing to do here?
}