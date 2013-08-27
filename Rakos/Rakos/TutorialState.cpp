#include "TutorialState.h"
#include "RPG.h"
#include "globalFunctions.h"

void TutorialState::InitializeLivingBeings() {
	livingBeings.clear();

	// initializing player
	player = RPG::GetInstance()->GetPlayer();
	player->setX(WorldBlockSize*13);
	player->setY(WorldBlockSize*23);
	livingBeings.push_back(player);


	// initializing npcs
	Steve = new NPC("Steve", WorldBlockSize*5, WorldBlockSize*14, explorer_greenPng);
	livingBeings.push_back(Steve);

	WhiteKnight = new NPC("White Knight", WorldBlockSize*18, WorldBlockSize*13, knight_whitePng);
	livingBeings.push_back(WhiteKnight);

	Mage = new NPC("Mage", WorldBlockSize*26, WorldBlockSize*11, mage_bluePng, true);
	livingBeings.push_back(Mage);

	Warrior = new NPC("Warrior", WorldBlockSize*26, WorldBlockSize*14, warrior_yellowPng, true);
	livingBeings.push_back(Warrior);
	

	// initializing creatures
	rabbit = new Rabbit(WorldBlockSize*5, WorldBlockSize*19);
	livingBeings.push_back(rabbit);
}

