#pragma once

#include "stdIncludes.h"
#include "Player.h"

class Portal {
public:
	Portal(bool alreadyOpened, int sourceBlockX, int sourceBlockY, int destinyBlockX, int destinyBlockY);

	void Open();
	void Close();
	void CheckIfPlayerPassedThrough(Player *player);
	void UpdateAnimationFrame();
	void Draw();

	bool isOpen() { return open; }

	~Portal(void);

private:
	bool open, opening;
	int sourceX, sourceY;
	int destinyX, destinyY;

	double openingSpeed;
	double regularSpeed;

	ALLEGRO_BITMAP *bitmap;
	int bitmap_sourceX;
};