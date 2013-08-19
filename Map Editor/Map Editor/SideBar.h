#pragma once

#include "stdIncludes.h"
#include "Button.h"

class SideBar {
public:
	SideBar(void);

	void InitializeButtons();

	void Update();
	void Draw();

	unsigned int X() { return x; }
	unsigned int Y() { return y; }
	unsigned int Width() { return width; }
	unsigned int Height() { return height; }

	bool DraggingIsEnabled() { return dragging; }

	~SideBar(void);

private:
	unsigned int x, y;
	unsigned int width, height;

	bool dragging;

	vector<Button*> buttons;
	Button *Tiles;
	Button *Creatures;
	Button *PreviousPage;
	Button *NextPage;
	Button *EditMap;
	Button *DragMap;
	Button *IncreaseMapWidth;
	Button *IncreaseMapHeight;
	Button *Save;
	Button *Quit;
};