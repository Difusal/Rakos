#pragma once

#include "stdIncludes.h"
#include "State.h"

#include "ToggleButton.h"
#include "FullscreenButton.h"
#include "MenuButton.h"
#include "Form.h"

class MenuState: public State {
public:
	virtual void Initialize();
	virtual bool Update( ALLEGRO_EVENT *ev );
	virtual void Draw();
	virtual void Terminate();

private:
	unsigned int titleX, titleY;
	unsigned int formsSpacing;
	unsigned int usernameFormX, usernameFormY;
	unsigned int passwordFormX, passwordFormY;
	unsigned int loginButtonWidth, loginButtonHeight;

	vector<MenuButton*> buttons;
	ToggleButton *Sounds;
	ToggleButton *Music;
	FullscreenButton *ToggleFullscreen;
	MenuButton *Login;
	MenuButton *SignUp;
	MenuButton *Exit;

	vector<Form*> forms;
	Form *usernameForm;
	Form *passwordForm;

	ALLEGRO_FONT *font;
	ALLEGRO_BITMAP *background;
};