#pragma once

#include "stdIncludes.h"
#include "BasicButton.h"

class ConfirmationDialog {
public:
	ConfirmationDialog(string Title, vector<string> Text);

	int Update();
	void Draw();

	void Open() { active = true; }
	void Close() { active = false; }

	~ConfirmationDialog(void);

private:
	bool active;

	int width, height;
	int x, y;
	int realX, realY;

	unsigned int buttonsWidth;
	unsigned int spaceBetweenButtons;
	BasicButton *Yes, *No;

	string title;
	vector<string> text;
	ALLEGRO_FONT *font;
};