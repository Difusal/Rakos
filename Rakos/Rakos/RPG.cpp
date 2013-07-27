#include "RPG.h"
#include "TutorialState.h"

/* generates random numbers */
int random_number (int min, int max) {
	max++;

	return ((rand() % (max-min)) + min);
}

void CameraUpdate(vector<vector<int> > & worldMap, float * cameraPosition, float x, float y, int width, int height) {
	cameraPosition[0] = -((ScreenWidth-200) / 2) + (x + width / 2); 
	cameraPosition[1] = -(ScreenHeight / 2) + (y + height / 2);

	if(cameraPosition[0] < 0)
		cameraPosition[0] = 0; 
	if(cameraPosition[1] < 0)
		cameraPosition[1] = 0;
	if(cameraPosition[0] > WorldBlockSize*worldMap[0].size() - (ScreenWidth-200))
		cameraPosition[0] = WorldBlockSize*worldMap[0].size() - (ScreenWidth-200);
	if(cameraPosition[1] > WorldBlockSize*worldMap.size() - ScreenHeight)
		cameraPosition[1] = WorldBlockSize*worldMap.size() - ScreenHeight;
}

bool boxCollision(float x, float y, float ex, float ey, int width, int height) {
	int x_correction = 15;
	int y_correction = 25;
	if (x + width - x_correction < ex || x > ex + width - x_correction ||
		y + height - y_correction < ey || y > ey + height - y_correction)
	{
		return false;
	}

	return true;
}

float calculateDistance(float p1_x, float p1_y, float p2_x, float p2_y) {
	return sqrt(pow(p2_y-p1_y, 2) + pow(p2_x-p1_x, 2));
}


RPG *RPG::instance = NULL;

RPG *RPG::GetInstance() {
	if (!instance)
	{
		instance = new RPG();
	}

	return instance;
}

void RPG::ChangeState (int newState) {
	if (state != -1)
	{
		states[state]->Terminate();
	}

	state = newState;

	states[state]->Initialize();
}


