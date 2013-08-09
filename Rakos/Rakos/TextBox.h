#pragma once

#include "stdIncludes.h"
#include "globalEnums.h"

class TextBox {
public:
	TextBox(Alignment Position, vector<string> Text);

	void Show() { showing = true; }
	void Hide() { showing = false; }
	void Draw();

	~TextBox(void);

private:
	bool showing;
	int width, height;
	int x, y;

	vector<string> text;
	ALLEGRO_FONT *font;
};