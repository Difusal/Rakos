#include "TutorialState.h"
#include "RPG.h"
#include "globalFunctions.h"

void TutorialState::InitializeLivingBeings() {
	livingBeings.clear();

	// initializing player
	player = RPG::GetInstance()->GetPlayer();
	livingBeings.push_back(player);


	// initializing npcs
	Steve = new NPC("Steve", 160, 200, 230, 320, explorer_greenPng);
	livingBeings.push_back(Steve);

	WhiteKnight = new NPC("White Knight", 670, 180, 740, 240, knight_whitePng);
	livingBeings.push_back(WhiteKnight);

	Sorcerer = new NPC("Sorcerer", 984, 90, sorcerer_bluePng);
	livingBeings.push_back(Sorcerer);

	Warrior = new NPC("Warrior", 984, 250, warrior_yellowPng);
	livingBeings.push_back(Warrior);
	

	// initializing creatures
	rabbit = new Rabbit(180, 390, 240, 390);
	livingBeings.push_back(rabbit);
}

void TutorialState::InitializeDialogs() {
	// temporary vector to initialize text boxes content
	vector<string> tempVec;

	tempVec.clear();
	tempVec.push_back("Welcome to Rakos!");
	tempVec.push_back("Move yourself using WASD keys.");
	tempVec.push_back("Try it now.");
	tutorialDialog1 = new TextBox(_Center, tempVec);
	dialogs.push_back(tutorialDialog1);

	tempVec.clear();
	tempVec.push_back("Congratulations!");
	tempVec.push_back("You should go talk to Steve now.");
	tempVec.push_back("He is a bit to the north. To chat, get close to him and press \"C\".");
	tutorialDialog2 = new TextBox(_Bottom, tempVec);
	dialogs.push_back(tutorialDialog2);
}

void TutorialState::MoveLivingBeings(ALLEGRO_EVENT *ev) {
	// moving player, npcs and creatures
	if (ev->timer.source == RPG::GetInstance()->GetTimer(_PlayerMoveTimer))
		player->Move(keyState, worldMap, unaccessibleTiles);
	for (unsigned int i = 1; i < livingBeings.size(); i++)
		if (!livingBeings[i]->isDead())
			if (ev->timer.source == RPG::GetInstance()->GetTimer(livingBeings[i]->getTimerType()))
				livingBeings[i]->Move();

	// checking if something collided with something
	for (unsigned int i = 0; i < livingBeings.size()-1; i++)
		for (unsigned int j = i+1; j < livingBeings.size(); j++)
			RPG::GetInstance()->UpdateLivingBeingsCollisions(livingBeings[i], livingBeings[j]);
}

void TutorialState::UpdateDialogs() {
	RPG::GetInstance()->CheckIfPlayerWantsToChat(livingBeings, keyState);

	if (player->isActive() && !playerHasTalkedToSteve) {
		tutorialDialog1->Hide();
		tutorialDialog2->Show();
	}

	if (Steve->isSpeaking()) {
		if (!playerHasTalkedToSteve) {
			playerHasTalkedToSteve = true;
			tutorialDialog2->Hide();
			player->setWeapon(RPG::GetInstance()->GetWeapon(_Knife));
		}

		if (rabbit->isDead())
			showSteveDialog2 = true;
		else
			showSteveDialog1 = true;
	}
	else {
		showSteveDialog1 = false;
		showSteveDialog2 = false;
	}
}

void TutorialState::UpdateSwitches() {
	// tutorial switch
	if (tutorialSwitch->isBeingPressed(player)) {
		tutorialSwitch->Press();

		// opening portal if not already opened
		if (!tutorialPortal->isOpen())
			tutorialPortal->Open();
	}
	else {
		if (tutorialSwitch->isPressed())
			tutorialSwitch->incrementUnpressDelayCounter();

		if (tutorialSwitch->unpressDelayPassed())
			tutorialPortal->Close();
	}
}

