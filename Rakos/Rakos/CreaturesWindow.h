#pragma once

#include "SideBarWindow.h"

class CreaturesWindow: public SideBarWindow {
public:
	CreaturesWindow(string Title);

	virtual void Update();
	virtual void Draw();

	~CreaturesWindow(void);
};