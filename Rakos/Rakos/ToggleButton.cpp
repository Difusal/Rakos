#include "ToggleButton.h"
#include "RPG.h"

ToggleButton::ToggleButton(const char *BitmapPath, unsigned int CenterX, unsigned int CenterY) {
	// default active value
	active = true;

	image = al_load_bitmap(BitmapPath);
	if (!image) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), ProgramTitle, "Error:", "Could not load a necessary image for a toggle button.\nPress OK to exit game.", NULL, ALLEGRO_MESSAGEBOX_WARN);
		exit(-1);
	}

	// setting button width and height
	width = al_get_bitmap_width(image);
	height = al_get_bitmap_height(image);

	// setting button coordinates
	x = CenterX - width/2.0;
	y = CenterY - height/2.0;

	// initializing bool values
	beingHovered = false;
	beingPressed = false;
	released = false;
}

void ToggleButton::Draw() {
	// if button is not active, do nothing
	if (!active)
		return;

	// if button is being hovered use a different button color
	ALLEGRO_COLOR buttonColor;
	if (beingPressed)
		buttonColor = DarkerGray;
	else if (beingHovered)
		buttonColor = DarkGray;
	else if (!beingPressed && !beingHovered)
		buttonColor = Gray;

	// drawing button background
	al_draw_filled_rectangle(x, y, x+width, y+height, buttonColor);

	// drawing image
	al_draw_bitmap(image, x, y, ALLEGRO_ALIGN_LEFT);

	// drawing button contour
	al_draw_rectangle(x, y, x+width, y+height, Black, 1.0);
}

ToggleButton::~ToggleButton(void) {
	// destroying image
	al_destroy_bitmap(image);
}