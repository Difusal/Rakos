#include "TextBox.h"
#include "RPG.h"
#include "globalFunctions.h"

TextBox::TextBox(Alignment Position, vector<string> Text) {
	showing = false;

	text = Text;
	font = al_load_font(CalibriTTF, 20, ALLEGRO_ALIGN_CENTER);
	if (!font) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not create a game text box.\nThe font file being used was not found.", "Your resources folder must be corrupt.\nPlease download the game again.\n\nPress OK to close the game.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	height = (text.size() + 1) * font->height;
	switch (Position) {
	case _Center:
		width = (getLengthOfBiggestSentenceOnVector(text)+1) * font->height/2.5;
		x = 600/2 - width/2;
		y = ScreenHeight/2 - height/2;
		break;
	case _Bottom:
		width = 600;
		x = 1;
		y = ScreenHeight - height;
		break;
	}
}


void TextBox::Draw() {
	// skipping if not supposed to draw dialog
	if (!showing)
		return;

	int destX = x + RPG::GetInstance()->cameraPosition[0];
	int destY = y + RPG::GetInstance()->cameraPosition[1];

	unsigned int alpha = 190;
	unsigned int rgb = 128;
	ALLEGRO_COLOR backgroundColor = al_map_rgba(rgb*alpha, rgb*alpha, rgb*alpha, alpha);

	// box background
	al_draw_filled_rectangle(destX, destY, destX + width, destY + height, backgroundColor);
	
	// box frame
	/*
	// --------------
	// Optional code:
	// Uncomment this block of code to draw a more complex frame
	// ---------------------------------------------------------
	al_draw_rectangle(destX+3, destY+3, destX+width-3, destY+height-3, DarkGray, 1.0);
	al_draw_rectangle(destX+2, destY+2, destX+width-2, destY+height-2, Gray, 1.0);
	al_draw_rectangle(destX+1, destY+1, destX+width-1, destY+height-1, LightGray, 1.0);
	*/
	al_draw_rectangle(destX, destY, destX+width, destY+height, Black, 1.0);

	// text
	for (unsigned int i = 0; i < text.size(); i++)
		al_draw_text(font, White, destX + width/2, destY + i*font->height + 1 + font->height/2, ALLEGRO_ALIGN_CENTER, text[i].c_str());
}


TextBox::~TextBox(void) {
	al_destroy_font(font);
}