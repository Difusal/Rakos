#include "Form.h"
#include "RPG.h"

#define formBackground al_map_rgb(235, 235, 235)
#define activeFormContour al_map_rgb(255, 165, 0)
#define formContourRadius 3

Form::Form(string Label, unsigned int X, unsigned int Y, bool HideText) {
	label = al_ustr_new(Label.c_str());
	x = X;
	y = Y;

	height = 0.06*RPG::GetInstance()->ScreenHeight;
	width = 9*height;

	active = false;
	hideCharacters = HideText;

	font = al_load_font(CalibriTTF, 0.6*height, NULL);

	text = al_ustr_new("");
	textX = x+0.4*font->height;
	textY = y+height-font->height;
}

void Form::Update(ALLEGRO_EVENT *ev) {
	// checking if form was selected or unselected
	if (RPG::GetInstance()->Mouse->leftMouseButtonReleased) {
		if (x < RPG::GetInstance()->Mouse->x && RPG::GetInstance()->Mouse->x < x+width && y < RPG::GetInstance()->Mouse->y && RPG::GetInstance()->Mouse->y < y+height)
			active = true;
		else
			active = false;
	}

	if (active) {
		// scanning keyboard hits
		al_get_keyboard_state(&keyboardState);

		// if there is any keyboard input
		if(ev->type == ALLEGRO_EVENT_KEY_CHAR) {

			// if string can still be bigger
			if (al_ustr_size(text) < 20) {

				// if shift is being held, append capital letters
				if (al_key_down(&keyboardState, ALLEGRO_KEY_RSHIFT) || al_key_down(&keyboardState, ALLEGRO_KEY_LSHIFT)) {
					cout << "* Shift is being held *" << endl;

					switch(ev->keyboard.keycode) {
						// LETTERS
					case ALLEGRO_KEY_Q: { al_ustr_append_cstr(text, "Q"); break; }
					case ALLEGRO_KEY_W: { al_ustr_append_cstr(text, "W"); break; }
					case ALLEGRO_KEY_E: { al_ustr_append_cstr(text, "E"); break; }
					case ALLEGRO_KEY_R: { al_ustr_append_cstr(text, "R"); break; }
					case ALLEGRO_KEY_T: { al_ustr_append_cstr(text, "T"); break; }
					case ALLEGRO_KEY_Y: { al_ustr_append_cstr(text, "Y"); break; }
					case ALLEGRO_KEY_U: { al_ustr_append_cstr(text, "U"); break; }
					case ALLEGRO_KEY_I: { al_ustr_append_cstr(text, "I"); break; }
					case ALLEGRO_KEY_O: { al_ustr_append_cstr(text, "O"); break; }
					case ALLEGRO_KEY_P: { al_ustr_append_cstr(text, "P"); break; }
					case ALLEGRO_KEY_A: { al_ustr_append_cstr(text, "A"); break; }
					case ALLEGRO_KEY_S: { al_ustr_append_cstr(text, "S"); break; }
					case ALLEGRO_KEY_D: { al_ustr_append_cstr(text, "D"); break; }
					case ALLEGRO_KEY_F: { al_ustr_append_cstr(text, "F"); break; }
					case ALLEGRO_KEY_G: { al_ustr_append_cstr(text, "G"); break; }
					case ALLEGRO_KEY_H: { al_ustr_append_cstr(text, "H"); break; }
					case ALLEGRO_KEY_J: { al_ustr_append_cstr(text, "J"); break; }
					case ALLEGRO_KEY_K: { al_ustr_append_cstr(text, "K"); break; }
					case ALLEGRO_KEY_L: { al_ustr_append_cstr(text, "L"); break; }
					case ALLEGRO_KEY_Z: { al_ustr_append_cstr(text, "Z"); break; }
					case ALLEGRO_KEY_X: { al_ustr_append_cstr(text, "X"); break; }
					case ALLEGRO_KEY_C: { al_ustr_append_cstr(text, "C"); break; }
					case ALLEGRO_KEY_V: { al_ustr_append_cstr(text, "V"); break; }
					case ALLEGRO_KEY_B: { al_ustr_append_cstr(text, "B"); break; }
					case ALLEGRO_KEY_N: { al_ustr_append_cstr(text, "N"); break; }
					case ALLEGRO_KEY_M: { al_ustr_append_cstr(text, "M"); break; }

										// SPECIAL CHARS
					case ALLEGRO_KEY_FULLSTOP: { al_ustr_append_cstr(text, ":"); break; }
					case ALLEGRO_KEY_MINUS: { al_ustr_append_cstr(text, "_"); break; }
					}
				}
				else {
					switch(ev->keyboard.keycode) {
						// LETTERS
					case ALLEGRO_KEY_Q: { al_ustr_append_cstr(text, "q"); break; }
					case ALLEGRO_KEY_W: { al_ustr_append_cstr(text, "w"); break; }
					case ALLEGRO_KEY_E: { al_ustr_append_cstr(text, "e"); break; }
					case ALLEGRO_KEY_R: { al_ustr_append_cstr(text, "r"); break; }
					case ALLEGRO_KEY_T: { al_ustr_append_cstr(text, "t"); break; }
					case ALLEGRO_KEY_Y: { al_ustr_append_cstr(text, "y"); break; }
					case ALLEGRO_KEY_U: { al_ustr_append_cstr(text, "u"); break; }
					case ALLEGRO_KEY_I: { al_ustr_append_cstr(text, "i"); break; }
					case ALLEGRO_KEY_O: { al_ustr_append_cstr(text, "o"); break; }
					case ALLEGRO_KEY_P: { al_ustr_append_cstr(text, "p"); break; }
					case ALLEGRO_KEY_A: { al_ustr_append_cstr(text, "a"); break; }
					case ALLEGRO_KEY_S: { al_ustr_append_cstr(text, "s"); break; }
					case ALLEGRO_KEY_D: { al_ustr_append_cstr(text, "d"); break; }
					case ALLEGRO_KEY_F: { al_ustr_append_cstr(text, "f"); break; }
					case ALLEGRO_KEY_G: { al_ustr_append_cstr(text, "g"); break; }
					case ALLEGRO_KEY_H: { al_ustr_append_cstr(text, "h"); break; }
					case ALLEGRO_KEY_J: { al_ustr_append_cstr(text, "j"); break; }
					case ALLEGRO_KEY_K: { al_ustr_append_cstr(text, "k"); break; }
					case ALLEGRO_KEY_L: { al_ustr_append_cstr(text, "l"); break; }
					case ALLEGRO_KEY_Z: { al_ustr_append_cstr(text, "z"); break; }
					case ALLEGRO_KEY_X: { al_ustr_append_cstr(text, "x"); break; }
					case ALLEGRO_KEY_C: { al_ustr_append_cstr(text, "c"); break; }
					case ALLEGRO_KEY_V: { al_ustr_append_cstr(text, "v"); break; }
					case ALLEGRO_KEY_B: { al_ustr_append_cstr(text, "b"); break; }
					case ALLEGRO_KEY_N: { al_ustr_append_cstr(text, "n"); break; }
					case ALLEGRO_KEY_M: { al_ustr_append_cstr(text, "m"); break; }

						// SPECIAL CHARS
					case ALLEGRO_KEY_FULLSTOP: { al_ustr_append_cstr(text, "."); break; }
					case ALLEGRO_KEY_MINUS: { al_ustr_append_cstr(text, "-"); break; }
					}
				}

				switch(ev->keyboard.keycode) {
					// NUMBERS
				case ALLEGRO_KEY_0: case ALLEGRO_KEY_PAD_0: { al_ustr_append_cstr(text, "0"); break; }
				case ALLEGRO_KEY_1: case ALLEGRO_KEY_PAD_1: { al_ustr_append_cstr(text, "1"); break; }
				case ALLEGRO_KEY_2: case ALLEGRO_KEY_PAD_2: { al_ustr_append_cstr(text, "2"); break; }
				case ALLEGRO_KEY_3: case ALLEGRO_KEY_PAD_3: { al_ustr_append_cstr(text, "3"); break; }
				case ALLEGRO_KEY_4: case ALLEGRO_KEY_PAD_4: { al_ustr_append_cstr(text, "4"); break; }
				case ALLEGRO_KEY_5: case ALLEGRO_KEY_PAD_5: { al_ustr_append_cstr(text, "5"); break; }
				case ALLEGRO_KEY_6: case ALLEGRO_KEY_PAD_6: { al_ustr_append_cstr(text, "6"); break; }
				case ALLEGRO_KEY_7: case ALLEGRO_KEY_PAD_7: { al_ustr_append_cstr(text, "7"); break; }
				case ALLEGRO_KEY_8: case ALLEGRO_KEY_PAD_8: { al_ustr_append_cstr(text, "8"); break; }
				case ALLEGRO_KEY_9: case ALLEGRO_KEY_PAD_9: { al_ustr_append_cstr(text, "9"); break; }

					// SPECIAL CHARS
				case ALLEGRO_KEY_SPACE: { al_ustr_append_cstr(text, " "); break; }
				}
			}

			switch(ev->keyboard.keycode) {
				// KEYS THAT WORK EVEN IF STRING IS MAXIMUM SIZE
			case ALLEGRO_KEY_BACKSPACE: { al_ustr_remove_chr(text, al_ustr_offset(text, -1)); break; }
			}
		}
	}
}

void Form::Draw() {
	// drawing background
	al_draw_filled_rounded_rectangle(x, y, x+width, y+height, formContourRadius, formContourRadius, formBackground);

	if (al_ustr_equal(text, al_ustr_new("")))
		al_draw_ustr(font, Gray, textX, textY, ALLEGRO_ALIGN_LEFT, label);
	else
		al_draw_ustr(font, Black, textX, textY, ALLEGRO_ALIGN_LEFT, text);

	// drawing contour
	al_draw_rounded_rectangle(x-1, y-1, x+width, y+height, formContourRadius, formContourRadius, Gray, 2.0);
	if (active)
		al_draw_rounded_rectangle(x, y, x+width-1, y+height-1, formContourRadius-1, formContourRadius-1, activeFormContour, 2.0);
}

Form::~Form(void) {
	// destroying font
	al_destroy_font(font);

	// destroying allegro ustrs
	al_ustr_free(label);
	al_ustr_free(text);
}