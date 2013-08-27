#include "Player.h"
#include "RPG.h"

Player::Player(string Name, Weapon *weapon, Shield *shield, double X, double Y) {
	type = _Player;
	vocation = _NoVocation;
	timer = _PlayerMoveTimer;
	name = Name;
	experience = 0;

	dead = false;
	active = false;
	alwaysInactive = !active;
	speaking = false;
	
	hp = 20;
	maxHp = hp;
	mp = 10;
	maxMp = mp;
	level = 1;
	experience = 0;
	gold = 0;

	this->weapon = weapon;
	attackCooldown = 0;
	playerCanAttack = true;

	this->shield = shield;

	running = false;

	x = X;
	y = Y;
	direction = DOWN;

	bitmap = al_load_bitmap(playerPng);
	if (!bitmap) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load player bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	bitmap_sourceX = al_get_bitmap_width(bitmap)/4.0;
	bitmap_sourceY = 0;
}


void Player::CheckIfRunning(ALLEGRO_KEYBOARD_STATE keyState) {
	if (al_key_down(&keyState, ALLEGRO_KEY_LSHIFT) || al_key_down(&keyState, ALLEGRO_KEY_RSHIFT)) {
		al_set_timer_speed(RPG::GetInstance()->GetTimer(_PlayerMoveTimer), 1.0 / HumansRunningSpeed);
		if (!running)
			al_set_timer_speed(RPG::GetInstance()->GetTimer(_PlayerAnimTimer), 1.0/(1.5*drawFPS));
		running = true;
	}
	else {
		al_set_timer_speed(RPG::GetInstance()->GetTimer(_PlayerMoveTimer), 1.0 / HumansWalkingSpeed);
		if (running)
			al_set_timer_speed(RPG::GetInstance()->GetTimer(_PlayerAnimTimer), 1.0/drawFPS);
		running = false;
	}
}

void Player::UpdatePosition(ALLEGRO_KEYBOARD_STATE keyState, const vector<vector<int> > &worldMap) {
	active = true;

	if(al_key_down(&keyState, ALLEGRO_KEY_S)) {
		y++;
		if (y > worldMap.size()*WorldBlockSize - 32)
			y = worldMap.size()*WorldBlockSize - 32;

		direction = DOWN;
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_W)) {
		y--;
		if (y < 0)
			y = 0;

		direction = UP;
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_D)) {
		x++;
		if (x > worldMap[0].size()*WorldBlockSize - 32)
			x = worldMap[0].size()*WorldBlockSize - 32;

		direction = RIGHT;
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_A)) {
		x--;
		if (x < 0)
			x = 0;

		direction = LEFT;
	}
	else
		active = false;
}

void Player::Move(ALLEGRO_KEYBOARD_STATE keyState, const vector<vector<vector<int> >*> &WorldMapLevels, const vector<vector<int>*> &LevelsAccessibleTiles) {
	CheckIfRunning(keyState);
	UpdatePosition(keyState, *WorldMapLevels[0]);

	// making corrections if being is colliding with map
	for (unsigned int i = 0; i < WorldMapLevels.size(); i++) {
		if (CorrectPositionIfCollidingWithMapLimits(this, *WorldMapLevels[i], *LevelsAccessibleTiles[i]))
			if (i != WorldMapLevels.size()-1)
				return;
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


void Player::setWeapon(Weapon *newWeapon) {
	weapon = newWeapon;
	cout << "Player weapon set: " << weapon->getName() << endl;
}


Player::~Player(void) {
	al_destroy_bitmap(bitmap);
}