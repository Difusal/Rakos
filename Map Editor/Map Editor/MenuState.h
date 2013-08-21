#pragma once

#include "stdIncludes.h"
#include "state.h"

#include "MenuButton.h"

class MenuState: public State {
public:
	virtual void Initialize();
	virtual bool Update( ALLEGRO_EVENT *ev );
	virtual void Draw();
	virtual void Terminate();

private:
	unsigned int titleY;
	unsigned int lineY, lineWidth;
	unsigned int subTitleY;

	unsigned int newMapButtonY;
	unsigned int editMapButtonY;
	unsigned int exitButtonY;
	
	vector<MenuButton*> buttons;
	MenuButton *NewMap;
	MenuButton *EditMap;
	MenuButton *Exit;
};