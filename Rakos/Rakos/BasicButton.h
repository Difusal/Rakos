#pragma once

#include "stdIncludes.h"

class BasicButton {
public:
	BasicButton(string Label, unsigned int X, unsigned int Y, unsigned int Width);

	void Update(unsigned int referencePointX, unsigned int referencePointY);
	void Draw(ALLEGRO_COLOR ButtonColor = White, ALLEGRO_COLOR ButtonColorWhenBeingHovered = LightBlue);

	unsigned int Height() { return height; }
	bool wasPressed() { return released; }

	~BasicButton(void);

private:
	string label;
	unsigned int x, y;
	unsigned int realX, realY;
	unsigned int width, height;

	ALLEGRO_FONT *font;
	bool beingHovered;
	bool released;
};