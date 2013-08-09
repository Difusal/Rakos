#pragma once

#include "stdIncludes.h"
#include "globalEnums.h"

class TextBox {
public:
	TextBox(Alignment Position, vector<string> Text);

	void Draw();

	~TextBox(void);

private:
	int x, y;
	int width, height;

	vector<string> text;
	ALLEGRO_FONT *font;
};