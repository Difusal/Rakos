#include "MenuState.h"
#include "RPG.h"

void MenuState::Initialize() {
	background = al_load_bitmap(MainMenuBackgroundPath);
	if (!background)
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Main Menu warning.", "Could not load Main Menu background.\nPress OK to continue anyway.", NULL, ALLEGRO_MESSAGEBOX_WARN);
}

bool MenuState::Update(ALLEGRO_EVENT *ev) {
	if (RPG::GetInstance()->Mouse->leftMouseButtonReleased) {
		RPG::GetInstance()->ToggleFullScreen();
		return true;
	}

	if (ev->type == ALLEGRO_EVENT_TIMER) {

	}

	return false;
}

void MenuState::Draw() {
	// drawing background
	if (RPG::GetInstance()->ScreenWidth <= 1366 && RPG::GetInstance()->ScreenHeight <= 768)
		al_draw_bitmap_region(background, al_get_bitmap_width(background)/2 - RPG::GetInstance()->ScreenWidth/2, al_get_bitmap_height(background) - RPG::GetInstance()->ScreenHeight, RPG::GetInstance()->ScreenWidth, RPG::GetInstance()->ScreenHeight, RPG::GetInstance()->cameraPosition[0], RPG::GetInstance()->cameraPosition[1], ALLEGRO_ALIGN_LEFT);
	else
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), RPG::GetInstance()->cameraPosition[0], RPG::GetInstance()->cameraPosition[1], RPG::GetInstance()->cameraPosition[0]+RPG::GetInstance()->ScreenWidth, RPG::GetInstance()->cameraPosition[1]+RPG::GetInstance()->ScreenHeight, ALLEGRO_ALIGN_LEFT);
}

void MenuState::Terminate() {
	// destroying background
	al_destroy_bitmap(background);
}