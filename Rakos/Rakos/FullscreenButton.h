#pragma once

#include "BasicButton.h"

class FullscreenButton: public BasicButton {
public:
	FullscreenButton(const char *BitmapPath, unsigned int CenterX, unsigned int CenterY);
	void PositionOnUpperRightCorner();
	void Draw();
	~FullscreenButton(void);

private:
	ALLEGRO_BITMAP *image;
};