#include "EquipmentWindow.h"
#include "RPG.h"

EquipmentWindow::EquipmentWindow(string Title) {
	Initialize();

	title = Title;
}


void EquipmentWindow::Update() {
	UpdateBase();

	weaponLabelX = x + width/4.0;
	shieldLabelX = x + 3*width/4.0;

	labelsY = y + font->height/2.0;
	
	thumbnailSize = 50;
	weaponThumbnailX = weaponLabelX - thumbnailSize/2.0;
	shieldThumbnailX = shieldLabelX - thumbnailSize/2.0;

	thumbnailsY = labelsY + font->height;
	
	height = (thumbnailsY + thumbnailSize + font->height) - y;
}

void EquipmentWindow::Draw() {
	DrawBase();

	string weaponStr, shieldStr;
	switch (RPG::GetInstance()->LanguageBeingUsed) {
	case _English:
		weaponStr = "Weapon:";
		shieldStr = "Shield:";
		break;
	case _Portuguese:
		weaponStr = "Arma:";
		shieldStr = "Escudo:";
		break;
	}

	// Printing labels
	al_draw_text(font, Black, weaponLabelX + 1, labelsY + 2, ALLEGRO_ALIGN_CENTER, weaponStr.c_str());
	al_draw_text(font, White, weaponLabelX, labelsY, ALLEGRO_ALIGN_CENTER, weaponStr.c_str());
	al_draw_text(font, Black, shieldLabelX + 1, labelsY + 2, ALLEGRO_ALIGN_CENTER, shieldStr.c_str());
	al_draw_text(font, White, shieldLabelX, labelsY, ALLEGRO_ALIGN_CENTER, shieldStr.c_str());

	// Drawing thumbnails background
	al_draw_filled_rectangle(weaponThumbnailX-2, thumbnailsY-2, weaponThumbnailX+thumbnailSize+2, thumbnailsY+thumbnailSize+2, DarkerGray);
	al_draw_filled_rectangle(shieldThumbnailX-2, thumbnailsY-2, shieldThumbnailX+thumbnailSize+2, thumbnailsY+thumbnailSize+2, DarkerGray);

	// Drawing thumbnails frame
	al_draw_rectangle(weaponThumbnailX, thumbnailsY, weaponThumbnailX+thumbnailSize+1, thumbnailsY+thumbnailSize+1, DarkGray, 1.0);
	al_draw_rectangle(shieldThumbnailX, thumbnailsY, shieldThumbnailX+thumbnailSize+1, thumbnailsY+thumbnailSize+1, DarkGray, 1.0);

	// Drawing weapon and shield thumbnails
	al_draw_bitmap(RPG::GetInstance()->GetPlayer()->getWeapon()->getThumbnail(), weaponThumbnailX, thumbnailsY, ALLEGRO_ALIGN_LEFT);
	al_draw_bitmap(RPG::GetInstance()->GetPlayer()->getShield()->getThumbnail(), shieldThumbnailX, thumbnailsY, ALLEGRO_ALIGN_LEFT);
}


EquipmentWindow::~EquipmentWindow(void) {
	delete cameraX;
	delete cameraY;
	al_destroy_font(font);
}