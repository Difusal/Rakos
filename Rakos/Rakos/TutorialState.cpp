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

void TutorialState::UpdateDialogs() {
	RPG::GetInstance()->CheckIfPlayerWantsToChat(livingBeings, keyState);

	if (player->isActive() && !playerHasTalkedToSteve) {
		showTutorialDialog1 = false;
		showTutorialDialog2 = true;
	}

	if (Steve->isSpeaking()) {
		if (!playerHasTalkedToSteve) {
			playerHasTalkedToSteve = true;
			showTutorialDialog2 = false;
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
	if (showTutorialDialog1)
		al_draw_bitmap(tutorialDialog1, 300 + RPG::GetInstance()->cameraPosition[0] - al_get_bitmap_width(tutorialDialog1)/2, RPG::GetInstance()->cameraPosition[1] + ScreenHeight/4, NULL);
	else if (showTutorialDialog2)
		al_draw_bitmap(tutorialDialog2, 300 + RPG::GetInstance()->cameraPosition[0] - al_get_bitmap_width(tutorialDialog2)/2, RPG::GetInstance()->cameraPosition[1] + ScreenHeight - al_get_bitmap_height(tutorialDialog2), NULL);
	else if (showSteveDialog1)
		al_draw_bitmap(steveDialog1, Steve->getX()-85, Steve->getY()-al_get_bitmap_height(steveDialog1), NULL);
	else if (showSteveDialog2)
		al_draw_bitmap(steveDialog2, Steve->getX()-85, Steve->getY()-al_get_bitmap_height(steveDialog2), NULL);
	
	tutorialDialogBox1->Draw();
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
	// EDIT THIS
	player->Move(keyState, worldMap);

	tutorialSwitch = new Switch(3, 3, FPS*4.6);
	switches.push_back(tutorialSwitch);

	tutorialPortal = new Portal(false, 12, 3, 17, 3);
	portals.push_back(tutorialPortal);

	vector<string> tempVec;
	tempVec.push_back("Welcome to Rakos!");
	tempVec.push_back("Move yourself using WASD keys.");
	tempVec.push_back("Try it now.");
	tutorialDialogBox1 = new TextBox(Bottom, tempVec);
	tempVec.clear();

	// loading dialogs
	tutorialDialog1 = al_load_bitmap(TutorialDialog1);
	tutorialDialog2 = al_load_bitmap(TutorialDialog2);
	steveDialog1 = al_load_bitmap(SteveDialog1);
	steveDialog2 = al_load_bitmap(SteveDialog2);
	if (!tutorialDialog1 || !tutorialDialog2 || !steveDialog1 || !steveDialog2) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load one or more dialogs.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	showTutorialDialog1 = true;
	showTutorialDialog2 = false;
	showSteveDialog1 = false;
	showSteveDialog2 = false;
	playerHasTalkedToSteve = false;
}

bool TutorialState::Update(ALLEGRO_EVENT *ev) {
	bool draw = false;
	al_get_keyboard_state(&keyState);

	draw = RPG::GetInstance()->RemoveDeadLivingBeingsFromVector(livingBeings);

	if (ev->type == ALLEGRO_EVENT_TIMER) {
		// moving player, npcs and creatures
		if (ev->timer.source == RPG::GetInstance()->GetTimer(_PlayerMoveTimer))
			player->Move(keyState, worldMap);
		for (unsigned int i = 1; i < livingBeings.size(); i++)
			if (!livingBeings[i]->isDead()) {
				switch (livingBeings[i]->getType()) {
				case _NPC:
					if (ev->timer.source == RPG::GetInstance()->GetTimer(_NPCMoveTimer))
						livingBeings[i]->Move();
					break;
				case _Creature:
					if (ev->timer.source == RPG::GetInstance()->GetTimer(_SlowCreatureMoveTimer))
						livingBeings[i]->Move();
					break;
				}
			}

		// checking if something collided
		player->CorrectPositionIfCollidingWithMapLimits(worldMap, unaccessibleTiles);
		for (unsigned int i = 0; i < livingBeings.size()-1; i++)
			for (unsigned int j = i+1; j < livingBeings.size(); j++)
				RPG::GetInstance()->UpdateLivingBeingsCollisions(livingBeings[i], livingBeings[j]);

		// REGULAR TIMER
		if (ev->timer.source == RPG::GetInstance()->GetTimer(_RegularTimer)) {
			player->ControlAttackRate();
			RPG::GetInstance()->CheckIfPlayerAttackedSomething(livingBeings, keyState);

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

	for (Switch *obj : switches)
		delete obj;
	switches.clear();

	for (Portal *obj : portals)
		delete obj;
	portals.clear();

	al_destroy_bitmap(sideBar);
}