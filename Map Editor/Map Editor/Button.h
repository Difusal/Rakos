#pragma once

#include "stdIncludes.h"
#include "globalEnums.h"

class Button {
public:
	Button(string Label, unsigned int Y, ButtonPosition Position, unsigned int sideBarWidth);

	void Update(unsigned int sideBarX, unsigned int sideBarY);
	void Draw();

	~Button(void);

private:
	string label;
	unsigned int x, y;
	unsigned int realX, realY;
	unsigned int width, height;
	
	ALLEGRO_FONT *font;
	bool beingHovered;
	bool released;
};