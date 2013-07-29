#pragma once

#include "stdIncludes.h"

class LivingBeing
{
public:
	LivingBeing(void);
	~LivingBeing(void);

	int getType() { return type; }
	void setType(LivingBeingType Type) { type = Type; }

	string getName() { return name; }
	void setName(string Name) { name = Name; }


	bool isDead() { return dead; }
	void setDeadState(bool Dead) { dead = Dead; }

	bool getActiveState() { return active; }
	void setActiveState(bool newState) { active = newState; }

	int getHP() { return hp; }
	void setHP(int HP) { hp = HP; }
	int getMaxHP() { return maxHp; }
	void setMaxHP(int MaxHP) { maxHp = MaxHP; }

	double getX() { return x; }
	double getY() { return y; }
	void setX(double X) { x = X; }
	void setY(double Y) { y = Y; }

	int getDir() { return direction; }
	void setDir(Direction Direction) { direction = Direction; }

	double getMoveSpeed() { return moveSpeed; }
	void setMoveSpeed(double newSpeed) { moveSpeed = newSpeed; }


	ALLEGRO_BITMAP *getBitmap() { return bitmap; }
	void setBitmap(ALLEGRO_BITMAP *Bitmap) { bitmap = Bitmap; }
	int getBitmapSourceX() { return bitmap_sourceX; }
	int getBitmapSourceY() { return bitmap_sourceY; }
	void setBitmapSourceX(int X) { bitmap_sourceX = X; }
	void setBitmapSourceY(int Y) { bitmap_sourceY = Y; }

private:
	LivingBeingType type;
	string name;

	unsigned int hp;
	unsigned int maxHp;

	bool dead;
	bool active;

	double x, y;
	Direction direction;
	double moveSpeed;

	ALLEGRO_BITMAP * bitmap;
	int bitmap_sourceX, bitmap_sourceY;

	friend class Player;
	friend class NPC;
	friend class Rabbit;
};