#include "Shield.h"
#include "RPG.h"

Shield::Shield(ShieldType Type, unsigned int Defense) {
	type = Type;
	switch (type) {
	case _NoShield:
		name = "None";
		break;
	case _WoodenShield:
		name = "Wooden Shield";
	}

	defense = Defense;

	xCorrection = 0;
	yCorrection = 0;

	switch (type) {
	case _NoShield:
		thumbnail = al_load_bitmap(NoShieldThumb);
		break;
	case _WoodenShield:
		thumbnail = al_load_bitmap(WoodenShieldThumb);
		break;
	}
	if (!thumbnail) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load shield bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	if (type != _NoShield) {
		switch (type) {
		case _WoodenShield:
			sprite = al_load_bitmap(WoodenShieldPng);
			break;
		}

		if (!sprite) {
			al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load shield sprite.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			exit(-1);
		}
	}
}


void Shield::UpdatePosition(Direction direction, int frame, double x, double y) {
	this->direction = direction;

	switch (direction) {
	case DOWN:
		switch (frame) {
		case 0:
			this->x = x + 24;
			this->y = y + 25;
			break;
		case 1:
		case 3:
			this->x = x + 26;
			this->y = y + 24;
			break;
		case 2:
			this->x = x + 27;
			this->y = y + 25;
			break;
		}
		break;
	case LEFT:
		switch (frame) {
		case 0:
			this->x = x + 12;
			this->y = y + 24;
			break;
		case 1:
		case 3:
			this->x = x + 14;
			this->y = y + 24;
			break;
		case 2:
			this->x = x + 16;
			this->y = y + 26;
			break;
		}
		break;
	case RIGHT:
		switch (frame) {
		case 0:
			this->x = x + 15;
			this->y = y + 26;
			break;
		case 1:
		case 3:
			this->x = x + 17;
			this->y = y + 24;
			break;
		case 2:
			this->x = x + 19;
			this->y = y + 24;
			break;
		}
		break;
	case UP:
		switch (frame) {
		case 0:
			this->x = x + 8;
			this->y = y + 24;
			break;
		case 1:
		case 3:
			this->x = x + 7;
			this->y = y + 24;
			break;
		case 2:
			this->x = x + 9;
			this->y = y + 25;
			break;
		}
		break;
	}
}

void Shield::Draw() {
	switch (type) {
	case _NoShield:
		break;
	case _WoodenShield:
		switch (direction) {
		case DOWN:
			al_draw_bitmap_region(sprite, 9, 10, 4, 10, x, y-5, NULL);
			break;
		case LEFT:
			al_draw_bitmap_region(sprite, 0, 0, 13, 10, x-7, y-5, NULL);
			break;
		case RIGHT:
			al_draw_bitmap_region(sprite, 0, 20, 13, 10, x-7, y-5, NULL);
			break;
		case UP:
			al_draw_bitmap_region(sprite, 0, 10, 4, 10, x-4, y-5, NULL);
			break;
		}
		break;
	}
}


Shield::~Shield(void) {
	if (thumbnail)
		al_destroy_bitmap(thumbnail);

	if (type != _NoShield)
		al_destroy_bitmap(sprite);
}