#pragma once

#include "stdIncludes.h"
#include "BasicButton.h"

class ConfirmationDialogButton: public BasicButton {
public:
	ConfirmationDialogButton(string Label, unsigned int CenterX, unsigned int CenterY, unsigned int Width, unsigned int Height, unsigned int FontSize = 0);
	void Draw();
	~ConfirmationDialogButton(void);
};