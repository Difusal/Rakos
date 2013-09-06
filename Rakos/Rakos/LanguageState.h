#pragma once

#include "stdIncludes.h"
#include "State.h"

#include "FlagButton.h"

class LanguageState: public State {
public:
	virtual void Initialize();
	virtual bool Update( ALLEGRO_EVENT *ev );
	virtual void Draw();
	virtual void Terminate();

private:
	vector<FlagButton*> flags;
	FlagButton *English, *Portugal;
};