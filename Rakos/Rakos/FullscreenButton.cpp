#include "FullscreenButton.h"
#include "RPG.h"

FullscreenButton::FullscreenButton(const char *BitmapPath, unsigned int CenterX, unsigned int CenterY) {
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

	// loading font
	font = al_load_font(CalibriTTF, 10, ALLEGRO_ALIGN_CENTER);
}

void FullscreenButton::PositionOnUpperRightCorner() {
	x = RPG::GetInstance()->cameraPosition[0] + RPG::GetInstance()->ScreenWidth - width;
	y = RPG::GetInstance()->cameraPosition[1];
}

void FullscreenButton::Draw() {
	// if button is not active, do nothing
	if (!active)
		return;

	// drawing image
	al_draw_bitmap(image, x, y, ALLEGRO_ALIGN_LEFT);

	// drawing button contour
	if (beingHovered)
		al_draw_rounded_rectangle(x+2, y+1, x+width-1, y+height-2, 10, 10, Yellow, 1.0);
}

FullscreenButton::~FullscreenButton(void) {
	// destroying image
	al_destroy_bitmap(image);
}