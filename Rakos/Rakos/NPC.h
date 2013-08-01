#pragma once

#include "stdIncludes.h"
#include "RPG.h"
#include "LivingBeing.h"

class NPC: public LivingBeing {
public:
	NPC(string Name, double P1_X, double P1_Y, double P2_X, double P2_Y, const char* Bitmap);
	NPC(string Name, double X, double Y, const char* Bitmap);

	~NPC(void);

private:
};