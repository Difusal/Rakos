#pragma once

#include "stdIncludes.h"
#include "globalEnums.h"

class Weapon {
public:
	Weapon(WeaponType Type, int minAttack, int maxAttack);

	void UpdatePosition(Direction direction, int frame, double x, double y);
	void PlayAttackAnim();
	void UpdateAttackAnimation();
	void Draw();
	void DrawAttackAnim();

	string getName() { return name; }
	int getDamage();
	bool animationIsPlaying() { return playingAnimation; };

	~Weapon(void);

private:
	WeaponType type;
	string name;

	int min_attack;
	int max_attack;

	int x, y;
	Direction direction;

	ALLEGRO_BITMAP *bitmap;
	ALLEGRO_BITMAP *sprite;
	int spriteX1, spriteY1, spriteX2, spriteY2;
	bool playingAnimation;
	int frame;
};