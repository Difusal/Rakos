#include "InfoWindow.h"
#include "RPG.h"

InfoWindow::InfoWindow(string Title) {
	Initialize();

	title = Title;
}


void InfoWindow::Update() {
	UpdateBase();

	windowCenterX = x + width/2.0;

	barWidth = 0.9*width;
	barHeight = 10;

	labelsX = windowCenterX - barWidth/2.0;

	ss.str(string());
	ss << RPG::GetInstance()->GetPlayer()->getHP() << "/" << RPG::GetInstance()->GetPlayer()->getMaxHP();
	hpLabel = ss.str();
	hpLabelY = y + font->height/2.0;
	hpBarY = hpLabelY + font->height;
	if (RPG::GetInstance()->GetPlayer()->getHP() >= 0.5*RPG::GetInstance()->GetPlayer()->getMaxHP())
		hpBarFillColor = Green;
	else if (RPG::GetInstance()->GetPlayer()->getHP() >= 0.25*RPG::GetInstance()->GetPlayer()->getMaxHP())
		hpBarFillColor = Yellow;
	else
		hpBarFillColor = Red;

	// EDIT THIS ////////////////////////////////////////
	ss.str(string());
	ss << 10 << "/" << RPG::GetInstance()->GetPlayer()->getMaxHP();
	mpLabel = ss.str();
	mpLabelY = hpBarY+barHeight + font->height/2.0;
	mpBarY = mpLabelY + font->height;
	mpBarFillColor = Blue;

	ss.str(string());
	ss << "7" << " (" << "25" << "%)";
	levelLabel = ss.str();
	levelLabelY = mpBarY+barHeight + font->height/2.0;
	levelBarY = levelLabelY + font->height;
	levelBarFillColor = Red;

	ss.str(string());
	switch (RPG::GetInstance()->LanguageBeingUsed) {
	case _English:
		ss << "Gold:  ";
		break;
	case _Portuguese:
		ss << "Dinheiro:  ";
		break;
	}
	ss << 39256;
	goldLabel = ss.str();
	goldLabelY = levelBarY+barHeight + font->height/2.0;

	height = (goldLabelY + font->height + font->height/2.0) - y;
}

void InfoWindow::Draw() {
	DrawBase();

	// Printing HP data
	al_draw_text(font, White, labelsX, hpLabelY, ALLEGRO_ALIGN_LEFT, "HP:");
	al_draw_text(font, White, windowCenterX, hpLabelY, ALLEGRO_ALIGN_CENTER, hpLabel.c_str());
	DrawBar(hpBarY, RPG::GetInstance()->GetPlayer()->getHP(), RPG::GetInstance()->GetPlayer()->getMaxHP(), hpBarFillColor);

	// Printing MP data
	al_draw_text(font, White, labelsX, mpLabelY, ALLEGRO_ALIGN_LEFT, "MP:");
	al_draw_text(font, White, windowCenterX, mpLabelY, ALLEGRO_ALIGN_CENTER, mpLabel.c_str());
	DrawBar(mpBarY, 10, RPG::GetInstance()->GetPlayer()->getMaxHP(), mpBarFillColor);

	// Printing Level data
	string str;
	switch (RPG::GetInstance()->LanguageBeingUsed) {
	case _English:
		str = "Level:";
		break;
	case _Portuguese:
		str = "Nivel:";
		break;
	}
	al_draw_text(font, White, labelsX, levelLabelY, ALLEGRO_ALIGN_LEFT, str.c_str());
	al_draw_text(font, White, windowCenterX, levelLabelY, ALLEGRO_ALIGN_CENTER, levelLabel.c_str());
	DrawBar(levelBarY, 25, 100, levelBarFillColor);

	// Printing gold coins data
	al_draw_text(font, White, labelsX, goldLabelY, ALLEGRO_ALIGN_LEFT, goldLabel.c_str());
}

void InfoWindow::DrawBar(unsigned int barY, unsigned int currentValue, unsigned int maxValue, ALLEGRO_COLOR fillColor) {
	double percentage = 100.0 * currentValue / maxValue;
	unsigned int fillWidthInpixels = barWidth * percentage / 100.0;

	//windowCenterX+barWidth/2.0 - 1
	al_draw_filled_rectangle(windowCenterX-barWidth/2.0, barY, windowCenterX + barWidth/2.0, barY + barHeight, Black);
	al_draw_rectangle(windowCenterX-barWidth/2.0, barY+1, windowCenterX+barWidth/2.0 - 1, barY + barHeight, DarkerGray, 1.0);
	al_draw_filled_rectangle(windowCenterX-barWidth/2.0 + 1, barY+1, windowCenterX-barWidth/2.0 + fillWidthInpixels, barY+barHeight-1, fillColor);
}



InfoWindow::~InfoWindow(void) {
	delete cameraX;
	delete cameraY;
	al_destroy_font(font);
}