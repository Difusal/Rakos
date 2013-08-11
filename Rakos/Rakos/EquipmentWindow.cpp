#include "EquipmentWindow.h"

EquipmentWindow::EquipmentWindow(string Title) {
	title = Title;
	titleBarHeight = 20;

	height = 150;
}

EquipmentWindow::~EquipmentWindow(void) {
	delete cameraX;
	delete cameraY;
	al_destroy_font(font);
}