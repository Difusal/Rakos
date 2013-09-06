#include "FlagButton.h"
#include "RPG.h"

FlagButton::FlagButton(string Label, const char *FlagBitmapPath, unsigned int CenterX, unsigned int CenterY, unsigned int Width, unsigned int Height) {
	// default active value
	active = true;

	label = Label;
	font = al_load_font(CalibriTTF, 0.2*Height, ALLEGRO_ALIGN_CENTER);

	flag = al_load_bitmap(FlagBitmapPath);
	if (!flag)
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Language Menu warning.", "Could not load a flag bitmap.\nPress OK to continue anyway.", NULL, ALLEGRO_MESSAGEBOX_WARN);

	// setting button coordinates
	x = CenterX - Width/2.0;
	y = CenterY - Height/2.0;

	// setting button width and height
	width = Width;
	height = Height;

	// initializing bool values
	beingHovered = false;
	beingPressed = false;
	released = false;
}

void FlagButton::Draw() {
	// if button is not active, do nothing
	if (!active)
		return;

	// printing label
	al_draw_text(font, White, x + Width()/2, y + Height()/2 - font->height/2, ALLEGRO_ALIGN_CENTER, label.c_str());

	// drawing flag
	if (flag)
		al_draw_scaled_bitmap(flag, 0, 0, al_get_bitmap_width(flag), al_get_bitmap_height(flag), x, y, width, height, ALLEGRO_ALIGN_LEFT);

	// drawing button contour
	if (beingHovered)
		al_draw_rectangle(x+1, y+1, x+width, y+height, Yellow, 1.0);
}

FlagButton::~FlagButton(void) {
	// destroying bitmap
	al_destroy_bitmap(flag);
}