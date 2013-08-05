#pragma once

#include "stdIncludes.h"
#include "Player.h"

class Switch {
public:
	Switch(int x, int y, int unpressDelay);

	void Press();
	void Unpress();
	bool isBeingPressed(Player *player);
	void incrementUnpressDelayCounter() { unpressDelayCounter++; }
	bool unpressDelayPassed();
	void Draw();

	bool isPressed() { return pressed; }

	~Switch(void);

private:
	int x, y;

	int unpressDelay;
	int unpressDelayCounter;

	bool pressed;

	ALLEGRO_BITMAP *bitmap;
};