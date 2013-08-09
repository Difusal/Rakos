#include "TextBox.h"
#include "RPG.h"
#include "globalFunctions.h"

TextBox::TextBox(Alignment Position, vector<string> Text) {
	showing = false;
	text = Text;
	font = RPG::GetInstance()->medium_font;

	height = (Text.size() + 1) * font->height;
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
	unsigned int lol = 128;
	ALLEGRO_COLOR backgroundColor = al_map_rgba(lol*alpha, lol*alpha, lol*alpha, alpha);

	// box background
	al_draw_filled_rectangle(destX, destY, destX + width, destY + height, backgroundColor);

	// box frame
	al_draw_rectangle(destX, destY, destX + width, destY + height, Black, 1.0);

	// text
	for (unsigned int i = 0; i < text.size(); i++)
		al_draw_text(font, White, destX + width/2, destY + i*font->height + 1 + font->height/2, ALLEGRO_ALIGN_CENTER, text[i].c_str());
}


TextBox::~TextBox(void) {
}