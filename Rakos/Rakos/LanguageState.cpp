#include "LanguageState.h"
#include "RPG.h"

// language flags
#define EnglandFlagPath "res//flags//england.jpg"
#define PortugalFlagPath "res//flags//portugal.jpg"

void LanguageState::Initialize() {
	unsigned int flagsWidth, flagsHeight;
	flagsWidth = 400;
	flagsHeight = flagsWidth/1.5;

	// creating buttons
	English = new FlagButton("English", EnglandFlagPath, ScreenWidth/4, ScreenHeight/2, flagsWidth, flagsHeight);
	flags.push_back(English);

	Portugal = new FlagButton("Portuguese", PortugalFlagPath, 3*ScreenWidth/4, ScreenHeight/2, flagsWidth, flagsHeight);
	flags.push_back(Portugal);
}

bool LanguageState::Update( ALLEGRO_EVENT *ev ) {
	if (ev->type == ALLEGRO_EVENT_TIMER) {
		// updating flags
		for (FlagButton *flag: flags)
			flag->Update();
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
}