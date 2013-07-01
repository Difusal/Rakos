#pragma once

#include "MovingObject.h"
#include "stdIncludes.h"

class MovingObjectSon: public MovingObject
{
public:
	MovingObjectSon(void);

	double getP1_x() { return p1_x; }
	double getP1_y() { return p1_y; }
	double getP2_x() { return p2_x; }
	double getP2_y() { return p2_y; }
	void setP1_x(double x) { p1_x = x; }
	void setP1_y(double y) { p1_y = y; }
	void setP2_x(double x) { p2_x = x; }
	void setP2_y(double y) { p2_y = y; }

	~MovingObjectSon(void);

private:
	double p1_x, p1_y;
	double p2_x, p2_y;

	friend class NPC;
	friend class Rabbit;
};