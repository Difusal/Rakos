#include "SideBarWindow.h"
#include "RPG.h"

void SideBarWindow::Initialize() {
	defaultWindowY = 0;

	cameraX = &RPG::GetInstance()->cameraPosition[0];
	cameraY = &RPG::GetInstance()->cameraPosition[1];

	titleBarHeight = 24;
	width = 200-1;

	mouse = RPG::GetInstance()->Mouse;
	beingDragged = false;

	font = al_load_font(CalibriTTF, 15, ALLEGRO_ALIGN_CENTER);
	if (!font) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not create a side bar window.\nThe font file being used was not found.", "Your resources folder must be corrupt.\nPlease download the game again.\n\nPress OK to close the game.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
}

void SideBarWindow::CheckIfWindowIsBeingMoved() {
	// if window starts to be dragged
	if (mouse->leftMouseButtonHasJustBeenPressed && !beingDragged) {
		if (titleBarX <= mouse->x && mouse->x <= titleBarX+width && titleBarY <= mouse->y && mouse->y <= y) {
			cout << "Side bar window being dragged." << endl;
			beingDragged = true;
			titleBarYWhenDraggingStarted = titleBarY;
			draggingStartY = mouse->y;
		}
	}

	// if window stops being dragged
	if (mouse->left_mouse_button_released && beingDragged) {
		beingDragged = false;
	}
}

void SideBarWindow::UpdateBase() {
	CheckIfWindowIsBeingMoved();

	// if being dragged, move window to current mouse y coord
	if (beingDragged) {
		displacement = mouse->y - draggingStartY;
		titleBarY = titleBarYWhenDraggingStarted + displacement;
	}
	else
		titleBarY = defaultWindowY + 1 + *cameraY;

	titleBarX = ScreenWidth - width + *cameraX;
	
	x = titleBarX;
	y = titleBarY + titleBarHeight;
}

void SideBarWindow::DrawBase() {
	unsigned int alpha = 190;
	unsigned int rgb = 128;
	ALLEGRO_COLOR backgroundColor = al_map_rgba(rgb*alpha, rgb*alpha, rgb*alpha, alpha);

	// box background
	al_draw_filled_rectangle(titleBarX, titleBarY, x + width - 1, y + height, backgroundColor);

	// box title background
	al_draw_filled_rectangle(titleBarX, titleBarY, titleBarX + width - 1, y, DarkGray);
	
	// box title frame
	al_draw_line(titleBarX + width - 2, titleBarY, titleBarX + width - 2, y, DarkerGray, 2.0);
	al_draw_line(titleBarX, y - 2, titleBarX + width - 1, y - 2, DarkerGray, 2.0);
	al_draw_line(titleBarX + 1, titleBarY , titleBarX + 1, y, Gray, 2.0);
	al_draw_line(titleBarX, titleBarY + 1, titleBarX + width - 1, titleBarY + 1, Gray, 2.0);
	al_draw_pixel(titleBarX + 2, y - 1, DarkerGray);
	al_draw_pixel(titleBarX + width - 1, titleBarY + 2, DarkerGray);
	al_draw_rectangle(titleBarX, titleBarY, titleBarX + width, y, Black, 1.0);

	// box frame
	al_draw_rectangle(x, y, x + width, y + height, Black, 1.0);

	// title
	unsigned int yCorrection = 4;
	al_draw_text(font, Black, titleBarX + width/2.0 + 2, titleBarY+yCorrection + 1, ALLEGRO_ALIGN_CENTER, title.c_str());
	al_draw_text(font, White, titleBarX + width/2.0, titleBarY+yCorrection, ALLEGRO_ALIGN_CENTER, title.c_str());
}