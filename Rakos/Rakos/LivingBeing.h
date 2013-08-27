#pragma once

#include "stdIncludes.h"
#include "globalEnums.h"
#include "SpeechBubble.h"
#include "Weapon.h"
#include "Shield.h"

class LivingBeing {
public:
	void Move();
	void UpdateAnimationFrame();
	void Draw();
	void DrawName();
	void DrawLifeBar();
	void DrawBeing();

	LivingBeingType getType() { return type; }
	void setType(LivingBeingType Type) { type = Type; }

	TimerType getTimerType() { return timer; }

	string getName() { return name; }
	void setName(string Name) { name = Name; }

	Weapon *GetWeapon() { return weapon; }
	Shield *GetShield() { return shield; }

	unsigned int GetAmountOfGold() { return gold; }
	void addGold(unsigned int GoldAmount) { gold += GoldAmount; }

	unsigned int GetExperience() { return experience; }

	bool isDead() { return dead; }
	void setDeadState(bool Dead) { dead = Dead; }

	bool isActive() { return active; }
	void Activate() { active = true; }
	void Deactivate() { active = false; }

	bool isSpeaking() { return speaking; }
	void Speak();
	void StopSpeaking();

	void takeHP(unsigned int HPAmount) { hp -= HPAmount; }
	int getHP() { return hp; }
	void setHP(int HP) { hp = HP; }
	int getMaxHP() { return maxHp; }
	void setMaxHP(int MaxHP) { maxHp = MaxHP; }

	void incX() { x++; }
	void incY() { y++; }
	void decX() { x--; }
	void decY() { y--; }

	unsigned int *getAddressOfX() { return &x; }
	unsigned int *getAddressOfY() { return &y; }

	double getX() { return x; }
	double getY() { return y; }
	void setX(double X) { x = X; }
	void setY(double Y) { y = Y; }

	double getFeetX() { return feet_x; }
	double getFeetY() { return feet_y; }

	Direction getDir() { return direction; }
	void setDir(Direction Direction) { direction = Direction; }

	double getWanderRadius() { return wanderRadius; }
	void setWanderRadius(double Radius) { wanderRadius = Radius; }

	int width() { return al_get_bitmap_width(bitmap)/4.0; }
	int height() { return al_get_bitmap_height(bitmap)/4.0; }
	int rightBorderX() { return x + width() - xCollisionCorrection; }
	int bottomBorderY() { return y + height() - yCollisionCorrection; }

	int getCurrentFrame();

	// public variables
	vector<SpeechBubble*> speechBubbles;

private:
	LivingBeingType type;
	TimerType timer;
	string name;
	Weapon *weapon;
	Shield *shield;
	unsigned int gold;
	unsigned int experience;

	bool dead;
	bool active;
	bool alwaysInactive;
	bool speaking;

	unsigned int hp;
	unsigned int maxHp;

	unsigned int centerX, centerY;
	unsigned int wanderRadius;

	unsigned int x, y;
	unsigned int feet_x, feet_y;
	Direction direction;

	ALLEGRO_BITMAP *bitmap;
	int bitmap_sourceX, bitmap_sourceY;

	friend class Player;
	friend class NPC;
	friend class Rabbit;
	friend class Weapon;
	friend class CreatureWindowObject;
};