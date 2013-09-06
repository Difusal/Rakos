#pragma once

#include "BasicButton.h"

class MenuButton: public BasicButton {
public:
	MenuButton(string Label, unsigned int CenterX, unsigned int CenterY, unsigned int Width, unsigned int Height, unsigned int FontSize = 0);
	void Draw();
	~MenuButton(void);
};