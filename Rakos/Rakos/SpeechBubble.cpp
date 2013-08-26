#include "SpeechBubble.h"
#include "RPG.h"
#include "globalFunctions.h"

SpeechBubble::SpeechBubble(unsigned int *BeingX, unsigned int *BeingY, vector<string> Text) {
	showing = false;
	cornersRadius = 10;

	text = Text;
	font = al_load_font(CalibriTTF, 16, ALLEGRO_ALIGN_CENTER);
	if (!font) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not create a game text box.\nThe font file being used was not found.", "Your resources folder must be corrupt.\nPlease download the game again.\n\nPress OK to close the game.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	// x and y are pointers to the being current position
	x = BeingX;
	y = BeingY;

	width = (getLengthOfBiggestSentenceOnVector(text)+1) * font->height/2.7;
	height = (text.size() + 1) * font->height;
}

void SpeechBubble::Draw() {
	// skipping if not supposed to draw dialog
	if (!showing)
		return;

	int beingWidth = RPG::GetInstance()->GetPlayer()->width();

	bubbleX = *x - width/3.0 + beingWidth/2.0;
	bubbleY = *y - height - 10;
	shadowX = bubbleX-4;
	shadowY = bubbleY+5;
	p1x = *x+beingWidth*3/4.0 + 3;
	p1y = bubbleY+height;
	p2x = *x+beingWidth*3/4.0 + 19;
	p2y = bubbleY+height;
	p3x = *x+beingWidth*3/4.0;
	p3y = *y+8;

	unsigned int alpha = 100;
	unsigned int rgb = 128;
	ALLEGRO_COLOR shadowColor = al_map_rgba(rgb*alpha, rgb*alpha, rgb*alpha, alpha);

	// shadow
	al_draw_filled_triangle(p1x-4, p1y+5, p2x-4, p2y+5, p3x-4, p3y+5, shadowColor);
	al_draw_filled_rounded_rectangle(shadowX, shadowY, shadowX+width, shadowY+height, cornersRadius, cornersRadius, shadowColor);

	// bubble frame
	al_draw_filled_triangle(p1x-1, p1y, p2x-1, p2y, p3x-1, p3y, Black);
	al_draw_filled_triangle(p1x, p1y+1, p2x, p2y+1, p3x, p3y+1, Black);
	al_draw_filled_rounded_rectangle(bubbleX-1, bubbleY-1, bubbleX+1+width, bubbleY+1+height, cornersRadius, cornersRadius, Black);

	// white background
	al_draw_filled_triangle(p1x, p1y, p2x, p2y, p3x, p3y, White);
	al_draw_filled_rounded_rectangle(bubbleX, bubbleY, bubbleX+width, bubbleY+height, cornersRadius, cornersRadius, White);

	// text
	for (unsigned int i = 0; i < text.size(); i++)
		al_draw_text(font, Black, bubbleX + width/2, bubbleY + i*font->height + 2 + font->height/2, ALLEGRO_ALIGN_CENTER, text[i].c_str());
}

SpeechBubble::~SpeechBubble(void) {
	al_destroy_font(font);
}