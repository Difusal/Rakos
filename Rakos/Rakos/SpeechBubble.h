#pragma once

#include "stdIncludes.h"
#include "globalEnums.h"

class SpeechBubble {
public:
	SpeechBubble(unsigned int *BeingX, unsigned int *BeingY, vector<string> Text);

	void Show() { showing = true; }
	void Hide() { showing = false; }
	void Draw();

	~SpeechBubble(void);

private:
	bool showing;
	int cornersRadius;
	unsigned int bubbleX, bubbleY;
	unsigned int shadowX, shadowY;
	unsigned int p1x, p1y, p2x, p2y, p3x, p3y;

	int width, height;
	unsigned int *x, *y;

	vector<string> text;
	ALLEGRO_FONT *font;
};