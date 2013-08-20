#pragma once

#include "stdIncludes.h"
#include "state.h"

#include "SideBar.h"

class EditingState: public State {
public:
	virtual void Initialize();
	virtual bool Update(ALLEGRO_EVENT *ev);
	virtual void Draw();
	virtual void Terminate();

private:
	ALLEGRO_BITMAP *tileSet;
	vector<vector<int> > worldMap;
	unsigned int numberOfTiles;

	bool drawSelectedTile;
	unsigned int selectedTileX, selectedTileY;

	double cameraCenterX;
	double cameraCenterY;

	SideBar *sideBar;
};