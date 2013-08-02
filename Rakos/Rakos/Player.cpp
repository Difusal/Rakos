#include "Player.h"
#include "RPG.h"

Player::Player(string Name, Weapon *weapon, double X, double Y) {
	type = _Player;
	name = Name;
	dead = false;
	this->weapon = weapon;

	active = false;
	direction = DOWN;
	x = X;
	y = Y;
	running = false;
	moveSpeed = HumansWalkingSpeed;

	bitmap = al_load_bitmap(playerPng);
	if (!bitmap) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load player bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	bitmap_sourceX = 32;
	bitmap_sourceY = 0;
}

void Player::updateFeetCoords() {
	feet_x = this->getX() + 16;
	feet_y = this->getY() + 32;
}

Player::~Player(void) {
}