void TutorialState::InitializeDialogs() {
	// temporary vector to initialize text boxes content
	vector<string> tempVec;

	switch (RPG::GetInstance()->LanguageBeingUsed) {
	case _English:
		{
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
			tempVec.push_back("There are 2 vocations: Mage and Warrior.");
			tempVec.push_back("Speak to each of the Masters ahead to learn details");
			tempVec.push_back("about each vocation. And CHOOSE WISELY!");
			tempVec.push_back("You only get to choose your vocation ONCE!");
			whiteKnightDialog = new SpeechBubble(WhiteKnight->getAddressOfX(), WhiteKnight->getAddressOfY(), tempVec);
			WhiteKnight->speechBubbles.push_back(whiteKnightDialog);
			speechBubbles.push_back(whiteKnightDialog);

			tempVec.clear();
			tempVec.push_back("Greetings " + RPG::GetInstance()->GetPlayer()->getName() + ".");
			tempVec.push_back("Mages are the masters of MAGIC!");
			tempVec.push_back("We don't need to use swords. We use magic and");
			tempVec.push_back("powerful skills to attack monsters and defend");
			tempVec.push_back("ourselves from our enemies! However, we need to");
			tempVec.push_back("RUN from them instead of fighting close to them");
			tempVec.push_back("because we aren't as good as warriors using shields.");
			tempVec.push_back("");
			tempVec.push_back("If you want to become a Mage, press <ENTER> now.");
			mageDialog = new SpeechBubble(Mage->getAddressOfX(), Mage->getAddressOfY(), tempVec);
			Mage->speechBubbles.push_back(mageDialog);
			speechBubbles.push_back(mageDialog);

			tempVec.clear();
			tempVec.push_back("Very well " + RPG::GetInstance()->GetPlayer()->getName() + "!");
			tempVec.push_back("You are now officially a Mage!");
			tempVec.push_back("Take this WAND as a gift.");
			tempVec.push_back("");
			tempVec.push_back("Now go through the portal located East.");
			tempVec.push_back("It will take you to the Temple of Rakos.");
			tempVec.push_back("Have fun, brave adventurer!");
			mageDialogIfPlayerIsAMage = new SpeechBubble(Mage->getAddressOfX(), Mage->getAddressOfY(), tempVec);
			Mage->speechBubbles.push_back(mageDialogIfPlayerIsAMage);
			speechBubbles.push_back(mageDialogIfPlayerIsAMage);

			tempVec.clear();
			tempVec.push_back("Hi again " + RPG::GetInstance()->GetPlayer()->getName() + "!");
			tempVec.push_back("I can see you have become a Warrior.");
			tempVec.push_back("");
			tempVec.push_back("Go through the portal located East.");
			tempVec.push_back("It will take you to the Temple of Rakos.");
			tempVec.push_back("Have fun, brave adventurer!");
			mageDialogIfPlayerIsNOTAMage = new SpeechBubble(Mage->getAddressOfX(), Mage->getAddressOfY(), tempVec);
			Mage->speechBubbles.push_back(mageDialogIfPlayerIsNOTAMage);
			speechBubbles.push_back(mageDialogIfPlayerIsNOTAMage);

			tempVec.clear();
			tempVec.push_back("Hey there " + RPG::GetInstance()->GetPlayer()->getName() + ".");
			tempVec.push_back("Warriors are the SWORD experts!");
			tempVec.push_back("We use a wide range of weapons such as swords,");
			tempVec.push_back("axes and spears. We also use shields to defend ourselves.");
			tempVec.push_back("We fight CLOSE to the enemy, we are fearless!");
			tempVec.push_back("Join us! You will never be defeated and");
			tempVec.push_back("even Dragons will fear the swing of your sword.");
			tempVec.push_back("");
			tempVec.push_back("If you want to become a Warrior, press <ENTER> now.");
			warriorDialog = new SpeechBubble(Warrior->getAddressOfX(), Warrior->getAddressOfY(), tempVec);
			Warrior->speechBubbles.push_back(warriorDialog);
			speechBubbles.push_back(warriorDialog);

			tempVec.clear();
			tempVec.push_back("Very well " + RPG::GetInstance()->GetPlayer()->getName() + "!");
			tempVec.push_back("You are now officially a Warrior!");
			tempVec.push_back("Take this SWORD as a gift.");
			tempVec.push_back("");
			tempVec.push_back("Now go through the portal located East.");
			tempVec.push_back("It will take you to the Temple of Rakos.");
			tempVec.push_back("Have fun, brave adventurer!");
			warriorDialogIfPlayerIsAWarrior = new SpeechBubble(Warrior->getAddressOfX(), Warrior->getAddressOfY(), tempVec);
			Warrior->speechBubbles.push_back(warriorDialogIfPlayerIsAWarrior);
			speechBubbles.push_back(warriorDialogIfPlayerIsAWarrior);

			tempVec.clear();
			tempVec.push_back("Hi again " + RPG::GetInstance()->GetPlayer()->getName() + "!");
			tempVec.push_back("I can see you have become a Mage.");
			tempVec.push_back("");
			tempVec.push_back("Go through the portal located East.");
			tempVec.push_back("It will take you to the Temple of Rakos.");
			tempVec.push_back("Have fun, brave adventurer!");
			warriorDialogIfPlayerIsNOTAWarrior = new SpeechBubble(Warrior->getAddressOfX(), Warrior->getAddressOfY(), tempVec);
			Warrior->speechBubbles.push_back(warriorDialogIfPlayerIsNOTAWarrior);
			speechBubbles.push_back(warriorDialogIfPlayerIsNOTAWarrior);

			break;
		}
	case _Portuguese:
		{
			tempVec.clear();
			tempVec.push_back("Bem vindo a Rakos!");
			tempVec.push_back("Caminha usando as teclas WASD do teclado.");
			tempVec.push_back("Tenta caminhar agora.");
			tutorialDialog1 = new TextBox(_Center, tempVec);
			textBoxes.push_back(tutorialDialog1);

			tempVec.clear();
			tempVec.push_back("Parabéns!");
			tempVec.push_back("Agora devias ir falar com o Steve.");
			tempVec.push_back("Para falar, aproxima-te dele e pressiona a tecla <C>.");
			tutorialDialog2 = new TextBox(_Bottom, tempVec);
			textBoxes.push_back(tutorialDialog2);

			tempVec.clear();
			tempVec.push_back("Olá! Deves ser novo por aqui...");
			tempVec.push_back("Toma esta faca e mata aquele coelho.");
			tempVec.push_back("Carrega na tecla <K> para atacar.");
			tempVec.push_back("Depois de terminares, volta a falar comigo.");
			steveDialog1 = new SpeechBubble(Steve->getAddressOfX(), Steve->getAddressOfY(), tempVec);
			Steve->speechBubbles.push_back(steveDialog1);
			speechBubbles.push_back(steveDialog1);

			tempVec.clear();
			tempVec.push_back("Muito bem! Agora caminha em cima daquele");
			tempVec.push_back("botão castanho e um portal irá abrir-se.");
			tempVec.push_back("Atravessa o portal! Aqui está uma dica:");
			tempVec.push_back("Carrega na tecla <SHIFT> para correres.");
			steveDialog2 = new SpeechBubble(Steve->getAddressOfX(), Steve->getAddressOfY(), tempVec);
			Steve->speechBubbles.push_back(steveDialog2);
			speechBubbles.push_back(steveDialog2);

			tempVec.clear();
			tempVec.push_back("Olá " + RPG::GetInstance()->GetPlayer()->getName() + "! Estás a safar-te bastante bem.");
			tempVec.push_back("Chegou a altura de escolheres uma profissão.");
			tempVec.push_back("Existem 2 profissões: Mage e Warrior.");
			tempVec.push_back("Fala com cada um dos Mestres para aprenderes detalhes");
			tempVec.push_back("sobre cada profissão. ESCOLHE BEM!");
			tempVec.push_back("Só podes escolher a tua profissão uma vez!");
			whiteKnightDialog = new SpeechBubble(WhiteKnight->getAddressOfX(), WhiteKnight->getAddressOfY(), tempVec);
			WhiteKnight->speechBubbles.push_back(whiteKnightDialog);
			speechBubbles.push_back(whiteKnightDialog);

			tempVec.clear();
			tempVec.push_back("Saudações " + RPG::GetInstance()->GetPlayer()->getName() + ".");
			tempVec.push_back("Os Mages são os mestres da MAGIA!");
			tempVec.push_back("Nós não usamos espadas. Usamos magia e");
			tempVec.push_back("skills poderosas para atacar monstros e nos");
			tempVec.push_back("defender dos inimigos! Contudo, precisamos de");
			tempVec.push_back("estar quase sempre a CORRER em vez de lutar");
			tempVec.push_back("perto deles porque não somos tão bons como");
			tempVec.push_back("os Warriors a usar escudos.");
			tempVec.push_back("");
			tempVec.push_back("Se queres ser um Mage, carrega agora na tecla <ENTER>.");
			mageDialog = new SpeechBubble(Mage->getAddressOfX(), Mage->getAddressOfY(), tempVec);
			Mage->speechBubbles.push_back(mageDialog);
			speechBubbles.push_back(mageDialog);

			tempVec.clear();
			tempVec.push_back("Muito bem " + RPG::GetInstance()->GetPlayer()->getName() + "!");
			tempVec.push_back("Agora és oficialmente um Mage!");
			tempVec.push_back("Aceita esta VARINHA como presente.");
			tempVec.push_back("");
			tempVec.push_back("Agora atravessa o portal a Este daqui.");
			tempVec.push_back("Vai levar-te para o Templo de Rakos.");
			tempVec.push_back("Diverte-te, corajoso aventureiro!");
			mageDialogIfPlayerIsAMage = new SpeechBubble(Mage->getAddressOfX(), Mage->getAddressOfY(), tempVec);
			Mage->speechBubbles.push_back(mageDialogIfPlayerIsAMage);
			speechBubbles.push_back(mageDialogIfPlayerIsAMage);

			tempVec.clear();
			tempVec.push_back("Olá outra vez, " + RPG::GetInstance()->GetPlayer()->getName() + "!");
			tempVec.push_back("Vejo que te tornaste num Warrior");
			tempVec.push_back("");
			tempVec.push_back("Atravessa o portal a Este daqui.");
			tempVec.push_back("Vai levar-te para o Templo de Rakos.");
			tempVec.push_back("Diverte-te, corajoso aventureiro!");
			mageDialogIfPlayerIsNOTAMage = new SpeechBubble(Mage->getAddressOfX(), Mage->getAddressOfY(), tempVec);
			Mage->speechBubbles.push_back(mageDialogIfPlayerIsNOTAMage);
			speechBubbles.push_back(mageDialogIfPlayerIsNOTAMage);

			tempVec.clear();
			tempVec.push_back("Hey " + RPG::GetInstance()->GetPlayer()->getName() + ".");
			tempVec.push_back("Os Warriors sao exímios com ESPADAS!");
			tempVec.push_back("Usamos uma grande variedade de armas como espadas");
			tempVec.push_back("machados e lanças. Também usamos escudos para nos defender.");
			tempVec.push_back("Lutamos PERTO do inimigo, não temos medo!");
			tempVec.push_back("Junta-te a nós! Nunca serás derrotado e");
			tempVec.push_back("até os Dragões vão ter medo da tua espada.");
			tempVec.push_back("");
			tempVec.push_back("Se queres ser um Warrior, carrega agora na tecla <ENTER>.");
			warriorDialog = new SpeechBubble(Warrior->getAddressOfX(), Warrior->getAddressOfY(), tempVec);
			Warrior->speechBubbles.push_back(warriorDialog);
			speechBubbles.push_back(warriorDialog);

			tempVec.clear();
			tempVec.push_back("Muito bem " + RPG::GetInstance()->GetPlayer()->getName() + "!");
			tempVec.push_back("Agora és oficialmente um Warrior!");
			tempVec.push_back("Aceita esta ESPADA como presente.");
			tempVec.push_back("");
			tempVec.push_back("Agora atravessa o portal a Este daqui.");
			tempVec.push_back("Vai levar-te para o Templo de Rakos.");
			tempVec.push_back("Diverte-te, corajoso aventureiro!");
			warriorDialogIfPlayerIsAWarrior = new SpeechBubble(Warrior->getAddressOfX(), Warrior->getAddressOfY(), tempVec);
			Warrior->speechBubbles.push_back(warriorDialogIfPlayerIsAWarrior);
			speechBubbles.push_back(warriorDialogIfPlayerIsAWarrior);

			tempVec.clear();
			tempVec.push_back("Olá outra vez, " + RPG::GetInstance()->GetPlayer()->getName() + "!");
			tempVec.push_back("Vejo que te tornaste um Mage");
			tempVec.push_back("");
			tempVec.push_back("Atravessa o portal a Este daqui.");
			tempVec.push_back("Vai levar-te para o Templo de Rakos.");
			tempVec.push_back("Diverte-te, corajoso aventureiro!");
			warriorDialogIfPlayerIsNOTAWarrior = new SpeechBubble(Warrior->getAddressOfX(), Warrior->getAddressOfY(), tempVec);
			Warrior->speechBubbles.push_back(warriorDialogIfPlayerIsNOTAWarrior);
			speechBubbles.push_back(warriorDialogIfPlayerIsNOTAWarrior);

			break;
		}
	}
}

