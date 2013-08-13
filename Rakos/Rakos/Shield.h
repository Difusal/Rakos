#pragma once

#include "stdIncludes.h"
#include "globalEnums.h"

class Shield {
public:
	Shield(ShieldType Type, unsigned int Defense);

	void UpdatePosition(Direction direction, int frame, double x, double y);
	void Draw();

	string getName() { return name; }
	unsigned int getDefense() { return defense; }
	ALLEGRO_BITMAP *getThumbnail() { return thumbnail; }

	~Shield(void);

private:
	ShieldType type;
	string name;

	unsigned int defense;

	int x, y;
	int xCorrection, yCorrection;
	Direction direction;

	ALLEGRO_BITMAP *thumbnail;
	ALLEGRO_BITMAP *sprite;
	int spriteX1, spriteY1, width, height;
};