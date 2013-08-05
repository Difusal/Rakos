#include "Switch.h"
#include "RPG.h"

Switch::Switch(int x, int y, int unpressDelay) {
	bitmap = al_load_bitmap(SwitchPng);
	if (!bitmap) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load switch bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	this->x = x*WorldBlockSize;
	this->y = y*WorldBlockSize;

	this->unpressDelay = unpressDelay;
	unpressDelayCounter = 0;

	pressed = false;
}


void Switch::Press() {
	pressed = true;
}

void Switch::Unpress() {
	pressed = false;
}

bool Switch::isBeingPressed(Player *player) {
	if ((x+6 <= player->getFeetX() && player->getFeetX() <= x+35) && (y+10 <= player->getFeetY() && player->getFeetY() <= y+35)) {
		unpressDelayCounter = 0;
		return true;
	}

	return false;
}

bool Switch::unpressDelayPassed() {
	if (unpressDelayCounter > unpressDelay){
		unpressDelayCounter = 0;
		Unpress();

		return true;
	}

	return false;
}

void Switch::Draw() {
	switch (pressed) {
	case true:
		al_draw_bitmap_region(bitmap, al_get_bitmap_width(bitmap)/2.0, 10, al_get_bitmap_width(bitmap)/2.0, al_get_bitmap_height(bitmap), x, y, NULL);
		break;
	case false:
		al_draw_bitmap_region(bitmap, 0, 10, al_get_bitmap_width(bitmap)/2.0, al_get_bitmap_height(bitmap), x, y, NULL);
		break;
	}
}


Switch::~Switch(void) {
	al_destroy_bitmap(bitmap);
}
