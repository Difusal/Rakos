#pragma once

#include "stdIncludes.h"

class Form {
public:
	Form(string Label, unsigned int x, unsigned int y, bool HideText = false);
	void Update(ALLEGRO_EVENT *ev);
	void Draw();
	~Form(void);

	unsigned int Width() { return width; }
	unsigned int Height() { return height; }

	unsigned int YStartPos() { return y; }
	unsigned int YEndPos() { return y+height; }

private:
	unsigned int x, y;
	unsigned int width, height;

	bool active;
	bool hideCharacters;

	ALLEGRO_USTR *label;
	ALLEGRO_USTR *text;
	unsigned int textX,textY;

	ALLEGRO_FONT *font;
	ALLEGRO_KEYBOARD_STATE keyboardState;
};