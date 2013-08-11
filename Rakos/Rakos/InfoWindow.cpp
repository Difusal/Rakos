#include "InfoWindow.h"
#include "RPG.h"

InfoWindow::InfoWindow(string Title) {
	Initialize();

	title = Title;
	height = 100;
}


void InfoWindow::Update() {
	UpdateBase();

}

void InfoWindow::Draw() {
	DrawBase();

	// Printing labels
	al_draw_text(font, White, x, y, ALLEGRO_ALIGN_LEFT, "HP");
	al_draw_text(font, White, x, y + font->height, ALLEGRO_ALIGN_LEFT, "HP");
}


InfoWindow::~InfoWindow(void) {
	delete cameraX;
	delete cameraY;
	al_destroy_font(font);
}