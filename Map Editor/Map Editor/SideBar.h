#pragma once

#include "stdIncludes.h"
#include "Button.h"
#include "SideBarTileSet.h"

class SideBar {
public:
	SideBar(ALLEGRO_BITMAP **tileSet, unsigned int numberOfTiles);

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

	bool displayingTilesNotMobs;
	bool dragging;

	SideBarTileSet *tileSet;

	unsigned int spaceBetweenButtons;
	vector<Button*> buttons;
	Button *Tiles;
	Button *Mobs;
	Button *PreviousPage;
	Button *NextPage;
	Button *EditMap;
	Button *DragMap;
	Button *IncreaseMapWidth;
	Button *IncreaseMapHeight;
	Button *Save;
	Button *Quit;
};