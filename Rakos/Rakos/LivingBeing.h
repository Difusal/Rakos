#pragma once

#include "stdIncludes.h"
#include "globalEnums.h"
#include "Weapon.h"

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
	string getName() { return name; }
	void setName(string Name) { name = Name; }
	Weapon *getWeapon() { return weapon; }
	
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

	double getX() { return x; }
	void setX(double X) { x = X; }
	double getY() { return y; }
	void setY(double Y) { y = Y; }
	Direction getDir() { return direction; }
	void setDir(Direction Direction) { direction = Direction; }
	double getMoveSpeed() { return moveSpeed; }
	void setMoveSpeed(double newSpeed) { moveSpeed = newSpeed; }

	double getWanderRadius() { return wanderRadius; }
	void setWanderRadius(double Radius) { wanderRadius = Radius; }
	double getP1_x() { return p1_x; }
	void setP1_x(double x) { p1_x = x; }
	double getP1_y() { return p1_y; }
	void setP1_y(double y) { p1_y = y; }
	double getP2_x() { return p2_x; }
	void setP2_x(double x) { p2_x = x; }
	double getP2_y() { return p2_y; }
	void setP2_y(double y) { p2_y = y; }

	int width() { return al_get_bitmap_width(bitmap)/4.0; }
	int height() { return al_get_bitmap_height(bitmap)/4.0; }
	int rightBorderX() { return x + width() - xCollisionCorrection; }
	int bottomBorderY() { return y + height() - yCollisionCorrection; }

	int getCurrentFrame();

private:
	LivingBeingType type;
	string name;
	Weapon *weapon;

	bool dead;
	bool active;
	bool alwaysInactive;
	bool speaking;

	unsigned int hp;
	unsigned int maxHp;

	unsigned int wanderRadius;
	unsigned int p1_x, p1_y;
	unsigned int p2_x, p2_y;

	unsigned int x, y;
	Direction direction;

	ALLEGRO_BITMAP *bitmap;
	int bitmap_sourceX, bitmap_sourceY;

	friend class Player;
	friend class NPC;
	friend class Rabbit;
	friend class Weapon;
};