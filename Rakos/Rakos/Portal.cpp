#include "Portal.h"
#include "RPG.h"

Portal::Portal(bool alreadyOpened, int sourceBlockX, int sourceBlockY, int destinyBlockX, int destinyBlockY) {
	bitmap = al_load_bitmap(PortalPng);
	if (!bitmap) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load portal bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	this->sourceX = sourceBlockX*WorldBlockSize;
	this->sourceY = sourceBlockY*WorldBlockSize;
	destinyX = destinyBlockX*WorldBlockSize;
	destinyY = destinyBlockY*WorldBlockSize;

	openingSpeed = 7;
	regularSpeed = 2;
	al_set_timer_speed(RPG::GetInstance()->GetTimer(_PortalAnimTimer), 1.0 / regularSpeed);

	open = alreadyOpened;
	if (open)
		bitmap_sourceX = 5*al_get_bitmap_width(bitmap)/7.0;
}


void Portal::Open() {
	opening = true;
	al_set_timer_speed(RPG::GetInstance()->GetTimer(_PortalAnimTimer), 1.0 / openingSpeed);
	bitmap_sourceX = 0;
	open = true;
}

void Portal::Close() {
	open = false;
}

void Portal::CheckIfPlayerPassedThrough(Player *player) {
	// if player passed through portal, transport player to destiny
	if (isOpen()) {
		if ((483 <= player->getFeetX() && player->getFeetX() <= 515) && (123 <= player->getFeetY() && player->getFeetY() <= 156)) {
			player->setX(destinyX + al_get_bitmap_width(bitmap)/7.0/2 - player->width()/2);
			player->setY(player->getY());
		}
	}
}

void Portal::UpdateAnimationFrame() {
	bitmap_sourceX += al_get_bitmap_width(bitmap)/7.0;

	if (opening && bitmap_sourceX == 5*al_get_bitmap_width(bitmap)/7.0) {
		al_set_timer_speed(RPG::GetInstance()->GetTimer(_PortalAnimTimer), 1.0 / regularSpeed);
		opening = false;
	}

	if(bitmap_sourceX >= al_get_bitmap_width(bitmap))
		bitmap_sourceX = 5*al_get_bitmap_width(bitmap)/7.0;
}

void Portal::Draw() {
	if (open) {
		al_draw_bitmap_region(bitmap, bitmap_sourceX, 10, al_get_bitmap_width(bitmap)/7.0, al_get_bitmap_height(bitmap), sourceX, sourceY, NULL);
		al_draw_bitmap_region(bitmap, bitmap_sourceX, 10, al_get_bitmap_width(bitmap)/7.0, al_get_bitmap_height(bitmap), destinyX, destinyY, NULL);
	}
}


Portal::~Portal(void) {
	al_destroy_bitmap(bitmap);
}
