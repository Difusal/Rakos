#include "NPC.h"

NPC::NPC(string Name, double P1_X, double P1_Y, double P2_X, double P2_Y, const char* Bitmap) {
	type = _NPC;
	name = Name;
	dead = false;

	active = true;
	direction = DOWN;
	p1_x = P1_X;
	p1_y = P1_Y;
	p2_x = P2_X;
	p2_y = P2_Y;
	x = P1_X;
	y = P1_Y;
	moveSpeed = NPCWalkingSpeed;

	bitmap = al_load_bitmap(Bitmap);
	if (!bitmap) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load NPC bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	bitmap_sourceX = 32;
	bitmap_sourceY = 0;
}

NPC::NPC(string Name, double X, double Y, const char* Bitmap) {
	type = _NPC;
	name = Name;
	dead = false;

	active = false;
	direction = DOWN;
	p1_x = X;
	p1_y = Y;
	p2_x = X;
	p2_y = Y;
	x = X;
	y = Y;
	moveSpeed = NPCWalkingSpeed;

	bitmap = al_load_bitmap(Bitmap);
	bitmap_sourceX = 32;
	bitmap_sourceY = 0;
}

NPC::~NPC(void) {
}