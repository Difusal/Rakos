#pragma once

#include "MovingObjectSon.h"
#include "stdIncludes.h"
#include "StateControl.h"

class NPC: public MovingObjectSon
{
public:
	//NPC(void);
	NPC(const char* Bitmap, double P1_X, double P1_Y, double P2_X, double P2_Y);
	NPC(const char* Bitmap, double P1_X, double P1_Y);

	~NPC(void);

private:
};