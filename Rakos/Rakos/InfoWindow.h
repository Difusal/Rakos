#pragma once

#include "SideBarWindow.h"

class InfoWindow: public SideBarWindow {
public:
	InfoWindow(string Title);

	virtual void Update();
	virtual void Draw();

	~InfoWindow(void);

private:

};