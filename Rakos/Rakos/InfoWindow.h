#pragma once

#include "SideBarWindow.h"

class InfoWindow: public SideBarWindow {
public:
	InfoWindow(string Title);

	virtual void Update();
	virtual void Draw();

	void DrawBar(unsigned int barY, unsigned int currentValue, unsigned int maxValue, ALLEGRO_COLOR fillColor);

	~InfoWindow(void);

private:
	unsigned int barWidth, barHeight;
	unsigned int windowCenterX;

	unsigned int labelsX;
	string hpLabel;
	unsigned int hpLabelY, hpBarY;
	ALLEGRO_COLOR hpBarFillColor;
	string mpLabel;
	unsigned int mpLabelY, mpBarY;
	ALLEGRO_COLOR mpBarFillColor;
	string levelLabel;
	unsigned int levelLabelY, levelBarY;
	ALLEGRO_COLOR levelBarFillColor;
	string goldLabel;
	unsigned int goldLabelY;

	stringstream ss;
};