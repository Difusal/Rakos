#pragma once

#include "stdIncludes.h"
#include "RPG.h"

class LivingBeing {
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


	double getP1_x() { return p1_x; }
	double getP1_y() { return p1_y; }
	double getP2_x() { return p2_x; }
	double getP2_y() { return p2_y; }
	void setP1_x(double x) { p1_x = x; }
	void setP1_y(double y) { p1_y = y; }
	void setP2_x(double x) { p2_x = x; }
	void setP2_y(double y) { p2_y = y; }


	ALLEGRO_BITMAP *getBitmap() { return bitmap; }
	void setBitmap(ALLEGRO_BITMAP *Bitmap) { bitmap = Bitmap; }
	int getBitmapSourceX() { return bitmap_sourceX; }
	int getBitmapSourceY() { return bitmap_sourceY; }
	void setBitmapSourceX(int X) { bitmap_sourceX = X; }
	void setBitmapSourceY(int Y) { bitmap_sourceY = Y; }

private:
	double p1_x, p1_y;
	double p2_x, p2_y;

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