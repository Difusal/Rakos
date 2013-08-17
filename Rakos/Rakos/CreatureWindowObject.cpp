#include "CreatureWindowObject.h"
#include "RPG.h"

CreatureWindowObject::CreatureWindowObject() {
	active = false;
	width = 200;
	height = 40;

	barWidth = 0.75*width;
	barHeight = 10;

	font = al_load_font(CalibriTTF, 15, ALLEGRO_ALIGN_CENTER);
	if (!font) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not create a side bar window.\nThe font file being used was not found.", "Your resources folder must be corrupt.\nPlease download the game again.\n\nPress OK to close the game.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
}


void CreatureWindowObject::Activate(LivingBeing *being) {
	active = true;

	sprite = being->bitmap;
	label = being->name;
	HP = &being->hp;
	maxHP = &being->maxHp;
}

void CreatureWindowObject::Update(unsigned int x, unsigned int y) {
	if (!active)
		return;

	this->x = x;
	this->y = y;

	thumbnailX = x + 4;
	thumbnailY = y + 4;
	thumbnailSize = al_get_bitmap_width(sprite)/4.0;

	labelX = x + 40 + 4;
	labelY = y + 4;

	barX = labelX;
	barY = y + 24;
	barCenterX = x+40 + (width-40)/2.0;
	if (*HP >= 0.5*(*maxHP))
		barFillColor = Green;
	else if (*HP >= 0.25*(*maxHP))
		barFillColor = Yellow;
	else
		barFillColor = Red;
}

void CreatureWindowObject::Draw() {
	if (!active)
		return;

	// Drawing thumbnail background
	al_draw_filled_rectangle(thumbnailX-2, thumbnailY-2, thumbnailX+thumbnailSize+2, thumbnailY+thumbnailSize+2, DarkerGray);

	// Drawing thumbnail frame
	al_draw_rectangle(thumbnailX, thumbnailY, thumbnailX+thumbnailSize+1, thumbnailY+thumbnailSize+1, DarkGray, 1.0);

	// Drawing thumbnail
	al_draw_bitmap_region(sprite, 32, 0, 32, 32, thumbnailX, thumbnailY, ALLEGRO_ALIGN_CENTER);

	// Drawing label
	al_draw_text(font, Black, labelX + 1, labelY + 2, ALLEGRO_ALIGN_LEFT, label.c_str());
	al_draw_text(font, White, labelX, labelY, ALLEGRO_ALIGN_LEFT, label.c_str());

	// Drawing life bar
	DrawBar(barY, *HP, *maxHP, barFillColor);
}

void CreatureWindowObject::DrawBar(unsigned int barY, unsigned int currentValue, unsigned int maxValue, ALLEGRO_COLOR fillColor) {
	double percentage = 100.0 * currentValue / maxValue;
	unsigned int fillWidthInpixels = barWidth * percentage / 100.0;

	al_draw_filled_rectangle(barCenterX - barWidth/2.0, barY, barCenterX + barWidth/2.0, barY + barHeight, Black);
	al_draw_rectangle(barCenterX-barWidth/2.0, barY+1, barCenterX+barWidth/2.0, barY + barHeight, DarkerGray, 1.0);
	al_draw_filled_rectangle(barCenterX-barWidth/2.0, barY+1, barCenterX-barWidth/2.0 + fillWidthInpixels - 1, barY+barHeight-1, fillColor);
}


CreatureWindowObject::~CreatureWindowObject(void) {
	delete HP;
	delete maxHP;
	delete font;
}