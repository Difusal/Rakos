#pragma once

#include "SideBarWindow.h"

class EquipmentWindow: public SideBarWindow {
public:
	EquipmentWindow(string Title);

	virtual void Update();
	virtual void Draw();

	~EquipmentWindow(void);

private:
	unsigned int weaponLabelX, shieldLabelX;
	unsigned int labelsY;
};