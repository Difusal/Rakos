#include "Player.h"

Player::Player(void)
{
	this->setType(playerType);
}

void Player::updateFeetCoords()
{
	feet_x = this->getX() + 16;
	feet_y = this->getY() + 32;
}

Player::~Player(void)
{
}