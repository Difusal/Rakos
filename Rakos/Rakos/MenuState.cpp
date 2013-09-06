#include "MenuState.h"
#include "RPG.h"

void MenuState::Initialize() {
	// loading background
	background = al_load_bitmap(MainMenuBackgroundPath);
	if (!background)
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Main Menu warning.", "Could not load Main Menu background.\nPress OK to continue anyway.", NULL, ALLEGRO_MESSAGEBOX_WARN);

	// initializing buttons
	ToggleFullscreen = new FullscreenButton(ToggleFullscreenPngPath, 50, 50);
	ToggleFullscreen->PositionOnUpperRightCorner();

	Submit = new MenuButton("Login", 250, 250, 120, 50);
	buttons.push_back(Submit);
}

bool MenuState::Update(ALLEGRO_EVENT *ev) {
	if (ev->type == ALLEGRO_EVENT_TIMER) {
		// updating buttons
		for (MenuButton *button: buttons)
			button->Update();
		ToggleFullscreen->Update();

		// if user toggled fullscreen
		if (ToggleFullscreen->wasReleased()) {
			RPG::GetInstance()->ToggleFullScreen();
			return true;
		}

		// if player submitted login data
		if (Submit->wasReleased()) {
			RPG::GetInstance()->ChangeState(_Tutorial);
			return true;
		}
	}

	return false;
}

void MenuState::Draw() {
	// drawing background
	if (RPG::GetInstance()->ScreenWidth <= 1366 && RPG::GetInstance()->ScreenHeight <= 768)
		al_draw_bitmap_region(background, al_get_bitmap_width(background)/2 - RPG::GetInstance()->ScreenWidth/2, al_get_bitmap_height(background) - RPG::GetInstance()->ScreenHeight, RPG::GetInstance()->ScreenWidth, RPG::GetInstance()->ScreenHeight, RPG::GetInstance()->cameraPosition[0], RPG::GetInstance()->cameraPosition[1], ALLEGRO_ALIGN_LEFT);
	else
		al_draw_scaled_bitmap(background, 0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background), RPG::GetInstance()->cameraPosition[0], RPG::GetInstance()->cameraPosition[1], RPG::GetInstance()->cameraPosition[0]+RPG::GetInstance()->ScreenWidth, RPG::GetInstance()->cameraPosition[1]+RPG::GetInstance()->ScreenHeight, ALLEGRO_ALIGN_LEFT);

	// drawing buttons
	for (MenuButton *button: buttons)
		button->Draw();
	ToggleFullscreen->Draw();
}

void MenuState::Terminate() {
	// destroying background
	al_destroy_bitmap(background);

	// destroying buttons
	delete ToggleFullscreen;
	for (MenuButton *button: buttons)
		delete button;
	buttons.clear();
}