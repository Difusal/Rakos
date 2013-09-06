#include "RPG.h"
#include "globalFunctions.h"

#include "LanguageState.h"
#include "MenuState.h"
#include "TutorialState.h"
#include "RakosState.h"

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
		states[state]->Terminate();

	state = newState;
	states[state]->Initialize();
}


void RPG::CreateAllegroDisplay(bool FullScreenMode) {
	cout << "Creating display..." << endl;

	switch (FullScreenMode) {
	case false:
		// creating a window
		{
			// specifying program to run on a window
			al_set_new_display_flags(ALLEGRO_WINDOWED);

			// default values
			ScreenWidth = DefaultScreenWidth;
			ScreenHeight = DefaultScreenHeight;

			// sidebar
			SideBarWidth = 200;

			break;
		}
	case true:
		// creating full screen display
		{
			// specifying program to run on full screen
			al_set_new_display_flags(ALLEGRO_FULLSCREEN);

			// getting monitor info
			ALLEGRO_DISPLAY_MODE disp_data;
			al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);

			// setting screen width and height
			ScreenWidth = disp_data.width;
			ScreenHeight = disp_data.height;

			// sidebar
			SideBarWidth = 200;

			break;
		}
	}

	// creating display
	display = al_create_display(ScreenWidth, ScreenHeight);

	// if display was not loaded correctly, show error message and quit program
	if (!display) {
		al_show_native_message_box(display, "Error", "Display Settings", "Couldn't create a display.\nQuitting program.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	// changing window title
	al_set_window_title(display, ProgramTitle);
}

void RPG::DisplayLoadingSplashScreen() {
	cout << "Displaying loading game background..." << endl;

	cameraPosition[0] = 0;
	cameraPosition[1] = 0;

	loading_background = al_load_bitmap(LoadingGameBackgroundPath);

	if (!loading_background)
		cout << "Error loading loading game bitmap... Proceeding anyway." << endl;
	else {
		if (ScreenWidth <= 1366 && ScreenHeight <= 768)
			al_draw_bitmap_region(loading_background, al_get_bitmap_width(loading_background)/2 - ScreenWidth/2, al_get_bitmap_height(loading_background)/2 - ScreenHeight/2, ScreenWidth, ScreenHeight, cameraPosition[0], cameraPosition[1], ALLEGRO_ALIGN_LEFT);
		else
			al_draw_scaled_bitmap(loading_background, 0, 0, al_get_bitmap_width(loading_background), al_get_bitmap_height(loading_background), cameraPosition[0], cameraPosition[1], cameraPosition[0]+ScreenWidth, cameraPosition[1]+ScreenHeight, ALLEGRO_ALIGN_LEFT);
	}

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

	medium_font = al_load_font(ConsolaTTF, 18, ALLEGRO_ALIGN_CENTER);
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

	playerMoveTimer = al_create_timer(1.0 / HumansWalkingSpeed);
	timers.push_back(playerMoveTimer);

	NPCMoveTimer = al_create_timer(1.0 / NPCWalkingSpeed);
	timers.push_back(NPCMoveTimer);

	slowCreatureMoveTimer = al_create_timer(1.0 / SlowCreaturesSpeed);
	timers.push_back(slowCreatureMoveTimer);

	mouseAnimTimer = al_create_timer(1.0 / 18);
	timers.push_back(mouseAnimTimer);

	drawTimer = al_create_timer(1.0 / drawFPS);
	timers.push_back(drawTimer);

	playerAnimTimer = al_create_timer(1.0 / drawFPS);
	timers.push_back(playerAnimTimer);

	weaponAnimTimer = al_create_timer(1.0 / 20);
	timers.push_back(weaponAnimTimer);

	portalAnimTimer = al_create_timer(1.0 / 2);
	timers.push_back(portalAnimTimer);
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

	previousNPCWhoTalkedToPlayer = NULL;

	seaAnimation = al_load_bitmap(SeaPng);

	DefaultLanguage = _English;
	LanguageBeingUsed = _UndefinedLanguage;

	togglingFullScreen = false;
	done = false;
	draw = true;
}

void RPG::StartTimers() {
	cout << "Starting timers..." << endl;
	for (unsigned int i = 0; i < timers.size(); i++)
		al_start_timer(timers[i]);
}


void RPG::LoadWeapons() {
	cout << "Loading weapons..." << endl;
	no_weapon = new Weapon(_NoWeapon, 0, 0);
	weapons.push_back(no_weapon);

	knife = new Weapon(_Knife, 1, 2);
	weapons.push_back(knife);

	wand = new Weapon(_Wand, 4, 6);
	weapons.push_back(wand);

	sword = new Weapon(_Sword, 2, 5);
	weapons.push_back(sword);
}

void RPG::LoadShields() {
	cout << "Loading shields..." << endl;
	no_shield = new Shield(_NoShield, 0);
	shields.push_back(no_shield);

	woodenShield = new Shield(_WoodenShield, 2);
	shields.push_back(woodenShield);
}


void RPG::Initialize(bool FullScreenMode) {
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

	CreateAllegroDisplay(FullScreenMode);
	DisplayLoadingSplashScreen();
	StartMouseCursor();
	LoadFonts();
	CreateTimers();
	CreateEventQueue();
	LoadSoundSamples();

	LoadWeapons();
	LoadShields();

	InitializeVariables();
	StartTimers();
}

GameCycleReturnValue RPG::StartGameControlCycle(bool FullScreenMode, Language GameLanguage) {
	// initializing game
	Initialize(FullScreenMode);

	// EDIT THIS
	player = new Player("Difusal", no_weapon, no_shield, 480, 580);

	// building states vector
	states.push_back(new LanguageState());
	states.push_back(new MenuState());
	states.push_back(new TutorialState());
	states.push_back(new RakosState());
	state = -1;

	// if not toggling full screen, choose a language
	if (GameLanguage == _UndefinedLanguage)
		ChangeState(_Language);
	else {
		// else use the same language being used before
		LanguageBeingUsed = GameLanguage;
		ChangeState(_MainMenu);
	}

	cout << "Starting game control cycle..." << endl;
	while (!done) {
		al_wait_for_event(event_queue, &ev);
		Update();
		Draw();
	}
	states[state]->Terminate();

	GameCycleReturnValue returnValue;
	returnValue.TogglingFullscreen = togglingFullScreen;
	returnValue.CurrentLanguage = LanguageBeingUsed;

	Terminate();

	return returnValue;
}

void RPG::Update() {
	// if window is closed on dedicated button (upper right corner)
	if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		cout << "Close button pressed..." << endl;
		done = true;
	}

	draw = Mouse->Update(&ev);
	states[state]->Update(&ev);

	if (ev.type != ALLEGRO_EVENT_MOUSE_AXES)
		draw = Mouse->CorrectMousePosition();

	if (ev.type == ALLEGRO_EVENT_TIMER) {
		Mouse->SetAllReleaseValuesToFalse();
		draw = true;
	}
}

