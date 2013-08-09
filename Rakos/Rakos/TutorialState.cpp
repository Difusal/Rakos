#include "TutorialState.h"
#include "RPG.h"
#include "globalFunctions.h"

void TutorialState::InitializeLivingBeings() {
	livingBeings.clear();

	// initializing player
	player = RPG::GetInstance()->GetPlayer();
	player->setX(WorldBlockSize*20);
	player->setY(WorldBlockSize*23.5);
	livingBeings.push_back(player);


	// initializing npcs
	Steve = new NPC("Steve", WorldBlockSize*12, WorldBlockSize*14, WorldBlockSize*14, WorldBlockSize*17, explorer_greenPng);
	livingBeings.push_back(Steve);

	WhiteKnight = new NPC("White Knight", WorldBlockSize*25, WorldBlockSize*13, WorldBlockSize*26, WorldBlockSize*15, knight_whitePng);
	livingBeings.push_back(WhiteKnight);

	Sorcerer = new NPC("Sorcerer", WorldBlockSize*32.6, WorldBlockSize*11.25, sorcerer_bluePng);
	livingBeings.push_back(Sorcerer);

	Warrior = new NPC("Warrior", WorldBlockSize*32.6, WorldBlockSize*15.25, warrior_yellowPng);
	livingBeings.push_back(Warrior);
	

	// initializing creatures
	rabbit = new Rabbit(WorldBlockSize*12, WorldBlockSize*19, WorldBlockSize*14, WorldBlockSize*19);
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
	textBoxes.push_back(tutorialDialog1);

	tempVec.clear();
	tempVec.push_back("Congratulations!");
	tempVec.push_back("You should go talk to Steve now.");
	tempVec.push_back("He is a bit to the north. To chat, get close to him and press <C>.");
	tutorialDialog2 = new TextBox(_Bottom, tempVec);
	textBoxes.push_back(tutorialDialog2);

	tempVec.clear();
	tempVec.push_back("Hello there! You must be new here...");
	tempVec.push_back("Take this knife and kill that rabbit.");
	tempVec.push_back("Press <K> to attack.");
	tempVec.push_back("After that, talk to me again.");
	steveDialog1 = new SpeechBubble(Steve->getAddressOfX(), Steve->getAddressOfY(), tempVec);
	Steve->speechBubbles.push_back(steveDialog1);
	speechBubbles.push_back(steveDialog1);

	tempVec.clear();
	tempVec.push_back("Very well! Now step onto that brown");
	tempVec.push_back("switch and a portal will open.");
	tempVec.push_back("Go through it! Here is a tip:");
	tempVec.push_back("Hold <SHIFT> to run.");
	steveDialog2 = new SpeechBubble(Steve->getAddressOfX(), Steve->getAddressOfY(), tempVec);
	Steve->speechBubbles.push_back(steveDialog2);
	speechBubbles.push_back(steveDialog2);

	tempVec.clear();
	tempVec.push_back("Hello " + RPG::GetInstance()->GetPlayer()->getName() + "! I can see you are doing pretty well.");
	tempVec.push_back("The time for you to choose a vocation has come.");
	tempVec.push_back("There are 2 vocations: Sorcerer and Warrior.");
	tempVec.push_back("Speak to each of the masters ahead to learn details");
	tempVec.push_back("about each vocation. And CHOOSE WISELY!");
	tempVec.push_back("You only get to choose your vocation ONCE!");
	whiteKnightDialog1 = new SpeechBubble(WhiteKnight->getAddressOfX(), WhiteKnight->getAddressOfY(), tempVec);
	WhiteKnight->speechBubbles.push_back(whiteKnightDialog1);
	speechBubbles.push_back(whiteKnightDialog1);
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
			steveDialog2->Show();
		else
			steveDialog1->Show();
	}
	else {
		steveDialog1->Hide();
		steveDialog2->Hide();
	}

	if (WhiteKnight->isSpeaking())
		whiteKnightDialog1->Show();
	else
		whiteKnightDialog1->Hide();
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
	for (TextBox *obj: textBoxes)
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

	tutorialSwitch = new Switch(11, 12, FPS*4.6);
	switches.push_back(tutorialSwitch);

	tutorialPortal = new Portal(false, 20, 12, 25, 12);
	portals.push_back(tutorialPortal);

	InitializeDialogs();

	tutorialDialog1->Show();
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

		// if left mouse pressed and any being is speaking, stop speaking
		if (RPG::GetInstance()->Mouse->left_mouse_button_released)
			for (LivingBeing *being: livingBeings)
				being->StopSpeaking();

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

	for (TextBox *obj: textBoxes)
		delete obj;
	textBoxes.clear();

	for (SpeechBubble *obj: speechBubbles)
		delete obj;
	speechBubbles.clear();

	al_destroy_bitmap(sideBar);
}