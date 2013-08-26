#include "Editor.h"

#include "MenuState.h"
#include "EditingState.h"

Editor *Editor::instance = NULL;

Editor *Editor::GetInstance() {
	if (!instance)
		instance = new Editor();

	return instance;
}

void Editor::ChangeState(EditorState newState) {
	// if there was no state before, do not terminate a state which was not even initialized
	if (state != -1)
		states[state]->Terminate();

	state = newState;
	states[state]->Initialize();
}

void Editor::StartAllegro5() {
	cout << "Starting Allegro 5..." << endl;
	if (!al_init())
		al_show_native_message_box(NULL, NULL, "Could not initialize Allegro 5", NULL, NULL, NULL);

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
}

void Editor::CreateAllegroDisplay() {
	cout << "Creating display..." << endl;
	
	// specifying program to run on full screen
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);

	// getting monitor info
	ALLEGRO_DISPLAY_MODE disp_data;
	al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

	// setting screen width and height
	ScreenWidth = disp_data.width;
	ScreenHeight = disp_data.height;

	// creating display
	display = al_create_display(ScreenWidth, ScreenHeight);

	// if display was not loaded correctly, show error message and quit program
	if (!display) {
		al_show_native_message_box(display, "Error", "Display Settings", "Couldn't create a display.\nQuitting game.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	// changing window title
	al_set_window_title(display, ProgramTitle);

}

void Editor::LoadFonts() {
	cout << "Loading fonts..." << endl;

	extraLargeFont = al_load_font(CalibriTTF, 50, ALLEGRO_ALIGN_CENTER);
	fonts.push_back(extraLargeFont);

	largeFont = al_load_font(CalibriTTF, 30, ALLEGRO_ALIGN_CENTER);
	fonts.push_back(largeFont);

	mediumFont = al_load_font(CalibriTTF, 15, ALLEGRO_ALIGN_CENTER);
	fonts.push_back(mediumFont);


	// checking if every font was loaded correctly
	for (unsigned int i = 0; i < fonts.size(); i++) {
		if (!fonts[i]) {
			al_show_native_message_box(display, "Error", "Could not load font file.", "Have you included the resources in the same directory of the program?", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			exit(-1);
		}
	}
}

void Editor::DisplayLoadingSplashScreen() {
	cout << "Displaying loading game background..." << endl;
	
	// setting background color
	al_clear_to_color(DarkGray);

	// printing text
	al_draw_text(largeFont, Black, ScreenWidth/2.0 + 1, ScreenHeight/2.0 + 2, ALLEGRO_ALIGN_CENTER, "Loading...");
	al_draw_text(largeFont, White, ScreenWidth/2.0, ScreenHeight/2.0, ALLEGRO_ALIGN_CENTER, "Loading...");

	// flipping display
	al_flip_display();
}

void Editor::StartMouseCursor() {
	cout << "Starting mouse cursor..." << endl;
	Mouse = new MouseCursor();
}

void Editor::CreateTimers() {
	cout << "Creating timers..." << endl;

	timer = al_create_timer(1.0 / FPS);
	timers.push_back(timer);
}

void Editor::CreateEventQueue() {
	cout << "Creating event queues..." << endl;
	eventQueue = al_create_event_queue();

	cout << "Registering event sources..." << endl;
	al_register_event_source(eventQueue, al_get_display_event_source(display));
	al_register_event_source(eventQueue, al_get_mouse_event_source());
	al_register_event_source(eventQueue, al_get_keyboard_event_source());
	for (unsigned int i = 0; i < timers.size(); i++)
		al_register_event_source(eventQueue, al_get_timer_event_source(timers[i]));
}

void Editor::LoadSoundSamples() {
	cout << "Stating how many sounds can play simultaneously..." << endl;
	al_reserve_samples(3);

	cout << "Loading audio samples..." << endl;
	/*
	lineClearSound = al_load_sample(LineClearSound);
	explosionSound = al_load_sample(ExplosionSound);
	themeSong = al_load_sample(ThemeSong);
	if (!themeSong) {
	al_show_native_message_box(Tetris::GetInstance()->GetDisplay(), "Error", "Could not load Tetris theme song.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	exit(-1);
	}*/
}

void Editor::InitializeVariables() {
	cout << "Initializing variables..." << endl;
	cameraPosition[0] = 0;
	cameraPosition[1] = 0;

	done = false;
	draw = true;
	creatingNewMap = false;
}

void Editor::StartTimers() {
	cout << "Starting timers..." << endl;
	for (unsigned int i = 0; i < timers.size(); i++)
		al_start_timer(timers[i]);
}


void Editor::StartControlCycle() {
	Initialize();

	states.push_back(new MenuState());
	states.push_back(new EditingState());
	state = -1;
	ChangeState(_Menu);

	cout << "Starting game control cycle..." << endl;
	while (!done) {
		al_wait_for_event(eventQueue, &ev);

		Update();

		Draw();
	}

	Terminate();
}

void Editor::Initialize() {
	cout << endl;
	cout << "###########################" << endl;
	cout << "##                       ##" << endl;
	cout << "##    STARTING EDITOR    ##" << endl;
	cout << "##                       ##" << endl;
	cout << "###########################" << endl;
	cout << endl;
	cout << "-------------" << endl;
	cout << "Activity Log:" << endl;
	cout << "-------------" << endl;

	cout << "Getting time seed for random numbers..." << endl;
	srand ((unsigned int) time(NULL));

	StartAllegro5();
	CreateAllegroDisplay();
	LoadFonts();
	DisplayLoadingSplashScreen();
	StartMouseCursor();
	CreateTimers();
	CreateEventQueue();
	LoadSoundSamples();
	InitializeVariables();
	StartTimers();
}

void Editor::Update() {
	// if window is closed on dedicated button (upper right corner)
	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		cout << "Close button pressed..." << endl;
		done = true;
	}

	// updating mouse
	draw = Mouse->Update(&ev);

	// updating current state
	states[state]->Update(&ev);

	// correcting mouse position due to camera movement
	if (ev.type != ALLEGRO_EVENT_MOUSE_AXES)
		draw = Mouse->CorrectMousePosition();

	// setting all mouse release values to false on timer event
	if (ev.type == ALLEGRO_EVENT_TIMER) {
		Mouse->SetAllReleaseValuesToFalse();
		draw = true;
	}
}

void Editor::Draw() {
	if (draw && al_event_queue_is_empty(eventQueue)) {
		// drawing current state
		states[state]->Draw();

		if (state == _Editing) {
			// displaying mouse coords if editing map
			stringstream ss;
			ss << " x:" << Mouse->x << "  y:" << Mouse->y;
			al_draw_text(mediumFont, Yellow, cameraPosition[0], cameraPosition[1], NULL, ss.str().c_str());
			ss.str(string());
			ss << " block x:" << Mouse->x/WorldBlockSize << "  block y:" << Mouse->y/WorldBlockSize;
			al_draw_text(mediumFont, Yellow, cameraPosition[0], cameraPosition[1]+mediumFont->height, NULL, ss.str().c_str());
		}		

		// flipping display and preparing buffer for next cycle
		al_flip_display();
		al_clear_to_color(DarkGray);
		draw = false;
	}
}

void Editor::Terminate() {
	cout << "Deallocating memory and quitting..." << endl;

	// deleting mouse cursor
	delete Mouse;

	// destroying fonts
	for (unsigned int i = 0; i < fonts.size(); i++)
		al_destroy_font(fonts[i]);
	fonts.clear();

	// destroying event queue
	al_destroy_event_queue(eventQueue);

	// destroying display
	al_destroy_display(display);

	// destroying timers
	for (unsigned int i = 0; i < timers.size(); i++)
		al_destroy_timer(timers[i]);
	timers.clear();

	// destroying states
	for (State *obj: states)
		delete obj;
	states.clear();

	// deleting instance
	delete instance;
}


void Editor::CameraReset() {
	cameraPosition[0] = 0;
	cameraPosition[1] = 0;

	al_identity_transform(&camera);
	al_translate_transform(&camera, -cameraPosition[0], -cameraPosition[1]);
	al_use_transform(&camera);
}

void Editor::SaveMap(const char *filename, vector<vector<int> > &map, vector<vector<int> > &mapLevel2, string &tileSetPath) {
	// opening input stream
	ofstream openfile(filename);
	if (openfile.is_open()) {
		cout << "Saving updated map to text file";

		// writing updated map to text file
		openfile << "[TileSet]" << endl;
		openfile << tileSetPath << endl;
		openfile << "[MapLevel1]" << endl;
		for (unsigned int i = 0; i  < map.size(); i++) {
			cout << ". ";

			for (unsigned int j = 0; j < map[i].size(); j++) {
				// writing tile id
				openfile << map[i][j];

				// leaving a space
				if (map[i][j] < 10)
					openfile << "  ";
				else if (map[i][j] < 100)
					openfile << " ";

				if (j == map[i].size()-1)
					if (i < map.size()-1)
						openfile << endl;
			}
		}
		openfile << endl;
		openfile << "[MapLevel2]" << endl;
		for (unsigned int i = 0; i  < mapLevel2.size(); i++) {
			cout << ". ";

			for (unsigned int j = 0; j < mapLevel2[i].size(); j++) {
				// writing tile id
				openfile << mapLevel2[i][j];

				// leaving a space
				if (mapLevel2[i][j] < 10)
					openfile << "  ";
				else if (mapLevel2[i][j] < 100)
					openfile << " ";

				if (j == mapLevel2[i].size()-1)
					if (i < mapLevel2.size()-1)
						openfile << endl;
			}
		}

		cout << "DONE!" << endl;
	}
	else {
		// if output stream was not opened successfully
		al_show_native_message_box(Editor::GetInstance()->GetDisplay(), "Error", "Could not save world map.", "Your game folder must be corrupt.\nQuitting editor.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
}


ALLEGRO_TIMER *Editor::GetTimer(TimerType Timer) {
	return timers[Timer];
}