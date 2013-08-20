#pragma once

#include "stdIncludes.h"

class TileSetButton;

class SideBarTileSet {
public:
	SideBarTileSet(ALLEGRO_BITMAP **tileSet, unsigned int numberOfTiles, unsigned int *sideBarX, unsigned int *sideBarY);

	void Update(unsigned int sideBarWidth, unsigned int tileSetY, bool &dragging);
	void Draw();

	void CheckIfAnyTileIsSelected();
	void SetSelectedTile(int Tile) { selectedTile = Tile; }
	void UnlockAnySelectedTile();
	
	void GoToNextPage();
	void GoToPrevPage();

	int GetSelectedTile() { return selectedTile; }
	unsigned int GetCurrentPage() { return pageToDisplay; }
	unsigned int GetTotalPages() { return totalPages; }

	~SideBarTileSet();

private:
	int selectedTile;
	ALLEGRO_BITMAP **tileSet;
	vector<TileSetButton*> tiles;

	unsigned int *sideBarX, *sideBarY;

	unsigned int pageToDisplay;
	unsigned int totalPages;
};

class TileSetButton {
public:
	TileSetButton(unsigned int TileID);

	void Update(SideBarTileSet *ThisThis, unsigned int sideBarX, unsigned int sideBarY, bool &dragging);
	void Draw(ALLEGRO_BITMAP **tileSet);
	void DrawLockedTile();

	void SetCoords(unsigned int X, unsigned int Y) { x = X; y = Y; }
	void Unlock() { locked = false; }

	unsigned int ID() { return tileID; }
	unsigned int Width() { return width; }

	bool isLocked() { return locked; }
	bool wasPressed() { return released; }

	~TileSetButton();

private:
	unsigned int tileID;

	unsigned int x, y;
	unsigned int realX, realY;
	unsigned int width, height;

	bool beingHovered;
	bool released;
	bool locked;
};