#include "CreaturesWindow.h"

CreaturesWindow::CreaturesWindow(string Title) {
	title = Title;
	titleBarHeight = 20;

	height = 250;
}

CreaturesWindow::~CreaturesWindow(void) {
	delete cameraX;
	delete cameraY;
	al_destroy_font(font);
}