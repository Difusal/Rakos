#pragma once

#include "stdIncludes.h"
#include "SideBarWindow.h"
#include "InfoWindow.h"
#include "EquipmentWindow.h"
#include "CreaturesWindow.h"

class SideBar {
public:
	SideBar(vector<LivingBeing*> *livingBeings);

	void InitializeWindows();
	void DistributeWindowsAlongSideBar();
	void CheckIfAnywindowIsBeingMoved();
	void Update();
	void Draw();

	~SideBar();

private:
	unsigned int x, y;

	vector<LivingBeing*> *beings;

	bool someWindowBeingMoved;
	unsigned int movingWindowID;

	vector<SideBarWindow*> windows;
	InfoWindow *infoWindow;
	EquipmentWindow *equipmentWindow;
	CreaturesWindow *creaturesWindow;

	float *cameraX, *cameraY;
	unsigned int width, height;
	ALLEGRO_BITMAP *background;
};