void RPG::Draw() {
	if (draw && al_event_queue_is_empty(event_queue)) {
		/*
		// ---------------
		// Debugging code:
		// Uncomment this block of code to display mouse coords.
		// -----------------------------------------------------
		stringstream ss;
		ss << mouse_x << " " << mouse_y;
		al_draw_text(font, Yellow, 0, 0, NULL, ss.str().c_str());
		cout << ss.str() << endl;
		*/

		states[state]->Draw();			
		Mouse->Draw();

		al_flip_display();
		al_clear_to_color(Black);
		draw = false;
	}
}

void RPG::Terminate() {
	cout << "Deallocating memory and quitting..." << endl;

	// audio samples


	// deleting mouse cursor
	delete Mouse;

	// destroying display
	al_destroy_display(display);

	// weapons
	for (Weapon *obj : weapons)
		delete obj;
	weapons.clear();

	// shields
	for (Shield *obj : shields)
		delete obj;
	shields.clear();

	// living beings
	delete player;

	// bitmaps
	al_destroy_bitmap(loading_background);
	// EDIT THIS
	//al_destroy_bitmap(tileSet);

	// destroying fonts
	for (unsigned int i = 0; i < fonts.size(); i++)
		al_destroy_font(fonts[i]);
	fonts.clear();

	// destroying event queue and timers
	al_destroy_event_queue(event_queue);
	for (unsigned int i = 0; i < timers.size(); i++)
		al_destroy_timer(timers[i]);
	timers.clear();
}


// Public Methods
void RPG::ToggleFullScreen() {
	cout << "Toggling full screen..." << endl;
	togglingFullScreen = true;
	done = true;
}