void TutorialState::InitializeConfirmationDialogs() {
	string tempTitle;
	vector<string> tempVec;

	tempVec.clear();
	switch (RPG::GetInstance()->LanguageBeingUsed) {
	case _English:
		tempTitle = "ATTENTION";
		tempVec.push_back("You only get to choose your vocation ONCE!");
		tempVec.push_back("Do you really want to become a Mage?");
		break;
	case _Portuguese:
		tempTitle = "ATENÇÃO";
		tempVec.push_back("Só podes escolher a tua profissão uma vez!");
		tempVec.push_back("Tens a certeza que te queres tornar um Mage?");
		break;
	}
	mageConfirmation = new ConfirmationDialog(tempTitle, tempVec);
	confirmationDialogs.push_back(mageConfirmation);

	tempVec.clear();
	switch (RPG::GetInstance()->LanguageBeingUsed) {
	case _English:
		tempTitle = "ATTENTION";
		tempVec.push_back("You only get to choose your vocation ONCE!");
		tempVec.push_back("Do you really want to become a Warrior?");
		break;
	case _Portuguese:
		tempTitle = "ATENÇÃO";
		tempVec.push_back("Só podes escolher a tua profissão uma vez!");
		tempVec.push_back("Tens a certeza que te queres tornar um Warrior?");
		break;
	}
	warriorConfirmation = new ConfirmationDialog(tempTitle, tempVec);
	confirmationDialogs.push_back(warriorConfirmation);
}

