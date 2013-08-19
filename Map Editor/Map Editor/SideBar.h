#pragma once

#include "stdIncludes.h"
#include "Button.h"

class SideBar {
public:
	SideBar(void);

	void Update();
	void Draw();

	unsigned int X() { return x; }
	unsigned int Y() { return y; }
	unsigned int Width() { return width; }
	unsigned int Height() { return height; }

	~SideBar(void);

private:
	unsigned int x, y;
	unsigned int width, height;

	vector<Button*> buttons;
	Button *Save;
	Button *Quit;
};