void RPG::CheckIfPlayerAttackedSomething(vector<LivingBeing*> &livingBeings, ALLEGRO_KEYBOARD_STATE keyState) {
	bool playerAttackedSomething = false;

	unsigned int maximumAttackDistance;
	switch (player->GetWeapon()->getType()) {
	case _NoWeapon:
	case _Knife:
	case _Sword:
		maximumAttackDistance = 40;
		break;
	case _Wand:
		maximumAttackDistance = 175;
		break;
	}
	
	if (al_key_down(&keyState, ALLEGRO_KEY_K) && player->CanAttack()) {
		playerAttackedSomething = true;

		for (unsigned int i = 0; i < livingBeings.size(); i++) {
			// skip if scanning something player can not attack
			if (livingBeings[i]->getType() != _Creature)
				continue;

			if (calcDistance(player->getX(), player->getY(), livingBeings[i]->getX(), livingBeings[i]->getY()) < maximumAttackDistance) {
				if (!(livingBeings[i]->getY() > player->getY() && player->getDir() == UP) &&
					!(livingBeings[i]->getY() < player->getY() && player->getDir() == DOWN) &&
					!(livingBeings[i]->getX() > player->getX() && player->getDir() == LEFT) &&
					!(livingBeings[i]->getX() < player->getX() && player->getDir() == RIGHT))
				{
					livingBeings[i]->takeHP(player->getWeapon()->getDamage());
					if (livingBeings[i]->getHP() <= 0)
						livingBeings[i]->setDeadState(true);
				}
			}
		}
	}

	if (playerAttackedSomething) {
		player->CanNotAttackNow();
		player->getWeapon()->PlayAttackAnim();
	}
}

void RPG::CheckIfPlayerWantsToChat(vector<LivingBeing*> &livingBeings, ALLEGRO_KEYBOARD_STATE keyState) {
	int idOfClosestNPCAbleToTalk = -1;
	int minimumDistance;
	float currentDistance;

	for (unsigned int i = 0; i < livingBeings.size(); i++) {
		// skip if living being being scanned is not a npc
		if (livingBeings[i]->getType() != _NPC)
			continue;

		if (al_key_down(&keyState, ALLEGRO_KEY_C)) {
			currentDistance = calcDistance(player->getX(), player->getY(), livingBeings[i]->getX(), livingBeings[i]->getY());

			if (currentDistance < 40 && (idOfClosestNPCAbleToTalk == -1 || currentDistance < minimumDistance)) {
				minimumDistance = currentDistance;
				idOfClosestNPCAbleToTalk = i;
			}
		}
	}

	// if player spoke to npc, enable npc speaking
	if (idOfClosestNPCAbleToTalk != -1) {
		livingBeings[idOfClosestNPCAbleToTalk]->Speak();
		previousNPCWhoTalkedToPlayer = livingBeings[idOfClosestNPCAbleToTalk];
	}

	// if no npc is talking to player, activate previous npc who talked to player, if there is one
	if (idOfClosestNPCAbleToTalk == -1 && previousNPCWhoTalkedToPlayer != NULL)
		if (calcDistance(player->getX(),player->getY(), previousNPCWhoTalkedToPlayer->getX(), previousNPCWhoTalkedToPlayer->getY()) > 60)
			previousNPCWhoTalkedToPlayer->StopSpeaking();
}

bool RPG::RemoveDeadLivingBeingsFromVector(vector<LivingBeing*> &livingBeings) {
	bool changedSomething = false;

	for (unsigned int i = 1; i < livingBeings.size(); i++)
		if (livingBeings[i]->isDead()) {
			switch (livingBeings[i]->getType()) {
			case _NPC:
			case _Creature:
				player->addExperience(livingBeings[i]->GetExperience());
				player->addGold(livingBeings[i]->GetAmountOfGold());
				livingBeings.erase(livingBeings.begin() + i);
				changedSomething = true;
				break;
			case _Player:
				// EDIT THIS
				al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Rakos", "You are dead!", "You just died, sorry...", NULL, NULL);
				break;
			}
		}

	return changedSomething;
}


