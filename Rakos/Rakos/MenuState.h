#pragma once

#include "stdIncludes.h"
#include "State.h"

class MenuState: public State {
public:
	virtual void Initialize();
	virtual bool Update( ALLEGRO_EVENT *ev );
	virtual void Draw();
	virtual void Terminate();

private:
	ALLEGRO_BITMAP *background;
};