#include "ConfirmationDialog.h"
#include "RPG.h"

ConfirmationDialog::ConfirmationDialog(string Title, vector<string> Text) {
	title = Title;
	text = Text;
	font = al_load_font(CalibriTTF, 16, ALLEGRO_ALIGN_CENTER);
	if (!font) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not create a game text box.\nThe font file being used was not found.", "Your resources folder must be corrupt.\nPlease download the game again.\n\nPress OK to close the game.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	width = (getLengthOfBiggestSentenceOnVector(text)+1) * font->height/2.8;
	height = (text.size() + 1) * font->height;

	x = 600/2 - width/2;
	y = RPG::GetInstance()->ScreenHeight/2 - height/2;

	// defining dialog buttons
	buttonsWidth = 35;
	buttonsHeight = font->height - 0.1*font->height;
	spaceBetweenButtons = 5;
	Yes = new ConfirmationDialogButton("Yes", x+width-buttonsWidth+13-buttonsWidth-spaceBetweenButtons, y+height+spaceBetweenButtons+buttonsHeight/2, buttonsWidth, buttonsHeight, 15);
	No = new ConfirmationDialogButton("No", x+width-buttonsWidth+13, y+height+spaceBetweenButtons+buttonsHeight/2, buttonsWidth, buttonsHeight, 15);

	Close();
}

int ConfirmationDialog::Update() {
	// skipping if not active
	if (!active)
		return 2;

	realX = x + RPG::GetInstance()->cameraPosition[0];
	realY = y + RPG::GetInstance()->cameraPosition[1];

	Yes->Update();
	if (Yes->wasReleased()) {
		Close();
		return 1;
	}

	No->Update();
	if (No->wasReleased()) {
		Close();
		return 0;
	}

	return 2;
}

void ConfirmationDialog::Draw() {
	// skipping if not active
	if (!active)
		return;

	// title background
	al_draw_filled_rectangle(realX, realY-1.3*font->height, realX + width, realY, al_map_rgba(0, 0, 30, 230));
	// text background
	al_draw_filled_rectangle(realX, realY, realX + width, realY + height, al_map_rgba(0, 0, 30, 200));
	// buttons background
	al_draw_filled_rectangle(realX, realY + height, realX + width, realY + height + Yes->Height()+2*spaceBetweenButtons, al_map_rgba(0, 0, 30, 230));

	// title frame
	al_draw_rectangle(realX+3, realY-1.3*font->height+3, realX+width-3, realY-3, DarkGray, 1.0);
	al_draw_rectangle(realX+2, realY-1.3*font->height+2, realX+width-2, realY-2, Gray, 1.0);
	al_draw_rectangle(realX+1, realY-1.3*font->height+1, realX+width-1, realY-1, LightGray, 1.0);
	// dialog frame
	al_draw_rectangle(realX, realY-1.3*font->height, realX+width, realY+height + Yes->Height()+2*spaceBetweenButtons, Black, 1.0);
	// text frame
	al_draw_rectangle(realX, realY, realX+width, realY+height, Black, 1.0);

	// title
	al_draw_text(font, White, realX + width/2, realY-font->height, ALLEGRO_ALIGN_CENTER, title.c_str());

	// text
	for (unsigned int i = 0; i < text.size(); i++) {
		al_draw_text(font, Black, realX+font->height/2.8 + 1, realY+i*font->height+1+font->height/2 + 1, ALLEGRO_ALIGN_LEFT, text[i].c_str());
		al_draw_text(font, White, realX+font->height/2.8, realY+i*font->height+1+font->height/2, ALLEGRO_ALIGN_LEFT, text[i].c_str());
	}

	// drawing buttons
	Yes->Draw();
	No->Draw();
}

ConfirmationDialog::~ConfirmationDialog( void ) {
	delete Yes;
	delete No;
	al_destroy_font(font);
}