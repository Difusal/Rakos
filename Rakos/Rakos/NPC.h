#pragma once

#include "stdIncludes.h"
#include "RPG.h"
#include "LivingBeing.h"

class NPC: public LivingBeing {
public:
	NPC(string Name, double X, double Y, const char* Bitmap, bool AlwaysInactive = false);
	
	~NPC(void);
};