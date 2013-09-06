#pragma once

#include "stdIncludes.h"
#include "State.h"

#include "ToggleButton.h"
#include "FullscreenButton.h"
#include "MenuButton.h"

class MenuState: public State {
public:
	virtual void Initialize();
	virtual bool Update( ALLEGRO_EVENT *ev );
	virtual void Draw();
	virtual void Terminate();

private:
	vector<MenuButton*> buttons;
	ToggleButton *Sounds;
	ToggleButton *Music;
	FullscreenButton *ToggleFullscreen;
	MenuButton *Submit;
	MenuButton *SignUp;
	MenuButton *Exit;

	ALLEGRO_BITMAP *background;
};