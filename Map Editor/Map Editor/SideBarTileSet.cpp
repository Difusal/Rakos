#include "SideBarTileSet.h"
#include "Editor.h"

// TileSetButton Class Method Implementations
TileSetButton::TileSetButton(unsigned int TileID) {
	// note: x and y should be updated automatically

	width = 40;
	height = 40;

	tileID = TileID;

	// initializing bool values
	beingHovered = false;
	released = false;
	locked = false;
}


void TileSetButton::Update(SideBarTileSet *ThisThis, unsigned int sideBarX, unsigned int sideBarY, bool &dragging) {
	realX = x + sideBarX;
	realY = y + sideBarY;

	// setting bool variables to their default value
	beingHovered = false;
	released = false;

	// checking if button is being hovered
	if (realX-width/2.0 < Editor::GetInstance()->Mouse->x && Editor::GetInstance()->Mouse->x < realX+width/2.0 &&
		realY < Editor::GetInstance()->Mouse->y && Editor::GetInstance()->Mouse->y < realY+height) {
			beingHovered = true;

			// checking if button was pressed
			if (Editor::GetInstance()->Mouse->leftMouseButtonReleased) {
				cout << "Tile selected." << endl;
				released = true;

				// if tile pressed and not locked, lock it. else, unlock it.
				if (!locked) {
					ThisThis->UnlockAnySelectedTile();
					locked = true;
				}
				else
					locked = false;

				// enabling edit mode if dragging mode was being used
				dragging = false;
			}
	}
	else
		beingHovered = false;
}

void TileSetButton::Draw(ALLEGRO_BITMAP **tileSet) {
	// drawing button background
	al_draw_filled_rectangle(realX - width/2.0, realY, realX + width/2.0, realY + height, Gray);

	// drawing tile from bitmap
	al_draw_bitmap_region(*tileSet, tileID*WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, realX-width/2.0, realY, ALLEGRO_ALIGN_LEFT);

	// if button is being hovered use a different contour color
	ALLEGRO_COLOR tileContour;
	switch (beingHovered) {
	case false:
		tileContour = DarkerGray;
		break;
	case true:
		tileContour = Blue;
		break;
	}
	// drawing button contour
	al_draw_rectangle(realX - width/2.0, realY, realX + width/2.0, realY + height, tileContour, 1.0);

	if (locked)
		DrawLockedTile();
}

void TileSetButton::DrawLockedTile() {
	// drawing different button contour
	al_draw_rectangle(realX - width/2.0, realY, realX + width/2.0, realY + height, Yellow, 1.0);
}

TileSetButton::~TileSetButton() {
	// nothing to do here
}


// SideBarTileSet Class Method Implementations
SideBarTileSet::SideBarTileSet(ALLEGRO_BITMAP **tileSet, unsigned int numberOfTiles, unsigned int *sideBarX, unsigned int *sideBarY) {
	this->tileSet = tileSet;

	// tile selected = no tile selected (-1)
	selectedTile = -1;

	// creating vector of available tiles
	for (unsigned int i = 0; i < numberOfTiles; i++)
		tiles.push_back(new TileSetButton(i));

	// saving pointers to sideBar coords
	this->sideBarX = sideBarX;
	this->sideBarY = sideBarY;

	// setting default display page
	pageToDisplay = 1;
}


void SideBarTileSet::Update(unsigned int sideBarWidth, unsigned int tileSetY, bool &dragging) {
	unsigned int buttonX;
	for (unsigned int i = 0; i < tiles.size() && i < 16; i++) {
		// simple math to align button on x axis
		buttonX = sideBarWidth/2.0 + pow(-1, i%2+1)*(sideBarWidth/2.0 - 5)/2.0;

		// setting button new coords
		tiles[i]->SetCoords(buttonX, tileSetY + (i/2)*(tiles[i]->Width()+10));
	}

	// updating tiles real coords based on side bar current position
	for (unsigned int i = 0; i < tiles.size(); i++) {
		tiles[i]->Update(this, *sideBarX, *sideBarY, dragging);
	}

	// checking if there is any tile selected
	if (!dragging)
		CheckIfAnyTileIsSelected();
}

void SideBarTileSet::Draw() {
	for (unsigned int i = 0; i < tiles.size() || i < 6; i++) {
		tiles[i]->Draw(tileSet);
	}
}


void SideBarTileSet::CheckIfAnyTileIsSelected() {
	for (unsigned int i = 0; i < tiles.size(); i++)
		if (tiles[i]->isLocked())
			SetSelectedTile(i);
}

void SideBarTileSet::UnlockAnySelectedTile() {
	SetSelectedTile(-1);

	for (TileSetButton *obj: tiles)
		obj->Unlock();
}


SideBarTileSet::~SideBarTileSet() {
	al_destroy_bitmap(*tileSet);

	for (TileSetButton *obj: tiles)
		delete obj;
	tiles.clear();

	delete sideBarX, sideBarY;
}