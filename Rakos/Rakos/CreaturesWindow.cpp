#include "CreaturesWindow.h"
#include "CreatureWindowObject.h"

CreaturesWindow::CreaturesWindow(string Title, vector<LivingBeing*> *beings) {
	Initialize();

	this->beings = beings;

	title = Title;

	unsigned int numberOfCreaturesToDisplayOnWindow = 4;
	for (unsigned int i = 0; i < numberOfCreaturesToDisplayOnWindow; i++)
		creatureInfo.push_back(new CreatureWindowObject());
	height = numberOfCreaturesToDisplayOnWindow*40 + 1;
}


void CreaturesWindow::ChooseCreaturesToDisplay(vector<LivingBeing*> *beings) {
	creaturesToDisplay.clear();

	// STILL NEED TO DEVELOP THIS ALGORITHM
	for (unsigned int i = 0; i < beings->size(); i++) {
		if ((*beings)[i]->getType() == _Creature)
			creaturesToDisplay.push_back((*beings)[i]);
	}
}

void CreaturesWindow::Update() {
	UpdateBase();

	for (unsigned int i = 0; i < creatureInfo.size(); i++)
		creatureInfo[i]->Deactivate();

	ChooseCreaturesToDisplay(beings);

	for (unsigned int i = 0; i < creaturesToDisplay.size(); i++)
		creatureInfo[i]->Activate(creaturesToDisplay[i]);
	
	for (unsigned int i = 0; i < creatureInfo.size(); i++)
		creatureInfo[i]->Update(x, y+40*i);
}

void CreaturesWindow::Draw(){
	DrawBase();

	for (CreatureWindowObject *obj: creatureInfo)
		obj->Draw();
}


CreaturesWindow::~CreaturesWindow(void) {
	delete cameraX;
	delete cameraY;
	al_destroy_font(font);
}