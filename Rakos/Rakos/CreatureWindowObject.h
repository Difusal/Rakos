#pragma once

#include "stdIncludes.h"
#include "LivingBeing.h"

class CreatureWindowObject {
public:
	CreatureWindowObject();

	void Activate(LivingBeing *being);
	void Deactivate() { active = false; }

	void Update(unsigned int x, unsigned int y);
	void Draw();

	void DrawBar(unsigned int barY, unsigned int currentValue, unsigned int maxValue, ALLEGRO_COLOR fillColor);

	~CreatureWindowObject(void);

private:
	bool active;
	unsigned int x, y;
	unsigned int width, height;

	unsigned int thumbnailX, thumbnailY;
	unsigned int thumbnailSize;

	string label;
	unsigned int labelX, labelY;

	ALLEGRO_COLOR barFillColor;
	unsigned int barX, barY;
	unsigned int barCenterX;
	unsigned int barWidth, barHeight;

	ALLEGRO_BITMAP *sprite;
	unsigned int *HP, *maxHP;

	ALLEGRO_FONT *font;
};