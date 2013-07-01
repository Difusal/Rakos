#pragma once

#include "MovingObjectSon.h"
#include "stdIncludes.h"
#include "StateControl.h"

class NPC: public MovingObjectSon
{
public:
	NPC(string Name, double P1_X, double P1_Y, double P2_X, double P2_Y, const char* Bitmap);
	NPC(string Name, double X, double Y, const char* Bitmap);

	~NPC(void);

private:
};