void TutorialState::Initialize() {
	// loading map
	LoadMap(TutorialMapPath, &worldMapLevel1, &worldMapLevel2);
	worldMapLevels.push_back(&worldMapLevel1);
	worldMapLevels.push_back(&worldMapLevel2);

	RPG::GetInstance()->LoadAccessibleTiles(level1AccessibleTiles, level2AccessibleTiles);
	levelsAccessibleTiles.push_back(&level1AccessibleTiles);
	levelsAccessibleTiles.push_back(&level2AccessibleTiles);

	seaAnimationFrame = 0;

	sideBar = new SideBar(&livingBeings);

	InitializeLivingBeings();
	InitializeDialogs();
	InitializeConfirmationDialogs();

	tutorialSwitch = new Switch(4, 12, FPS*4.6);
	switches.push_back(tutorialSwitch);

	tutorialPortal = new Portal(false, 13, 12, 18, 12);
	portals.push_back(tutorialPortal);

	portalToRakos = new BasicPortal(false, 45, 8);

	tutorialDialog1->Show();
	playerHasTalkedToSteve = false;
}


void TutorialState::MoveLivingBeings(ALLEGRO_EVENT *ev) {
	// moving player, npcs and creatures
	if (ev->timer.source == RPG::GetInstance()->GetTimer(_PlayerMoveTimer))
		player->Move(keyState, worldMapLevels, levelsAccessibleTiles);
	for (unsigned int i = 1; i < livingBeings.size(); i++)
		if (!livingBeings[i]->isDead())
			if (ev->timer.source == RPG::GetInstance()->GetTimer(livingBeings[i]->getTimerType()))
				livingBeings[i]->Move(worldMapLevels, levelsAccessibleTiles);

	// checking if something collided with something
	for (unsigned int i = 0; i < livingBeings.size()-1; i++)
		for (unsigned int j = i+1; j < livingBeings.size(); j++)
			RPG::GetInstance()->UpdateLivingBeingsCollisions(livingBeings[i], livingBeings[j]);
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
		whiteKnightDialog->Show();
	else
		whiteKnightDialog->Hide();

	if (Mage->isSpeaking()) {
		switch (player->getVocation()) {
		case _NoVocation:
			mageDialog->Show();
			break;
		case _Mage:
			mageDialog->Hide();
			mageDialogIfPlayerIsAMage->Show();
			break;
		case _Warrior:
			mageDialog->Hide();
			mageDialogIfPlayerIsNOTAMage->Show();
			break;
		}
	}
	else {
		mageDialog->Hide();
		mageDialogIfPlayerIsAMage->Hide();
		mageDialogIfPlayerIsNOTAMage->Hide();
	}

	if (Warrior->isSpeaking()) {
		switch (player->getVocation()) {
		case _NoVocation:
			warriorDialog->Show();
			break;
		case _Warrior:
			warriorDialog->Hide();
			warriorDialogIfPlayerIsAWarrior->Show();
			break;
		case _Mage:
			warriorDialog->Hide();
			warriorDialogIfPlayerIsNOTAWarrior->Show();
			break;
		}
	}
	else {
		warriorDialog->Hide();
		warriorDialogIfPlayerIsAWarrior->Hide();
		warriorDialogIfPlayerIsNOTAWarrior->Hide();
	}
}

