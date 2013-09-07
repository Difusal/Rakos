#include "MenuState.h"
#include "RPG.h"

void MenuState::Initialize() {
	// loading background
	background = al_load_bitmap(MainMenuBackgroundPath);
	if (!background)
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Main Menu warning.", "Could not load Main Menu background.\nPress OK to continue anyway.", NULL, ALLEGRO_MESSAGEBOX_WARN);

	// initializing data
	font = al_load_font(CalibriTTF, RPG::GetInstance()->ScreenHeight/5, NULL);
	titleX = RPG::GetInstance()->cameraPosition[0]+font->height/2;
	titleY = RPG::GetInstance()->cameraPosition[1]+font->height/2;

	// initializing forms
	formsSpacing = 30;

	switch (RPG::GetInstance()->LanguageBeingUsed) {
	case _English:
		usernameForm = new Form("Username", titleX, titleY+font->height);
		passwordForm = new Form("Password", titleX, usernameForm->YEndPos()+formsSpacing);
		break;
	case _Portuguese:
		usernameForm = new Form("Nome de Utilizador", titleX, titleY+font->height);
		passwordForm = new Form("Palavra-Passe", titleX, usernameForm->YEndPos()+formsSpacing);
		break;
	}
	forms.push_back(usernameForm);
	forms.push_back(passwordForm);

	loginButtonWidth = usernameForm->Width()/3;
	loginButtonHeight = usernameForm->Height();

	// initializing buttons
	ToggleFullscreen = new FullscreenButton(ToggleFullscreenPngPath, 50, 50);
	ToggleFullscreen->PositionOnUpperRightCorner();

	Login = new MenuButton("Login", titleX+loginButtonWidth/2, passwordForm->YEndPos()+formsSpacing+loginButtonHeight/2, loginButtonWidth, loginButtonHeight);
	buttons.push_back(Login);
}

bool MenuState::Update(ALLEGRO_EVENT *ev) {
	// updating forms
	for (Form *form: forms)
		form->Update(ev);

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
		if (Login->wasReleased()) {
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

	// drawing title
	al_draw_text(font, White, titleX, titleY, ALLEGRO_ALIGN_LEFT, "Rakos");

	// drawing forms
	for (Form *form: forms)
		form->Draw();

	// drawing buttons
	for (MenuButton *button: buttons)
		button->Draw();
	ToggleFullscreen->Draw();
}

void MenuState::Terminate() {
	// destroying background
	al_destroy_bitmap(background);

	// destroying forms
	for (Form *form: forms)
		delete form;
	forms.clear();

	// destroying buttons
	delete ToggleFullscreen;
	for (MenuButton *button: buttons)
		delete button;
	buttons.clear();
}