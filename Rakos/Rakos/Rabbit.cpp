#include "Rabbit.h"

Rabbit::Rabbit(double P1_X, double P1_Y, double P2_X, double P2_Y) {
	name = "Rabbit";
	type = _Creature;

	dead = false;
	maxHp = 10;
	hp = maxHp;

	active = true;
	direction = DOWN;
	p1_x = P1_X;
	p1_y = P1_Y;
	p2_x = P2_X;
	p2_y = P2_Y;
	x = P1_X;
	y = P1_Y;
	moveSpeed = SlowCreaturesSpeed;

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