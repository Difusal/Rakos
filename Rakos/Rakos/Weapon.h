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

	WeaponType getType() { return type; }
	string getName() { return name; }
	int getDamage();
	ALLEGRO_BITMAP *getThumbnail() { return thumbnail; }
	bool animationIsPlaying() { return playingAnimation; };

	~Weapon(void);

private:
	WeaponType type;
	string name;

	int min_attack;
	int max_attack;

	int x, y;
	int xCorrection, yCorrection;
	Direction direction;

	ALLEGRO_BITMAP *thumbnail;
	ALLEGRO_BITMAP *sprite;
	int spriteX1, spriteY1, width, height;
	bool startPlayingAnimation;
	bool playingAnimation;
	int frame;
};