#pragma once

#include "MovingObjectSon.h"
#include "stdIncludes.h"
#include "StateControl.h"

class Rabbit: public MovingObjectSon
{
public:
	Rabbit(double P1_X, double P1_Y, double P2_X, double P2_Y);

	~Rabbit(void);

private:
};