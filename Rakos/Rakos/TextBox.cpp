#include "TextBox.h"
#include "RPG.h"

TextBox::TextBox(Alignment Position, vector<string> Text) {
	switch (Position) {
	case Center:
		break;
	case Bottom:
		width = 600;
		height = (Text.size() + 1) * RPG::GetInstance()->medium_font->height;
		x = 1;
		y = ScreenHeight - height;
		break;
	}

	text = Text;
	font = RPG::GetInstance()->medium_font;
}


void TextBox::Draw() {
	int destX = x + RPG::GetInstance()->cameraPosition[0];
	int destY = y + RPG::GetInstance()->cameraPosition[1];

	unsigned int alpha = 180;
	unsigned int lol = 128;
	ALLEGRO_COLOR backgroundColor = al_map_rgba(lol*alpha, lol*alpha, lol*alpha, alpha);

	// box background
	al_draw_filled_rectangle(destX, destY, destX + width, destY + height, backgroundColor);

	// box frame
	al_draw_rectangle(destX, destY, destX + width, destY + height, Black, 1.0);

	al_draw_text(font, White, 100 + RPG::GetInstance()->cameraPosition[0], 500 + RPG::GetInstance()->cameraPosition[1], NULL, "TESTE");
	// text
	for (unsigned int i = 0; i < text.size(); i++)
		al_draw_text(font, White, destX + width/2, destY + i*font->height + 1 + font->height/2, ALLEGRO_ALIGN_CENTER, text[i].c_str());
}


TextBox::~TextBox(void) {
}