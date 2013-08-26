#pragma once

#include "stdIncludes.h"
#include "Player.h"

class BasicPortal {
public:
	BasicPortal(bool alreadyOpened, int sourceBlockX, int sourceBlockY);

	void Open();
	void Close();
	bool PassedThrough(Player *player);
	void UpdateAnimationFrame();
	void Draw();

	bool isOpen() { return open; }

	~BasicPortal(void);

private:
	bool open, opening;
	int sourceX, sourceY;

	double openingSpeed;
	double regularSpeed;

	ALLEGRO_BITMAP *bitmap;
	int bitmap_sourceX;
};