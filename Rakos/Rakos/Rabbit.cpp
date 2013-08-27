#include "Rabbit.h"
#include "globalFunctions.h"

Rabbit::Rabbit(double X, double Y) {
	type = _Creature;
	timer = _SlowCreatureMoveTimer;
	switch (RPG::GetInstance()->LanguageBeingUsed) {
	case _English:
		name = "Rabbit";
		break;
	case _Portuguese:
		name = "Coelho";
		break;
	}
	weapon = RPG::GetInstance()->GetWeapon(_NoWeapon);
	shield = RPG::GetInstance()->GetShield(_NoShield);
	gold = randomNumber(1, 3);
	experience = 5;

	dead = false;
	active = true;
	alwaysInactive = !active;
	speaking = false;

	maxHp = 10;
	hp = maxHp;
	
	x = X;
	y = Y;
	direction = DOWN;

	centerX = x;
	centerY = y;
	wanderRadius = 4*WorldBlockSize;

	bitmap = al_load_bitmap(rabbitPng);
	if (!bitmap) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load rabbit bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	bitmap_sourceX = 32;
	bitmap_sourceY = 0;
}

Rabbit::~Rabbit(void) {
}