bool TutorialState::CheckIfPlayerChoseAVocation(ALLEGRO_EVENT *ev) {
	// mage confirmation dialog
	switch (mageConfirmation->Update()) {
	case 2:
		// nothing chosen
		break;
	case 0:
		cout << "NO button pressed." << endl;
		break;
	case 1:
		cout << "YES button pressed." << endl;
		player->setVocation(_Mage);
		player->setWeapon(RPG::GetInstance()->GetWeapon(_Wand));
		// setting this to false to prevent speech bubbles of being closed
		RPG::GetInstance()->Mouse->leftMouseButtonReleased = false;
		Mage->Speak();
		mageDialogIfPlayerIsAMage->Show();
		portalToRakos->Open();
		break;
	}

	// warrior confirmation dialog
	switch (warriorConfirmation->Update()) {
	case 2:
		// nothing chosen
		break;
	case 0:
		cout << "NO button pressed." << endl;
		break;
	case 1:
		cout << "YES button pressed." << endl;
		player->setVocation(_Warrior);
		player->setWeapon(RPG::GetInstance()->GetWeapon(_Sword));
		// setting this to false to prevent speech bubbles of being closed
		RPG::GetInstance()->Mouse->leftMouseButtonReleased = false;
		Warrior->Speak();
		warriorDialogIfPlayerIsAWarrior->Show();
		portalToRakos->Open();
		break;
	}

	// checking if any confirmation dialog needs to be open
	if (player->getVocation() == _NoVocation) {
		if (ev->type == ALLEGRO_EVENT_KEY_UP && ev->keyboard.keycode == ALLEGRO_KEY_ENTER) {
			if (Mage->isSpeaking()) {
				mageConfirmation->Open();
				warriorConfirmation->Close();
			}
			else if (Warrior->isSpeaking()) {
				warriorConfirmation->Open();
				mageConfirmation->Close();
			}

			return true;
		}
	}

	return false;
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

			// if player went through portal to Rakos and has chosen a vocation, teleport it to Rakos Temple
			if (portalToRakos->PassedThrough(player)) {
				if (player->getVocation() != _NoVocation) {
					RPG::GetInstance()->ChangeState(_Rakos);
					return true;
				}
			}

			UpdateDialogs();
		}

		// controlling sea animation
		if (ev->timer.source == RPG::GetInstance()->GetTimer(_DrawTimer)) {
			seaAnimationFrame++;
			if (seaAnimationFrame > WorldBlockSize-1)
				seaAnimationFrame = 0;
		}

		RPG::GetInstance()->UpdateCamera(worldMapLevel1, livingBeings);
		RPG::GetInstance()->UpdateAnimationsFrame(livingBeings);
		RPG::GetInstance()->UpdateAnimationsFrame(portals);
		if (ev->timer.source == RPG::GetInstance()->GetTimer(_PortalAnimTimer))
			portalToRakos->UpdateAnimationFrame();
		RPG::GetInstance()->UpdateWeaponAndShieldPositions(livingBeings);
		RPG::GetInstance()->UpdateWeaponAttackAnimations(livingBeings);

		player->updateLevel();
		sideBar->Update();

		// if left mouse pressed and any being is speaking, stop speaking
		if (RPG::GetInstance()->Mouse->leftMouseButtonReleased)
			for (LivingBeing *being: livingBeings)
				being->StopSpeaking();

		// sorting vector in the correct drawing order
		sort(livingBeings.begin(), livingBeings.end(), [](LivingBeing *a, LivingBeing *b) { return a->getY() < b->getY(); });

		draw = true;
	}

	draw = CheckIfPlayerChoseAVocation(ev);

	return draw;
}


