#include "CreaturesWindow.h"

CreaturesWindow::CreaturesWindow(string Title) {
	Initialize();

	title = Title;
	height = 250;
}


void CreaturesWindow::Update() {
	UpdateBase();
}

void CreaturesWindow::Draw(){
	DrawBase();
}


CreaturesWindow::~CreaturesWindow(void) {
	delete cameraX;
	delete cameraY;
	al_destroy_font(font);
}