bool RPG::livingBeingCollidingWithMap(LivingBeing *being, const vector<vector<int> > &worldMap, const vector<int> &accessibleTiles) {
	int scan = worldMap[being->getFeetY()/WorldBlockSize][being->getFeetX()/WorldBlockSize];

	for (unsigned int i = 0; i < accessibleTiles.size(); i++) {
		if (scan == accessibleTiles[i])
			return false;
	}

	return true;
}

void RPG::UpdateLivingBeingsCollisions(LivingBeing *a, LivingBeing *b) {
	LivingBeing *objBeingCorrected = nullptr;

	// if a collision is happening
	if (boxCollision(a->getX(), a->getY(), b->getX(), b->getY(), a->width(), 32)) {
		// if objects are heading the same direction
		if (a->getDir() == b->getDir()) {
			switch (a->getDir()) {
			case RIGHT:
				{
					if (a->getX() < b->getX())
						objBeingCorrected = a;
					else
						objBeingCorrected = b;

					if (ev.timer.source == GetTimer(objBeingCorrected->getTimerType()))
						objBeingCorrected->decX();
					break;
				}
			case LEFT:
				{
					if (a->getX() > b->getX())
						objBeingCorrected = a;
					else
						objBeingCorrected = b;

					if (ev.timer.source == GetTimer(objBeingCorrected->getTimerType()))
						objBeingCorrected->incX();
					break;
				}
			case UP:
				{
					if (a->getY() > b->getY())
						objBeingCorrected = a;
					else
						objBeingCorrected = b;

					if (ev.timer.source == GetTimer(objBeingCorrected->getTimerType()))
						objBeingCorrected->incY();
					break;
				}
			case DOWN:
				{
					if (a->getY() < b->getY())
						objBeingCorrected = a;
					else
						objBeingCorrected = b;

					if (ev.timer.source == GetTimer(objBeingCorrected->getTimerType()))
						objBeingCorrected->decY();
					break;
				}
			}
		}
		// if objects are heading opposite directions
		else if ((a->getDir() == RIGHT && b->getDir() == LEFT) || (a->getDir() == LEFT && b->getDir() == RIGHT) ||
			(a->getDir() == UP && b->getDir() == DOWN) || (a->getDir() == DOWN && b->getDir() == UP))
		{
			switch (a->getDir()) {
			case RIGHT:
				// correct X coords
				if (a->isActive() && ev.timer.source == GetTimer(a->getTimerType()))
					a->decX();
				if (b->isActive() && ev.timer.source == GetTimer(b->getTimerType()))
					b->incX();

				break;
			case LEFT:
				// correct X coords
				if (a->isActive() && ev.timer.source == GetTimer(a->getTimerType()))
					a->incX();
				if (b->isActive() && ev.timer.source == GetTimer(b->getTimerType()))
					b->decX();

				break;
			case DOWN:
				// correct Y coords
				if (a->isActive() && ev.timer.source == GetTimer(a->getTimerType()))
					a->decY();
				if (b->isActive() && ev.timer.source == GetTimer(b->getTimerType()))
					b->incY();

				break;
			case UP:
				// correct Y coords
				if (a->isActive() && ev.timer.source == GetTimer(a->getTimerType()))
					a->incY();
				if (b->isActive() && ev.timer.source == GetTimer(b->getTimerType()))
					b->decY();

				break;
			}
		}
		// if objects are heading different directions
		else {
			int xDistance;
			int yDistance;

			bool done = false;
			while (!done) {
				switch (a->getDir()) {
				case RIGHT:
				case LEFT:
					break;
				case DOWN:
					yDistance = abs(a->bottomBorderY() - b->getY());

					switch (b->getDir()) {
					case RIGHT:
						xDistance = abs(a->getX() - b->rightBorderX());

						if (yDistance < xDistance) {
							if (ev.timer.source == GetTimer(a->getTimerType()))
								a->decY();
						}
						else
							if (ev.timer.source == GetTimer(b->getTimerType()))
								b->decX();

						break;
					case LEFT:
						xDistance = abs(a->rightBorderX() - b->getX());

						if (yDistance < xDistance) {
							if (ev.timer.source == GetTimer(a->getTimerType()))
								a->decY();
						}
						else
							if (ev.timer.source == GetTimer(b->getTimerType()))
								b->incX();

						break;
					}

					done = true;
					break;
				case UP:
					yDistance = abs(a->getY() - b->bottomBorderY());

					switch (b->getDir()) {
					case RIGHT:
						xDistance = abs(a->getX() - b->rightBorderX());

						if (yDistance < xDistance) {
							if (ev.timer.source == GetTimer(a->getTimerType()))
								a->incY();
						}
						else
							if (ev.timer.source == GetTimer(b->getTimerType()))
								b->decX();

						break;
					case LEFT:
						xDistance = abs(a->rightBorderX() - b->getX());

						if (yDistance < xDistance) {
							if (ev.timer.source == GetTimer(a->getTimerType()))
								a->incY();
						}
						else
							if (ev.timer.source == GetTimer(b->getTimerType()))
								b->incX();

						break;
					}

					done = true;
					break;
				}

				if (!done) {
					LivingBeing *temp = a;
					a = b;
					b = temp;
				}
			}
		}
	}
}

