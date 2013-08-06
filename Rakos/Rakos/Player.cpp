#include "Player.h"
#include "RPG.h"

Player::Player(string Name, Weapon *weapon, double X, double Y) {
	type = _Player;
	name = Name;

	dead = false;
	active = false;
	alwaysInactive = !active;
	speaking = false;
	
	hp = 20;
	maxHp = hp;

	this->weapon = weapon;
	attackCooldown = 0;
	playerCanAttack = true;

	running = false;

	x = X;
	y = Y;
	direction = DOWN;
	moveSpeed = HumansWalkingSpeed;

	bitmap = al_load_bitmap(playerPng);
	if (!bitmap) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load player bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	bitmap_sourceX = 32;
	bitmap_sourceY = 0;
}


void Player::CheckIfRunning(ALLEGRO_KEYBOARD_STATE keyState) {
	if (al_key_down(&keyState, ALLEGRO_KEY_LSHIFT)) {
		moveSpeed = HumansRunningSpeed;
		if (!running)
			al_set_timer_speed(RPG::GetInstance()->GetTimer(_PlayerAnimTimer), 1.0/(1.5*drawFPS));
		running = true;
	}
	else {
		moveSpeed = HumansWalkingSpeed;
		if (running)
			al_set_timer_speed(RPG::GetInstance()->GetTimer(_PlayerAnimTimer), 1.0/drawFPS);
		running = false;
	}
}

void Player::UpdatePosition(ALLEGRO_KEYBOARD_STATE keyState, const vector<vector<int> > &worldMap) {
	active = true;

	if(al_key_down(&keyState, ALLEGRO_KEY_S)) {
		y += moveSpeed;
		if (y > worldMap.size()*WorldBlockSize - 32)
			y = worldMap.size()*WorldBlockSize - 32;

		direction = DOWN;
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_W)) {
		y -= moveSpeed;
		if (y < 0)
			y = 0;

		direction = UP;
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_D)) {
		x += moveSpeed;
		if (x > worldMap[0].size()*WorldBlockSize - 32)
			x = worldMap[0].size()*WorldBlockSize - 32;

		direction = RIGHT;
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_A)) {
		x -= moveSpeed;
		if (x < 0)
			x = 0;

		direction = LEFT;
	}
	else
		active = false;
}

void Player::Move(ALLEGRO_KEYBOARD_STATE keyState, const vector<vector<int> > &worldMap) {
	CheckIfRunning(keyState);
	UpdatePosition(keyState, worldMap);
	UpdateFeetCoords();
}

void Player::CorrectPositionIfCollidingWithMapLimits(const vector<vector<int> > &worldMap, const vector<int> &unaccessibleTiles) {
	if (RPG::GetInstance()->livingBeingCollidingWithMap(direction, worldMap, unaccessibleTiles)) {
		switch (direction) {
		default:
		case UP:
			y += moveSpeed;
			break;
		case DOWN:
			y -= moveSpeed;
			break;
		case LEFT:
			x += moveSpeed;
			break;
		case RIGHT:
			x -= moveSpeed;
			break;
		}
	}
}

void Player::ControlAttackRate() {
	if (!playerCanAttack)
		attackCooldown++;
	if (attackCooldown > AttackRate) {
		attackCooldown = 0;
		playerCanAttack = true;
	}
}

void Player::UpdateFeetCoords() {
	feet_x = this->getX() + 16;
	feet_y = this->getY() + 32;
}


Player::~Player(void) {
	al_destroy_bitmap(bitmap);
}