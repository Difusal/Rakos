#include "InfoWindow.h"
#include "RPG.h"

InfoWindow::InfoWindow(string Title) {
	title = Title;
	titleBarHeight = 20;

	height = 100;
}

InfoWindow::~InfoWindow(void) {
	delete cameraX;
	delete cameraY;
	al_destroy_font(font);
}