void RPG::CreateAllegroDisplay() {
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(ScreenWidth, ScreenHeight);
	if (!display)
	{
		al_show_native_message_box(display, "Error", "Display Settings", "Couldn't create a display.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	/* setting new window title */
	al_set_window_title(display, GameTitle);
}

void RPG::LoadFonts() {
	big_font = al_load_font(ConsolaTTF, 36, ALLEGRO_ALIGN_CENTER);
	medium_font = al_load_font(ConsolaTTF, 20, ALLEGRO_ALIGN_CENTER);
	small_font = al_load_font(ConsolaTTF, 14, ALLEGRO_ALIGN_CENTER);
	tiny_font = al_load_font(ConsolaTTF, 10, ALLEGRO_ALIGN_CENTER);
	if (!big_font || !medium_font || !small_font || !tiny_font)
	{
		al_show_native_message_box(display, "Error", "Could not load font file.", "Have you included the resources in the same directory of the program?", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
}

void RPG::Initialize() {
	cout << endl;
	cout << "#########################" << endl;
	cout << "##                     ##" << endl;
	cout << "##    STARTING GAME    ##" << endl;
	cout << "##                     ##" << endl;
	cout << "#########################" << endl;
	cout << endl;
	cout << "-------------" << endl;
	cout << "Activity Log:" << endl;
	cout << "-------------" << endl;

	cout << "Getting time seed for random numbers..." << endl;
	srand ((unsigned int) time(NULL));

	cout << "Starting Allegro 5..." << endl;
	if (!al_init())
	{ al_show_native_message_box(NULL, NULL, "Could not initialize Allegro 5", NULL, NULL, NULL); }

	cout << "Initializing add ons..." << endl;
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_acodec_addon();

	cout << "Installing devices..." << endl;
	al_install_mouse();
	al_install_keyboard();
	al_install_audio();

	cout << "Creating display..." << endl;
	CreateAllegroDisplay();

	cout << "Displaying loading game background..." << endl;
	loading_background = al_load_bitmap(LoadingGameBackgroundPath);
	if (!loading_background) {
		al_show_native_message_box(display, "Error", "Could not load loading game background bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	al_draw_bitmap(loading_background, 0, 0, NULL);
	al_flip_display();

	cout << "Hiding windows mouse cursor..." << endl;
	al_hide_mouse_cursor(display);

	cout << "Loading fonts..." << endl;
	LoadFonts();

	cout << "Creating timers..." << endl;
	timer = al_create_timer(1.0 / FPS);
	drawTimer = al_create_timer(1.0 / drawFPS);
	playerAnimTimer = al_create_timer(1.0 / drawFPS);

	cout << "Creating event queues..." << endl;
	event_queue = al_create_event_queue();

	cout << "Registering event sources..." << endl;
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(drawTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(playerAnimTimer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());	

	cout << "Stating how many sounds can play simultaneously..." << endl;
	al_reserve_samples(3);
	/*
	cout << "Loading audio samples..." << endl;
	lineClearSound = al_load_sample(LineClearSound);
	explosionSound = al_load_sample(ExplosionSound);
	themeSong = al_load_sample(ThemeSong);
	if (!themeSong) {
		al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load Tetris theme song.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}*/

	cout << "Initializing variables..." << endl;
	mouse = al_load_bitmap(MouseCursor);
	mouse_x = ScreenWidth;
	mouse_y = ScreenHeight;
	left_mouse_button_pressed = false;
	left_mouse_button_released = false;
	right_mouse_button_pressed = false;
	right_mouse_button_released = false;

	possible_double_press = false;
	double_press_counter = 0;

	done = false;
	draw = true;

	cout << "Starting timers..." << endl;
	al_start_timer(timer);
	al_start_timer(drawTimer);
	al_start_timer(playerAnimTimer);
}

void RPG::TrackMouse() {
	/* --- controlling left mouse button double press --- */
	if (possible_double_press && double_press_counter < FPS*1.5/4) {
		double_press_counter++;
	}
	else if (possible_double_press)	{
		possible_double_press = false;
		double_press_counter = 0;
	}

	/* --- tracking mouse --- */
	if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
		mouse_x = ev.mouse.x;
		mouse_y = ev.mouse.y;

		draw = true;
	}

	/* --- tracking button presses/releases --- */
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		if (ev.mouse.button &1) {
			//cout << "* Left mouse button pressed *" << endl;
			left_mouse_button_pressed = true;
			left_mouse_button_released = false;
			draw = true;
		}
		if (ev.mouse.button &2) {
			//cout << "* Right mouse button pressed *" << endl;
			right_mouse_button_pressed = true;
			right_mouse_button_released = false;
			draw = true;
		}
	}
	if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		if (ev.mouse.button &1) {
			if (possible_double_press) {
				cout << "* Left mouse button released(pressed) twice *" << endl;
				left_mouse_button_pressed_twice = true;
			}
			else
				cout << "* Left mouse button released *" << endl;

			possible_double_press = true;
			left_mouse_button_pressed = false;
			left_mouse_button_released = true;
			draw = true;
		}
		if (ev.mouse.button &2) {
			cout << "* Right mouse button released *" << endl;
			right_mouse_button_pressed = false;
			right_mouse_button_released = true;
			draw = true;
		}
	}
}

void RPG::start_game ()
{
	Initialize();

	states.push_back(new TutorialState());
	state = -1;
	ChangeState(Tutorial);

	cout << "Starting control cycle..." << endl;
	while (!done) {
		al_wait_for_event(event_queue, & ev);

		TrackMouse();

		/* --- UPDATING --- */
		states[state]->Update(&ev);

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			left_mouse_button_released = false;
			left_mouse_button_pressed_twice = false;
			right_mouse_button_released = false;

			draw = true;
		}

		/* --- DRAWING --- */
		if (draw && al_event_queue_is_empty(event_queue))
		{
			states[state]->Draw();
			
			/* -- mouse cursor -- */
			al_draw_bitmap(mouse, mouse_x, mouse_y, NULL);

			/*
			// mouse temp coords
			stringstream ss;
			ss << mouse_x << " " << mouse_y;
			al_draw_text(font, Yellow, 0, 0, NULL, ss.str().c_str());
			//cout << ss.str() << endl;
			// -----------------
			*/

			al_flip_display();
			al_clear_to_color(Black);
			draw = false;
		}

		/* if window is closed */
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			cout << "Close button pressed..." << endl;
			done = true;
		}
	}
	cout << "* done = true; *" << endl;

	Terminate();
}

void RPG::Terminate() {
	cout << "Deallocating memory and quitting..." << endl;

	/* fonts */
	al_destroy_font(big_font);
	al_destroy_font(medium_font);
	al_destroy_font(small_font);
	al_destroy_font(tiny_font);

	/* audio samples */

	/* event queue and timers */
	al_destroy_event_queue(event_queue);
	al_destroy_timer(playerAnimTimer);
	al_destroy_timer(drawTimer);
	al_destroy_timer(timer);
	al_destroy_display(display);

	/* bitmaps */
	al_destroy_bitmap(loading_background);
	al_destroy_bitmap(mouse);

	delete instance;
}