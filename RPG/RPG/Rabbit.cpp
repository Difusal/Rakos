#include "Rabbit.h"

Rabbit::Rabbit(double P1_X, double P1_Y, double P2_X, double P2_Y)
{
	name = "Rabbit";
	type = creatureType;

	dead = false;
	max_hp = 10;
	hp = max_hp;

	active = true;
	dir = DOWN;
	p1_x = P1_X;
	p1_y = P1_Y;
	p2_x = P2_X;
	p2_y = P2_Y;
	x = P1_X;
	y = P1_Y;
	moveSpeed = SlowCreaturesSpeed;

	bitmap = al_load_bitmap(rabbitPng);
	bitmap_sourceX = 32;
	bitmap_sourceY = 0;
}

Rabbit::~Rabbit(void)
{
}