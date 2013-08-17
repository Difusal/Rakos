#pragma once

#include "stdIncludes.h"
#include "MouseCursor.h"

class SideBarWindow {
public:
	void Initialize();
	void CheckIfWindowIsBeingMoved();
	virtual void Update() = 0;
	void UpdateBase();
	virtual void Draw() = 0;
	void DrawBase();

	void setTitle(string Title) { title = Title; }
	void setHeight(unsigned int Height) { height = Height; }

	bool isBeingDragged() { return beingDragged; }

	unsigned int currentYPos() { return titleBarY; }
	unsigned int middleYPos() { return titleBarY + titleBarHeight + height/2.0; }
	unsigned int currentBottomYPos() { return titleBarY + getHeight(); }
	unsigned int getHeight() { return titleBarHeight + height; }
	void setDefaultWindowY(unsigned int Y) { defaultWindowY = Y; }

private:
	string title;
	unsigned int defaultWindowY;
	unsigned int titleBarX, titleBarY;
	unsigned int titleBarHeight;
	unsigned int x, y;
	unsigned int width, height;

	MouseCursor *mouse;
	bool beingDragged;
	unsigned int titleBarYWhenDraggingStarted;
	unsigned int draggingStartY;
	int displacement;

	float *cameraX, *cameraY;
	ALLEGRO_FONT *font;

	friend class InfoWindow;
	friend class EquipmentWindow;
	friend class CreaturesWindow;
	friend class CreatureWindowObject;
};