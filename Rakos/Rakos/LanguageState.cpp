#include "LanguageState.h"
#include "RPG.h"

// language flags
#define EnglandFlagPath "res//flags//england.jpg"
#define PortugalFlagPath "res//flags//portugal.jpg"

void LanguageState::Initialize() {
	unsigned int flagsWidth, flagsHeight;
	flagsWidth = 0.44*RPG::GetInstance()->ScreenWidth;
	flagsHeight = flagsWidth/1.5;

	// creating buttons
	England = new FlagButton("English", EnglandFlagPath, RPG::GetInstance()->ScreenWidth/4, RPG::GetInstance()->ScreenHeight/2, flagsWidth, flagsHeight);
	flags.push_back(England);

	Portugal = new FlagButton("Portuguese", PortugalFlagPath, 3*RPG::GetInstance()->ScreenWidth/4, RPG::GetInstance()->ScreenHeight/2, flagsWidth, flagsHeight);
	flags.push_back(Portugal);
}

bool LanguageState::Update( ALLEGRO_EVENT *ev ) {
	// if language has already been chosen
	if (RPG::GetInstance()->LanguageBeingUsed != _UndefinedLanguage) {
		cout << "Language being used: ";
		switch (RPG::GetInstance()->LanguageBeingUsed) {
		case _English:
			cout << "English" << endl;
			break;
		case _Portuguese:
			cout << "Portuguese" << endl;
			break;
		}

		// go to main menu
		RPG::GetInstance()->ChangeState(_MainMenu);
		return true;
	}

	if (ev->type == ALLEGRO_EVENT_TIMER) {
		// updating flags
		for (FlagButton *flag: flags)
			flag->Update();

		// checking if any button was released
		if (Portugal->wasReleased()) {
			RPG::GetInstance()->LanguageBeingUsed = _Portuguese;
			return true;
		}
		if (England->wasReleased()) {
			RPG::GetInstance()->LanguageBeingUsed = _English;
			return true;
		}
	}

	return false;
}

void LanguageState::Draw() {
	// drawing flags
	for (FlagButton *flag: flags)
		flag->Draw();
}

void LanguageState::Terminate() {
	// deleting flag buttons
	for (FlagButton *flag: flags)
		delete flag;
	flags.clear();
}