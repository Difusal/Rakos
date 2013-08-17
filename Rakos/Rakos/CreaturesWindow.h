#pragma once

#include "SideBarWindow.h"
#include "LivingBeing.h"

class CreaturesWindow: public SideBarWindow {
public:
	CreaturesWindow(string Title, vector<LivingBeing*> *beings);

	void ChooseCreaturesToDisplay(vector<LivingBeing*> *beings);
	virtual void Update();
	virtual void Draw();

	~CreaturesWindow(void);

private:
	vector<LivingBeing*> *beings;
	vector<LivingBeing*> creaturesToDisplay;
	vector<CreatureWindowObject*> creatureInfo;
};