#include "NPC.h"
#include "RPG.h"

NPC::NPC(string Name, double X, double Y, const char* Bitmap, bool AlwaysInactive) {
	type = _NPC;
	timer = _NPCMoveTimer;
	name = Name;
	weapon = RPG::GetInstance()->GetWeapon(_NoWeapon);
	shield = RPG::GetInstance()->GetShield(_NoShield);

	dead = false;
	alwaysInactive = AlwaysInactive;
	active = !alwaysInactive;
	speaking = false;

	x = X;
	y = Y;
	direction = DOWN;

	centerX = x;
	centerY = y;
	wanderRadius = 3*WorldBlockSize;

	bitmap = al_load_bitmap(Bitmap);
	if (!bitmap) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load NPC bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	bitmap_sourceX = al_get_bitmap_width(bitmap)/4.0;
	bitmap_sourceY = 0;
}

NPC::~NPC(void) {
	al_destroy_bitmap(bitmap);
}