#pragma once

#include "stdIncludes.h"
#include "state.h"

class EditingState: public State {
public:
	virtual void Initialize();
	virtual bool Update(ALLEGRO_EVENT *ev);
	virtual void Draw();
	virtual void Terminate();

private:
	ALLEGRO_BITMAP *tileSet;
	vector<vector<int> > worldMap;

	double cameraCenterX;
	double cameraCenterY;

	unsigned int sideBarWidth;
};