void TutorialState::DrawDialogs() {
	if (showSteveDialog1)
		al_draw_bitmap(steveDialog1, Steve->getX()-85, Steve->getY()-al_get_bitmap_height(steveDialog1), NULL);
	else if (showSteveDialog2)
		al_draw_bitmap(steveDialog2, Steve->getX()-85, Steve->getY()-al_get_bitmap_height(steveDialog2), NULL);
	
	for (TextBox *obj: dialogs)
		obj->Draw();
}


void TutorialState::Initialize() {
	// loading map
	LoadMap(TutorialWorldMapPath, worldMap);
	unaccessibleTiles.push_back(0);

	// loading images
	sideBar = al_load_bitmap(SideBarPath);
	if (!sideBar) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load side bar bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	InitializeLivingBeings();

	tutorialSwitch = new Switch(3, 3, FPS*4.6);
	switches.push_back(tutorialSwitch);

	tutorialPortal = new Portal(false, 12, 3, 17, 3);
	portals.push_back(tutorialPortal);

	InitializeDialogs();

	// loading dialogs
	steveDialog1 = al_load_bitmap(SteveDialog1);
	steveDialog2 = al_load_bitmap(SteveDialog2);
	if (!steveDialog1 || !steveDialog2) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load one or more dialogs.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	tutorialDialog1->Show();
	showSteveDialog1 = false;
	showSteveDialog2 = false;
	playerHasTalkedToSteve = false;
}

bool TutorialState::Update(ALLEGRO_EVENT *ev) {
	bool draw = false;
	al_get_keyboard_state(&keyState);

	if (ev->type == ALLEGRO_EVENT_TIMER) {
		MoveLivingBeings(ev);

		if (ev->timer.source == RPG::GetInstance()->GetTimer(_RegularTimer)) {
			player->ControlAttackRate();
			RPG::GetInstance()->CheckIfPlayerAttackedSomething(livingBeings, keyState);
			RPG::GetInstance()->RemoveDeadLivingBeingsFromVector(livingBeings);

			UpdateSwitches();
			tutorialPortal->CheckIfPlayerPassedThrough(player);
			UpdateDialogs();

			RPG::GetInstance()->UpdateCamera(worldMap, livingBeings);
		}

		RPG::GetInstance()->UpdateAnimationsFrame(livingBeings);
		RPG::GetInstance()->UpdateAnimationsFrame(portals);
		RPG::GetInstance()->UpdateWeaponPositions(livingBeings);
		RPG::GetInstance()->UpdateWeaponAttackAnimations(livingBeings);

		// sorting vector in the correct drawing order
		sort(livingBeings.begin(), livingBeings.end(), [](LivingBeing *a, LivingBeing *b) { return a->getY() < b->getY(); });

		draw = true;
	}

	return draw;
}

void TutorialState::Draw() {
	DrawMap(worldMap);

	// drawing switches
	for (Switch *obj : switches)
		obj->Draw();

	// drawing portals
	for (Portal *obj : portals)
		obj->Draw();

	// drawing living beings
	for (unsigned int i = 0; i < livingBeings.size(); i++)
		livingBeings[i]->Draw();

	// drawing side bar
	al_draw_bitmap(sideBar, 600 + RPG::GetInstance()->cameraPosition[0], RPG::GetInstance()->cameraPosition[1], NULL);
	
	DrawDialogs();

	/*
	// ---------------
	// Debugging code:
	// Uncomment this block of code to display player coords.
	// ------------------------------------------------------
	cout << "Player feet coords: " << player->getFeetX() << " " << player->getFeetY()
		<< "\t\tbitmap source: " << player->getX() << " " << player->getY() << endl;
	// -----------------
	*/
}

void TutorialState::Terminate() {
	for (LivingBeing *being : livingBeings)
		delete being;
	livingBeings.clear();

	for (Switch *obj: switches)
		delete obj;
	switches.clear();

	for (Portal *obj: portals)
		delete obj;
	portals.clear();

	for (TextBox *obj: dialogs)
		delete obj;
	dialogs.clear();

	al_destroy_bitmap(sideBar);
}

