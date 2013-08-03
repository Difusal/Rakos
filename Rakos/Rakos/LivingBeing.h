#pragma once

#include "stdIncludes.h"
#include "globalEnums.h"

class LivingBeing {
public:
	void Move();
	void UpdateAnimationFrame();
	void Draw();
	void DrawName();
	void DrawLifeBar();

	int getType() { return type; }
	void setType(LivingBeingType Type) { type = Type; }
	string getName() { return name; }
	void setName(string Name) { name = Name; }
	
	bool isDead() { return dead; }
	void setDeadState(bool Dead) { dead = Dead; }
	bool getActiveState() { return active; }
	void setActiveState(bool newState) { active = newState; }

	void takeHP(unsigned int HPAmount) { hp -= HPAmount; }
	int getHP() { return hp; }
	void setHP(int HP) { hp = HP; }
	int getMaxHP() { return maxHp; }
	void setMaxHP(int MaxHP) { maxHp = MaxHP; }

	double getX() { return x; }
	void setX(double X) { x = X; }
	double getY() { return y; }
	void setY(double Y) { y = Y; }
	int getDir() { return direction; }
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

private:
	LivingBeingType type;
	string name;

	bool dead;
	bool active;

	unsigned int hp;
	unsigned int maxHp;

	double wanderRadius;
	double p1_x, p1_y;
	double p2_x, p2_y;

	double x, y;
	Direction direction;
	double moveSpeed;
	
	ALLEGRO_BITMAP *bitmap;
	int bitmap_sourceX, bitmap_sourceY;

	friend class Player;
	friend class NPC;
	friend class Rabbit;
};