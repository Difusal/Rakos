#include "RPG.h"
#include "TutorialState.h"
#include "globalFunctions.h"

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


void RPG::StartAllegro5() {
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

void RPG::CreateAllegroDisplay() {
	cout << "Creating display..." << endl;
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(ScreenWidth, ScreenHeight);
	if (!display) {
		al_show_native_message_box(display, "Error", "Display Settings", "Couldn't create a display.\nQuitting game.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
	/* setting new window title */
	al_set_window_title(display, GameTitle);
}

void RPG::DisplayLoadingSplashScreen() {
	cout << "Displaying loading game background..." << endl;
	loading_background = al_load_bitmap(LoadingGameBackgroundPath);
	if (!loading_background)
		cout << "Error loading loading game bitmap... Proceeding anyway." << endl;
	al_draw_bitmap(loading_background, 0, 0, NULL);
	al_flip_display();
}

void RPG::StartMouseCursor() {
	cout << "Hiding windows mouse cursor..." << endl;
	al_hide_mouse_cursor(display);
	Mouse = new MouseCursor();
}

void RPG::LoadFonts() {
	cout << "Loading fonts..." << endl;
	big_font = al_load_font(ConsolaTTF, 36, ALLEGRO_ALIGN_CENTER);
	fonts.push_back(big_font);

	medium_font = al_load_font(ConsolaTTF, 20, ALLEGRO_ALIGN_CENTER);
	fonts.push_back(medium_font);

	small_font = al_load_font(ConsolaTTF, 12, ALLEGRO_ALIGN_CENTER);
	fonts.push_back(small_font);

	tiny_font = al_load_font(ConsolaTTF, 10, ALLEGRO_ALIGN_CENTER);
	fonts.push_back(tiny_font);

	for (unsigned int i = 0; i < fonts.size(); i++) {
		if (!fonts[i]) {
			al_show_native_message_box(display, "Error", "Could not load font file.", "Have you included the resources in the same directory of the program?", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			exit(-1);
		}
	}
}

void RPG::CreateTimers() {
	cout << "Creating timers..." << endl;
	timer = al_create_timer(1.0 / FPS);
	timers.push_back(timer);

	mouseAnimTimer = al_create_timer(1.0 / mouseAnimFPS);
	timers.push_back(mouseAnimTimer);

	drawTimer = al_create_timer(1.0 / drawFPS);
	timers.push_back(drawTimer);

	playerAnimTimer = al_create_timer(1.0 / drawFPS);
	timers.push_back(playerAnimTimer);
}

void RPG::CreateEventQueue() {
	cout << "Creating event queues..." << endl;
	event_queue = al_create_event_queue();

	cout << "Registering event sources..." << endl;
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	for (unsigned int i = 0; i < timers.size(); i++) {
		al_register_event_source(event_queue, al_get_timer_event_source(timers[i]));
	}
}

void RPG::LoadSoundSamples() {
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
}

void RPG::InitializeVariables() {
	cout << "Initializing variables..." << endl;
	cameraPosition[0] = 0;
	cameraPosition[1] = 0;

	done = false;
	draw = true;
}

void RPG::StartTimers() {
	cout << "Starting timers..." << endl;
	for (unsigned int i = 0; i < timers.size(); i++) {
		al_start_timer(timers[i]);
	}
}


void RPG::LoadWeapons() {
	cout << "Loading weapons..." << endl;
	no_weapon = new Weapon();
	knife = new Weapon("knife", 1, 2);
}

Weapon * RPG::GetWeapon(WeaponType Weapon) {
	switch (Weapon) {
	default:
	case _None:
		return no_weapon;
		break;
	case _Knife:
		return knife;
		break;
	}
}


bool RPG::livingBeingCollidingWithMap(int Dir, const vector<vector<int> > &worldMap, const vector<int> &unaccessibleTiles) {
	int north_scan = worldMap[(player->getFeetY()-15)/WorldBlockSize][player->getFeetX()/WorldBlockSize];
	int ne_scan = worldMap[(player->getFeetY()-15)/WorldBlockSize][(player->getFeetX()+25)/WorldBlockSize];
	int east_scan = worldMap[player->getFeetY()/WorldBlockSize][(player->getFeetX()+25)/WorldBlockSize];
	int se_scan = worldMap[(player->getFeetY()+25)/WorldBlockSize][(player->getFeetX()+25)/WorldBlockSize];
	int south_scan = worldMap[(player->getFeetY()+25)/WorldBlockSize][player->getFeetX()/WorldBlockSize];
	int sw_scan = worldMap[(player->getFeetY()+25)/WorldBlockSize][(player->getFeetX()-25)/WorldBlockSize];
	int west_scan = worldMap[player->getFeetY()/WorldBlockSize][(player->getFeetX()-25)/WorldBlockSize];
	int nw_scan = worldMap[(player->getFeetY()-15)/WorldBlockSize][(player->getFeetX()-25)/WorldBlockSize];

	for (unsigned int i = 0; i < unaccessibleTiles.size(); i++) {
		switch (Dir) {
		case UP:
			if (north_scan == unaccessibleTiles[i] || east_scan == unaccessibleTiles[i] || west_scan == unaccessibleTiles[i] || ne_scan == unaccessibleTiles[i] || nw_scan == unaccessibleTiles[i])
				return true;
			break;
		case DOWN:
			if (east_scan == unaccessibleTiles[i] || south_scan == unaccessibleTiles[i] || west_scan == unaccessibleTiles[i] || se_scan == unaccessibleTiles[i] || sw_scan == unaccessibleTiles[i])
				return true;
			break;
		case LEFT:
			if (north_scan == unaccessibleTiles[i] || south_scan == unaccessibleTiles[i] || west_scan == unaccessibleTiles[i] || sw_scan == unaccessibleTiles[i] || nw_scan == unaccessibleTiles[i])
				return true;
			break;
		case RIGHT:
			if (north_scan == unaccessibleTiles[i] || east_scan == unaccessibleTiles[i] || south_scan == unaccessibleTiles[i] || ne_scan == unaccessibleTiles[i] || se_scan == unaccessibleTiles[i])
				return true;
			break;
		}
	}

	return false;
}

void RPG::UpdateLivingBeingsCollisions(LivingBeing *a, LivingBeing *b) {
	LivingBeing *objBeingCorrected = nullptr;

	// if a collision is happening
	if (boxCollision(a->getX(), a->getY(), b->getX(), b->getY(), 32, 32)) {
		// if objects are heading the same direction
		if (a->getDir() == b->getDir()) {
			switch (a->getDir()) {
			case RIGHT:
				{
					if (a->getX() < b->getX())
						objBeingCorrected = a;
					else
						objBeingCorrected = b;

					objBeingCorrected->setX(objBeingCorrected->getX() - objBeingCorrected->getMoveSpeed());
					break;
				}
			case LEFT:
				{
					if (a->getX() > b->getX())
						objBeingCorrected = a;
					else
						objBeingCorrected = b;

					objBeingCorrected->setX(objBeingCorrected->getX() + objBeingCorrected->getMoveSpeed());
					break;
				}
			case UP:
				{
					if (a->getY() > b->getY())
						objBeingCorrected = a;
					else
						objBeingCorrected = b;

					objBeingCorrected->setY(objBeingCorrected->getY() + objBeingCorrected->getMoveSpeed());
					break;
				}
			case DOWN:
				{
					if (a->getY() < b->getY())
						objBeingCorrected = a;
					else
						objBeingCorrected = b;

					objBeingCorrected->setY(objBeingCorrected->getY() - objBeingCorrected->getMoveSpeed());
					break;
				}
			}
		}
	}

	/*
	if(a->getActiveState() && boxCollision(a->getX(), a->getY(), b->getX(), b->getY(), 32, 32)) {
	if (a->getDir() == 0)
	a->setY(a->getY() - a->getMoveSpeed());
	else if (a->getDir() == 1)
	a->setX(a->getX() + a->getMoveSpeed());
	else if (a->getDir() == 2)
	a->setX(a->getX() - a->getMoveSpeed());
	else if (a->getDir() == 3)
	a->setY(a->getY() + a->getMoveSpeed());
	}
	if(b->getActiveState() && boxCollision(b->getX(), b->getY(), a->getX(), a->getY(), 32, 32)) {
	if (b->getDir() == 0)
	b->setY(b->getY() - b->getMoveSpeed());
	else if (b->getDir() == 1)
	b->setX(b->getX() + b->getMoveSpeed());
	else if (b->getDir() == 2)
	b->setX(b->getX() - b->getMoveSpeed());
	else if (b->getDir() == 3)
	b->setY(b->getY() + b->getMoveSpeed());
	}*/
}

void RPG::UpdateCamera(vector<vector<int> > &worldMap) {
	CameraUpdate(worldMap, RPG::GetInstance()->cameraPosition, player->getX(), player->getY(), 32, 32);
	al_identity_transform(RPG::GetInstance()->GetCamera());
	al_translate_transform(RPG::GetInstance()->GetCamera(), -RPG::GetInstance()->cameraPosition[0], -RPG::GetInstance()->cameraPosition[1]);
	al_use_transform(RPG::GetInstance()->GetCamera());
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

	StartAllegro5();
	CreateAllegroDisplay();
	DisplayLoadingSplashScreen();
	StartMouseCursor();
	LoadFonts();
	CreateTimers();
	CreateEventQueue();
	LoadSoundSamples();

	LoadWeapons();

	InitializeVariables();
	StartTimers();
}

void RPG::start_game () {
	Initialize();

	// TEMP EDIT THIS
	player = new Player("Difusal", no_weapon, 480, 580);

	states.push_back(new TutorialState());
	state = -1;
	ChangeState(_Tutorial);

	cout << "Starting control cycle..." << endl;
	while (!done) {
		al_wait_for_event(event_queue, &ev);

		/* --- UPDATING --- */
		draw = Mouse->Update(&ev);
		states[state]->Update(&ev);
		if (ev.type != ALLEGRO_EVENT_MOUSE_AXES)
			draw = Mouse->CorrectMousePosition();

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			Mouse->SetAllReleaseValuesToFalse();

			draw = true;
		}

		/* --- DRAWING --- */
		if (draw && al_event_queue_is_empty(event_queue)) {
			states[state]->Draw();			
			Mouse->Draw();

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
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			cout << "Close button pressed..." << endl;
			done = true;
		}
	}
	cout << "* done = true; *" << endl;

	Terminate();
}

void RPG::Terminate() {
	cout << "Deallocating memory and quitting..." << endl;

	// destroying fonts
	for (unsigned int i = 0; i < fonts.size(); i++) {
		al_destroy_font(fonts[i]);
	}

	// audio samples


	// destroying event queue and timers
	al_destroy_event_queue(event_queue);
	for (unsigned int i = 0; i < timers.size(); i++) {
		al_destroy_timer(timers[i]);
	}
	timers.clear();

	// deleting mouse cursor
	delete Mouse;

	// destroying display
	al_destroy_display(display);

	// bitmaps
	al_destroy_bitmap(loading_background);

	delete instance;
}


ALLEGRO_TIMER * RPG::GetTimer( TimerType Timer ) {
	switch (Timer) {
	default:
	case _RegularTimer:
		return timer;
		break;
	case _MouseAnimTimer:
		return mouseAnimTimer;
		break;
	case _DrawTimer:
		return drawTimer;
		break;
	case _PlayerAnimTimer:
		return playerAnimTimer;
		break;
	}
}