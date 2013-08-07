#include "Weapon.h"
#include "globalFunctions.h"
#include "RPG.h"

Weapon::Weapon(WeaponType Type, int minAttack, int maxAttack) {
	type = Type;
	switch (type) {
	case _None:
		name = "none";
		break;
	case _Knife:
		name = "Knife";
		break;
	}

	min_attack = minAttack;
	max_attack = maxAttack;

	bitmap = al_load_bitmap(SwordsPng);
	if (!bitmap) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load weapon bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	if (type != _None) {
		if (type == _Knife)
			sprite = al_load_bitmap(SwordsPng);

		if (!sprite) {
			al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load weapon sprite.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			exit(-1);
		}
	}
	playingAnimation = false;
	frame = 0;
}


void Weapon::UpdatePosition(Direction direction, int frame, double x, double y) {
	this->direction = direction;

	switch (direction) {
	case DOWN:
		switch (frame) {
		case 0:
			this->x = x + 6;
			this->y = y + 26;
			break;
		case 1:
		case 3:
			this->x = x + 8;
			this->y = y + 25;
			break;
		case 2:
			this->x = x + 10;
			this->y = y + 26;
			break;
		}
		break;
	case LEFT:
		switch (frame) {
		case 0:
			this->x = x + 16;
			this->y = y + 26;
			break;
		case 1:
		case 3:
			this->x = x + 14;
			this->y = y + 24;
			break;
		case 2:
			this->x = x + 12;
			this->y = y + 24;
			break;
		}
		break;
	case RIGHT:
		switch (frame) {
		case 0:
			this->x = x + 19;
			this->y = y + 24;
			break;
		case 1:
		case 3:
			this->x = x + 17;
			this->y = y + 24;
			break;
		case 2:
			this->x = x + 15;
			this->y = y + 26;
			break;
		}
		break;
	case UP:
		switch (frame) {
		case 0:
			this->x = x + 26;
			this->y = y + 24;
			break;
		case 1:
		case 3:
			this->x = x + 24;
			this->y = y + 24;
			break;
		case 2:
			this->x = x + 22;
			this->y = y + 26;
			break;
		}
		break;
	}
}

void Weapon::PlayAttackAnim() {
	playingAnimation = true;
	frame = 0;
}

void Weapon::UpdateAttackAnimation() {
	// skipping if not supposed to play animation
	if (!playingAnimation)
		return;

	switch (type) {
	case _None:
		break;
	case _Knife:
		switch (direction) {
		case UP:
			switch (frame) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			}
			break;
		}
		break;
	}

	frame++;
	if (frame > 3)
		playingAnimation = false;
}

void Weapon::Draw() {
	switch (type) {
	case _None:
		break;
	case _Knife:
		switch (direction) {
		case DOWN:
			al_draw_bitmap_region(sprite, 16, 0, 7, 14, x-4, y-14, NULL);
			break;
		case LEFT:
			al_draw_bitmap_region(sprite, 4, 4, 11, 11, x-11, y-11, NULL);
			break;
		case RIGHT:
			al_draw_bitmap_region(sprite, 24, 4, 11, 11, x, y-11, NULL);
			break;
		case UP:
			al_draw_bitmap_region(sprite, 16, 0, 7, 14, x-4, y-14, NULL);
			break;
		}
		break;
	}
}

void Weapon::DrawAttackAnim() {

}


int Weapon::getDamage() {
	return randomNumber(min_attack, max_attack);
}


Weapon::~Weapon(void) {
	if (bitmap)
		al_destroy_bitmap(bitmap);

	if (sprite)
		al_destroy_bitmap(sprite);
}