void TutorialState::Draw() {
	// drawing world map
	DrawMap(worldMapLevel1, worldMapLevel2, seaAnimationFrame);

	// drawing switches
	for (Switch *obj : switches)
		obj->Draw();

	// drawing portals
	portalToRakos->Draw();
	for (Portal *obj : portals)
		obj->Draw();

	// drawing living beings
	for (unsigned int i = 0; i < livingBeings.size(); i++)
		livingBeings[i]->Draw();

	// drawing side bar
	sideBar->Draw();

	// drawing text boxes
	for (TextBox *obj: textBoxes)
		obj->Draw();

	// drawing confirmation dialogs
	for (ConfirmationDialog *obj: confirmationDialogs)
		obj->Draw();

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
		if (being->getType() != _Player)
			delete being;
	livingBeings.clear();

	for (Switch *obj: switches)
		delete obj;
	switches.clear();

	delete portalToRakos;
	for (Portal *obj: portals)
		delete obj;
	portals.clear();

	for (TextBox *obj: textBoxes)
		delete obj;
	textBoxes.clear();

	for (SpeechBubble *obj: speechBubbles)
		delete obj;
	speechBubbles.clear();

	for (ConfirmationDialog *obj: confirmationDialogs)
		delete obj;
	confirmationDialogs.clear();

	delete sideBar;
}