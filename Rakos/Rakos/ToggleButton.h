#pragma once

#include "BasicButton.h"

class ToggleButton: public BasicButton {
public:
	ToggleButton(const char *BitmapPath, unsigned int CenterX, unsigned int CenterY);
	void Draw();
	~ToggleButton(void);

private:
	ALLEGRO_BITMAP *image;
};