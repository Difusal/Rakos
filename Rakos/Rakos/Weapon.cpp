#include "Weapon.h"
#include "globalFunctions.h"
#include "RPG.h"

Weapon::Weapon(WeaponType Type, int minAttack, int maxAttack) {
	type = Type;
	switch (type) {
	case _NoWeapon:
		name = "none";
		break;
	case _Knife:
		name = "Knife";
		break;
	case _Sword:
		name = "Sword";
	}

	min_attack = minAttack;
	max_attack = maxAttack;

	xCorrection = 0;
	yCorrection = 0;

	switch (type) {
	case _NoWeapon:
		bitmap = al_load_bitmap(SwordsPng);
		break;
	case _Knife:
		bitmap = al_load_bitmap(SwordsPng);
		break;
	case _Sword:
		bitmap = al_load_bitmap(SwordsPng);
		break;
	}
	if (!bitmap) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load weapon bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	if (type != _NoWeapon) {
		switch (type) {
		case _Knife:
		case _Sword:
			sprite = al_load_bitmap(SwordsPng);
			break;
		}

		if (!sprite) {
			al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load weapon sprite.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			exit(-1);
		}
	}
	startPlayingAnimation = false;
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
	startPlayingAnimation = true;
	frame = -1;
}

void Weapon::UpdateAttackAnimation() {
	if (startPlayingAnimation) {
		startPlayingAnimation = false;
		playingAnimation = true;
	}

	// skipping if not supposed to play animation
	if (!playingAnimation)
		return;
	
	frame++;
	if (frame > 3)
		playingAnimation = false;

	switch (type) {
	case _NoWeapon:
		break;
	case _Knife:
	case _Sword:
		switch (direction) {
		case DOWN:
			switch (frame) {
			case 0:
				spriteX1 = 4;
				spriteY1 = 24;
				width = height = 11;
				xCorrection = -11;
				yCorrection = 0;
				break;
			case 1:
				spriteX1 = 16;
				spriteY1 = 25;
				width = 7;
				height = 14;
				xCorrection = -4;
				yCorrection = 0;
				break;
			case 2:
				spriteX1 = 24;
				spriteY1 = 24;
				width = height = 11;
				xCorrection = 0;
				yCorrection = 0;
				break;
			case 3:
				spriteX1 = 25;
				spriteY1 = 16;
				width = 14;
				height = 7;
				xCorrection = 0;
				yCorrection = -4;
				break;
			}
			break;
		case LEFT:
			switch (frame) {
			case 0:
				spriteX1 = 16;
				spriteY1 = 0;
				width = 7;
				height = 14;
				xCorrection = -4;
				yCorrection = -14;
				break;
			case 1:
				spriteX1 = 4;
				spriteY1 = 4;
				width = height = 11;
				xCorrection = -11;
				yCorrection = -11;
				break;
			case 2:
				spriteX1 = 0;
				spriteY1 = 16;
				width = 14;
				height = 7;
				xCorrection = -14;
				yCorrection = -4;
				break;
			case 3:
				spriteX1 = 4;
				spriteY1 = 24;
				width = 11;
				height = 11;
				xCorrection = -11;
				yCorrection = 0;
				break;
			}
			break;
		case RIGHT:
			switch (frame) {
			case 0:
				spriteX1 = 16;
				spriteY1 = 0;
				width = 7;
				height = 14;
				xCorrection = -4;
				yCorrection = -14;
				break;
			case 1:
				spriteX1 = 24;
				spriteY1 = 4;
				width = height = 11;
				xCorrection = 0;
				yCorrection = -11;
				break;
			case 2:
				spriteX1 = 25;
				spriteY1 = 16;
				width = 14;
				height = 7;
				xCorrection = 0;
				yCorrection = -4;
				break;
			case 3:
				spriteX1 = 24;
				spriteY1 = 24;
				width = height = 11;
				xCorrection = 0;
				yCorrection = 0;
				break;
			}
			break;
		case UP:
			switch (frame) {
			case 0:
				spriteX1 = 24;
				spriteY1 = 4;
				width = height = 11;
				xCorrection = 0;
				yCorrection = -11;
				break;
			case 1:
				spriteX1 = 16;
				spriteY1 = 0;
				width = 7;
				height = 14;
				xCorrection = -4;
				yCorrection = -14;
				break;
			case 2:
				spriteX1 = 4;
				spriteY1 = 4;
				width = height = 11;
				xCorrection = -11;
				yCorrection = -11;
				break;
			case 3:
				spriteX1 = 0;
				spriteY1 = 16;
				width = 14;
				height = 7;
				xCorrection = -14;
				yCorrection = -4;
				break;
			}
			break;
		}
		break;
	}
}

void Weapon::Draw() {
	switch (type) {
	case _NoWeapon:
		break;
	case _Knife:
	case _Sword:
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
	al_draw_bitmap_region(sprite, spriteX1, spriteY1, width, height, x + xCorrection, y + yCorrection, NULL);
}


int Weapon::getDamage() {
	return randomNumber(min_attack, max_attack);
}


Weapon::~Weapon(void) {
	if (bitmap)
		al_destroy_bitmap(bitmap);

	if (type != _NoWeapon)
		al_destroy_bitmap(sprite);
}
