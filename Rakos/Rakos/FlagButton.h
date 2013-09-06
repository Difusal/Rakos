#pragma once

#include "BasicButton.h"

class FlagButton: public BasicButton {
public:
	FlagButton(string Label, const char *FlagBitmapPath, unsigned int CenterX, unsigned int CenterY, unsigned int Width, unsigned int Height);
	void Draw();
	~FlagButton(void);

private:
	ALLEGRO_BITMAP *flag;
};