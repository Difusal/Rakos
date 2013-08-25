#include "MenuState.h"
#include "Editor.h"

void MenuState::Initialize() {
	Editor::GetInstance()->CameraReset();

	titleY = 30;
	lineY = titleY + Editor::GetInstance()->extraLargeFont->height*0.85;
	lineWidth = 70;
	subTitleY = titleY + Editor::GetInstance()->extraLargeFont->height;

	newMapButtonY = 200;
	editMapButtonY = 280;
	exitButtonY = 400;

	// initializing buttons
	NewMap = new MenuButton("New Map", newMapButtonY);
	buttons.push_back(NewMap);

	EditMap = new MenuButton("Edit Map", editMapButtonY);
	buttons.push_back(EditMap);

	Exit = new MenuButton("Exit", exitButtonY);
	buttons.push_back(Exit);
}

bool MenuState::Update(ALLEGRO_EVENT *ev) {
	if (ev->timer.source == Editor::GetInstance()->GetTimer(_RegularTimer)) {
		for (MenuButton *button: buttons)
			button->Update();

		// checking if any button was pressed
		if (NewMap->wasPressed()) {
			Editor::GetInstance()->creatingNewMap = true;
			Editor::GetInstance()->ChangeState(_Editing);
		}
		else if (EditMap->wasPressed()) {
			Editor::GetInstance()->creatingNewMap = false;
			Editor::GetInstance()->ChangeState(_Editing);
		}
		else if (Exit->wasPressed())
			Editor::GetInstance()->FinishControlCycle();

		return true;
	}

	return false;
}

void MenuState::Draw() {
	// drawing title
	al_draw_text(Editor::GetInstance()->extraLargeFont, Black, Editor::GetInstance()->ScreenWidth/2.0+1, titleY+2, ALLEGRO_ALIGN_CENTER, "RAKOS");
	al_draw_text(Editor::GetInstance()->extraLargeFont, White, Editor::GetInstance()->ScreenWidth/2.0, titleY, ALLEGRO_ALIGN_CENTER, "RAKOS");

	// drawing line under title and above subtitle
	al_draw_line(Editor::GetInstance()->ScreenWidth/2.0-lineWidth+1, lineY+2, Editor::GetInstance()->ScreenWidth/2.0+lineWidth+1, lineY+2, Black, 4.0);
	al_draw_line(Editor::GetInstance()->ScreenWidth/2.0-lineWidth, lineY, Editor::GetInstance()->ScreenWidth/2.0+lineWidth, lineY, White, 4.0);

	// drawing subtitle
	al_draw_text(Editor::GetInstance()->largeFont, Black, Editor::GetInstance()->ScreenWidth/2.0+1, subTitleY+2, ALLEGRO_ALIGN_CENTER, "Map Editor");
	al_draw_text(Editor::GetInstance()->largeFont, White, Editor::GetInstance()->ScreenWidth/2.0, subTitleY, ALLEGRO_ALIGN_CENTER, "Map Editor");

	// drawing buttons
	for (MenuButton *button: buttons)
		button->Draw();

	// printing program version
	al_draw_text(Editor::GetInstance()->mediumFont, Black, 1, Editor::GetInstance()->ScreenHeight-Editor::GetInstance()->mediumFont->height+1, ALLEGRO_ALIGN_LEFT, " Rakos: Map Editor v1.0");
	al_draw_text(Editor::GetInstance()->mediumFont, White, 0, Editor::GetInstance()->ScreenHeight-Editor::GetInstance()->mediumFont->height, ALLEGRO_ALIGN_LEFT, " Rakos: Map Editor v1.0");

	// printing author and date
	al_draw_text(Editor::GetInstance()->mediumFont, Black, Editor::GetInstance()->ScreenWidth+1, Editor::GetInstance()->ScreenHeight-Editor::GetInstance()->mediumFont->height+1, ALLEGRO_ALIGN_RIGHT, "Henrique Ferrolho - August, 2013 ");
	al_draw_text(Editor::GetInstance()->mediumFont, White, Editor::GetInstance()->ScreenWidth, Editor::GetInstance()->ScreenHeight-Editor::GetInstance()->mediumFont->height, ALLEGRO_ALIGN_RIGHT, "Henrique Ferrolho - August, 2013 ");
}

void MenuState::Terminate() {
	// destroying buttons
	for (MenuButton *button: buttons)
		delete button;
	buttons.clear();
}