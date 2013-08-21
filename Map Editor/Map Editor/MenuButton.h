#pragma once

#include "stdIncludes.h"

class MenuButton {
public:
	MenuButton(string Label, unsigned int Y);

	void Update();
	void Draw();

	unsigned int Height() { return height; }
	bool wasPressed() { return released; }

	~MenuButton(void);

private:
	string label;
	unsigned int x, y;
	unsigned int width, height;

	ALLEGRO_FONT *font;
	bool beingHovered;
	bool released;
};