void RPG::LoadAccessibleTiles( vector<int> &level1AccessibleTiles, vector<int> &level2AccessibleTiles ) {
	// stating level 1 tiles player can walk on
	level1AccessibleTiles.push_back(1);		// grass
	level1AccessibleTiles.push_back(15);	// snow
	level1AccessibleTiles.push_back(32);	// sand
	level1AccessibleTiles.push_back(48);	// wood
	level1AccessibleTiles.push_back(49);
	for (unsigned int i = 52; i < 67; i++)
		level1AccessibleTiles.push_back(i);

	// stating level 2 tiles player can walk on
	level2AccessibleTiles = level1AccessibleTiles;
	level2AccessibleTiles.push_back(0);		// empty tile
	level2AccessibleTiles.push_back(14);	// dirt
	for (unsigned int i = 28; i < 32; i++)
		level2AccessibleTiles.push_back(i);
	level2AccessibleTiles.push_back(32);	// sand
	for (unsigned int i = 34; i < 46; i++)
		level2AccessibleTiles.push_back(i);
	// flowers and other stuff
	level2AccessibleTiles.push_back(77);
	level2AccessibleTiles.push_back(81);
	level2AccessibleTiles.push_back(88);
	level2AccessibleTiles.push_back(89);
	level2AccessibleTiles.push_back(94);
	level2AccessibleTiles.push_back(95);
	level2AccessibleTiles.push_back(96);
	level2AccessibleTiles.push_back(99);
	level2AccessibleTiles.push_back(100);
	level2AccessibleTiles.push_back(103);
	level2AccessibleTiles.push_back(106);
}


void RPG::UpdateAnimationsFrame(vector<LivingBeing*> &livingBeings) {
	// creatures and npcs
	if (ev.timer.source == drawTimer)
		for (LivingBeing *obj : livingBeings)
			if (obj->getType() != _Player)
				obj->UpdateAnimationFrame();

	// player
	if (ev.timer.source == playerAnimTimer)
		player->UpdateAnimationFrame();
}

void RPG::UpdateAnimationsFrame(vector<Portal*> &portals) {
	if (ev.timer.source == portalAnimTimer)
		for (Portal *obj : portals)
			obj->UpdateAnimationFrame();
}

void RPG::UpdateWeaponAndShieldPositions(vector<LivingBeing*> &livingBeings) {
	for (LivingBeing *being : livingBeings) {
		being->GetWeapon()->UpdatePosition(being->getDir(), being->getCurrentFrame(), being->getX(), being->getY());
		being->GetShield()->UpdatePosition(being->getDir(), being->getCurrentFrame(), being->getX(), being->getY());
	}
}

void RPG::UpdateWeaponAttackAnimations(vector<LivingBeing*> &livingBeings) {
	if (ev.timer.source == RPG::GetInstance()->GetTimer(_WeaponAnimTimer))
		for (unsigned int i = 0; i < livingBeings.size(); i++)
			livingBeings[i]->GetWeapon()->UpdateAttackAnimation();
}

void RPG::UpdateCamera(vector<vector<int> > &worldMap, vector<LivingBeing*> &livingBeings) {
	CameraUpdate(worldMap, RPG::GetInstance()->cameraPosition, player->getX(), player->getY(), 32, 32);
	al_identity_transform(RPG::GetInstance()->GetCamera());
	al_translate_transform(RPG::GetInstance()->GetCamera(), -RPG::GetInstance()->cameraPosition[0], -RPG::GetInstance()->cameraPosition[1]);
	al_use_transform(RPG::GetInstance()->GetCamera());
}