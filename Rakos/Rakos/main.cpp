#include "stdIncludes.h"
#include "RPG.h"

void StartAllegro5() {
	cout << "Starting Allegro 5..." << endl;
	if (!al_init())
		al_show_native_message_box(NULL, NULL, "Could not initialize Allegro 5", NULL, NULL, NULL);

	cout << "Initializing add ons..." << endl;
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();

	cout << "Installing devices..." << endl;
	al_install_mouse();
	al_install_keyboard();
	al_install_audio();
}

int main() {
	StartAllegro5();

	bool FullScreenMode = true;

	GameCycleReturnValue returnValue;
	returnValue.TogglingFullscreen = false;
	returnValue.CurrentLanguage = _UndefinedLanguage;

	do {
		// starting program control cycle
		returnValue = RPG::GetInstance()->StartGameControlCycle(FullScreenMode, returnValue.CurrentLanguage);

		// changing fullscreen state
		FullScreenMode = !FullScreenMode;
	} while (returnValue.TogglingFullscreen);

	// deleting instance
	delete RPG::GetInstance();

	return 0;
}