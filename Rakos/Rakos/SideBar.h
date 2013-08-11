#pragma once

#include "stdIncludes.h"
#include "SideBarWindow.h"
#include "InfoWindow.h"

class SideBar {
public:
	SideBar();

	void InitializeWindows();
	void DistributeWindowsAlongSideBar();
	void CheckIfAnywindowIsBeingMoved();
	void Update();
	void Draw();

	~SideBar();

private:
	unsigned int x, y;

	bool someWindowBeingMoved;
	unsigned int movingWindowID;
	vector<SideBarWindow*> windows;
	InfoWindow *infoWindow;
	SideBarWindow *testWindow2;
	SideBarWindow *testWindow3;

	float *cameraX, *cameraY;
	unsigned int width, height;
	ALLEGRO_BITMAP *bacground;
};