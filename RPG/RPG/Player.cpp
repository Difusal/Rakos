#include "Player.h"

/*
Player::Player(void)
{
	type = playerType;
	dead = false;
	weapon = new Weapon();

	active = false;
	dir = DOWN;
	x = 0;
	y = 0;
	running = false;
	moveSpeed = HumansWalkingSpeed;

	bitmap = al_load_bitmap(playerPng);
	bitmap_sourceX = 32;
	bitmap_sourceY = 0;
}
*/

Player::Player(Weapon *weapon, double X, double Y)
{
	type = playerType;
	dead = false;
	this->weapon = weapon;

	active = false;
	dir = DOWN;
	x = X;
	y = Y;
	running = false;
	moveSpeed = HumansWalkingSpeed;

	bitmap = al_load_bitmap(playerPng);
	bitmap_sourceX = 32;
	bitmap_sourceY = 0;
}

void Player::updateFeetCoords()
{
	feet_x = this->getX() + 16;
	feet_y = this->getY() + 32;
}

Player::~Player(void)
{
}