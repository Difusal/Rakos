#include "BasicPortal.h"
#include "RPG.h"

BasicPortal::BasicPortal( bool alreadyOpened, int sourceBlockX, int sourceBlockY ) {
	bitmap = al_load_bitmap(PortalPng);
	if (!bitmap) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load portal bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	this->sourceX = sourceBlockX*WorldBlockSize;
	this->sourceY = sourceBlockY*WorldBlockSize;

	openingSpeed = 7;
	regularSpeed = 2;
	al_set_timer_speed(RPG::GetInstance()->GetTimer(_PortalAnimTimer), 1.0 / regularSpeed);

	open = alreadyOpened;
	if (open)
		bitmap_sourceX = 5*al_get_bitmap_width(bitmap)/7.0;
}

void BasicPortal::Open() {
	opening = true;
	al_set_timer_speed(RPG::GetInstance()->GetTimer(_PortalAnimTimer), 1.0 / openingSpeed);
	bitmap_sourceX = 0;
	open = true;
}

void BasicPortal::Close() {
	open = false;
}

bool BasicPortal::PassedThrough( Player *player ) {
	// if player passed through portal return true
	if (isOpen()) {
		if ((sourceX+3 <= player->getFeetX() && player->getFeetX() <= sourceX+35) &&
			(sourceY+3 <= player->getFeetY() && player->getFeetY() <= sourceY+36)) {
				return true;
		}
	}

	return false;
}

void BasicPortal::UpdateAnimationFrame() {
	bitmap_sourceX += al_get_bitmap_width(bitmap)/7.0;

	if (opening && bitmap_sourceX == 5*al_get_bitmap_width(bitmap)/7.0) {
		al_set_timer_speed(RPG::GetInstance()->GetTimer(_PortalAnimTimer), 1.0 / regularSpeed);
		opening = false;
	}

	if(bitmap_sourceX >= al_get_bitmap_width(bitmap))
		bitmap_sourceX = 5*al_get_bitmap_width(bitmap)/7.0;
}

void BasicPortal::Draw() {
	if (open) {
		al_draw_bitmap_region(bitmap, bitmap_sourceX, 10, al_get_bitmap_width(bitmap)/7.0, al_get_bitmap_height(bitmap), sourceX, sourceY, NULL);
	}
}

BasicPortal::~BasicPortal(void) {
	al_destroy_bitmap(bitmap);
}