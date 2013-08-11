#include "EquipmentWindow.h"

EquipmentWindow::EquipmentWindow(string Title) {
	Initialize();

	title = Title;
	height = 150;
}


void EquipmentWindow::Update() {
	UpdateBase();

	weaponLabelX = x + width/4.0;
	shieldLabelX = x + 3*width/4.0;

	labelsY = y + font->height/2.0;
}

void EquipmentWindow::Draw() {
	DrawBase();

	// Printing labels
	al_draw_text(font, Black, weaponLabelX + 1, labelsY + 2, ALLEGRO_ALIGN_CENTER, "Weapon:");
	al_draw_text(font, White, weaponLabelX, labelsY, ALLEGRO_ALIGN_CENTER, "Weapon:");
	al_draw_text(font, Black, shieldLabelX + 1, labelsY + 2, ALLEGRO_ALIGN_CENTER, "Shield:");
	al_draw_text(font, White, shieldLabelX, labelsY, ALLEGRO_ALIGN_CENTER, "Shield:");
}


EquipmentWindow::~EquipmentWindow(void) {
	delete cameraX;
	delete cameraY;
	al_destroy_font(font);
}