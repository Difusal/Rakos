#pragma once

#include "stdIncludes.h"

class MovingObject
{
public:
	MovingObject(void);

	int getType() { return type; }
	void setType(int Type) { type = Type; }

	bool isDead() { return dead; }
	void setDeadState(bool Dead) { dead = Dead; }

	string getName() { return name; }
	void setName(string Name) { name = Name; }

	int getHP() { return hp; }
	void setHP(int HP) { hp = HP; }
	int getMaxHP() { return max_hp; }
	void setMaxHP(int MaxHP) { max_hp = MaxHP; }

	double getX() { return x; }
	double getY() { return y; }
	void setX(double X) { x = X; }
	void setY(double Y) { y = Y; }

	bool getActiveState() { return active; }
	void setActiveState(bool newState) { active = newState; }
	int getDir() { return dir; }
	void setDir(int Dir) { dir = Dir; }
	double getMoveSpeed() { return moveSpeed; }
	void setMoveSpeed(double newSpeed) { moveSpeed = newSpeed; }

	ALLEGRO_BITMAP * getBitmap() { return bitmap; }
	void setBitmap(ALLEGRO_BITMAP * Bitmap) { bitmap = Bitmap; }
	int getBitmapSourceX() { return bitmap_sourceX; }
	int getBitmapSourceY() { return bitmap_sourceY; }
	void setBitmapSourceX(int X) { bitmap_sourceX = X; }
	void setBitmapSourceY(int Y) { bitmap_sourceY = Y; }

	~MovingObject(void);

private:
	int type;

	bool dead;
	string name;
	int hp;
	int max_hp;
	double x, y;

	bool active;
	int dir;
	double moveSpeed;

	ALLEGRO_BITMAP * bitmap;
	int bitmap_sourceX, bitmap_sourceY;

	friend class Player;
	friend class NPC;
	friend class Rabbit;
};