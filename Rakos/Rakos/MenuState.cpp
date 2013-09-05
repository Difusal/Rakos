#include "MenuState.h"
#include "RPG.h"

void MenuState::Initialize() {
	background = al_load_bitmap(MainMenuBackgroundPath);
	if (!background)
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Main Menu warning.", "Could not load Main Menu background.\nPress OK to continue anyway.", NULL, ALLEGRO_MESSAGEBOX_WARN);
}

bool MenuState::Update( ALLEGRO_EVENT *ev ) {


	return false;
}

void MenuState::Draw() {
	// drawing background
	al_draw_bitmap(background, RPG::GetInstance()->cameraPosition[0], RPG::GetInstance()->cameraPosition[1], ALLEGRO_ALIGN_LEFT);


}

void MenuState::Terminate() {
	// destroying background
	al_destroy_bitmap(background);
}
