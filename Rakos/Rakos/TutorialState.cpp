#include "TutorialState.h"
#include "RPG.h"
#include "globalFunctions.h"

void TutorialState::InitializeLivingBeings() {
	livingBeings.clear();

	// initializing player
	player = RPG::GetInstance()->GetPlayer();
	livingBeings.push_back(player);


	// initializing npcs
	steve = new NPC("Steve", 160, 200, 230, 320, explorer_greenPng);
	livingBeings.push_back(steve);

	knight = new NPC("White Knight", 670, 180, 740, 240, knight_whitePng);
	livingBeings.push_back(knight);

	sorcerer = new NPC("Sorcerer", 985, 90, sorcerer_bluePng);
	livingBeings.push_back(sorcerer);

	warrior = new NPC("Warrior", 985, 250, warrior_yellowPng);
	livingBeings.push_back(warrior);
	

	// initializing creatures
	rabbit = new Rabbit(180, 390, 240, 390);
	livingBeings.push_back(rabbit);
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


void TutorialState::Initialize() {
	// loading map
	LoadMap(TutorialWorldMapPath, worldMap);
	unaccessibleTiles.push_back(0);

	// loading images
	side_bar = al_load_bitmap(SideBarPath);
	if (!side_bar) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load side bar bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	// loading npc dialogs
	tutorial_dialog_1 = al_load_bitmap(TutorialDialog1);
	tutorial_dialog_2 = al_load_bitmap(TutorialDialog2);
	steve_dialog_1 = al_load_bitmap(SteveDialog1);
	steve_dialog_2 = al_load_bitmap(SteveDialog2);
	if (!tutorial_dialog_1 || !tutorial_dialog_2 || !steve_dialog_1 || !steve_dialog_2) {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load one or more dialogs.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	InitializeLivingBeings();

	tutorialPortal = new Portal(false, 12, 3, 17, 3);
	portals.push_back(tutorialPortal);

	tutorialSwitch = new Switch(3, 3, FPS*4.6);
	switches.push_back(tutorialSwitch);
}

bool TutorialState::Update(ALLEGRO_EVENT *ev) {
	al_get_keyboard_state(&keyState);

	RPG::GetInstance()->RemoveDeadLivingBeingsFromVector(livingBeings);

	if (ev->type == ALLEGRO_EVENT_TIMER) {
		if (ev->timer.source == RPG::GetInstance()->GetTimer(_RegularTimer)) {
			player->ControlAttackRate();

			tutorialPortal->CheckIfPlayerPassedThrough(player);
			
			// player wants to chat
			if (al_key_down(&keyState, ALLEGRO_KEY_C) &&
				calculateDistance(player->getX(), player->getY(), steve->getX(), steve->getY()) < 40) {
				//show_tutorial_dialog_2 = false;
				/*
				if (rabbit->isDead())
					show_steve_dialog_2 = true;
				else
					show_steve_dialog_1 = true;*/

				//player_has_talked_to_steve = true;
				player->setWeapon(RPG::GetInstance()->GetWeapon(_Knife));
				steve->setActiveState(false);
			}
			if (calculateDistance(player->getX(), player->getY(), steve->getX(), steve->getY()) > 60) {
				//show_steve_dialog_1 = false;
				//show_steve_dialog_2 = false;
				steve->setActiveState(true);
			}
			
			// player attacks
			if (al_key_down(&keyState, ALLEGRO_KEY_K) && player->CanAttack() &&
				calculateDistance(player->getX(), player->getY(), rabbit->getX(), rabbit->getY()) < 40 &&
				((player->getDir() != UP && rabbit->getDir() != DOWN) || (player->getDir() != LEFT && rabbit->getDir() != RIGHT) ||
				(player->getDir() != RIGHT && rabbit->getDir() != LEFT) || (player->getDir() != DOWN && rabbit->getDir() != UP))) {
				player->CanNotAttackNow();
				rabbit->takeHP(player->getWeapon()->Damage());
				if (rabbit->getHP() <= 0)
					rabbit->setDeadState(true);
			}
			
			player->Move(keyState, worldMap);

			UpdateSwitches();

			// moving npcs and creatures
			for (unsigned int i = 1; i < livingBeings.size(); i++)
				if (!livingBeings[i]->isDead())
					livingBeings[i]->Move();

			// collisions
			player->CorrectPositionIfCollidingWithMapLimits(worldMap, unaccessibleTiles);
			for (unsigned int i = 0; i < livingBeings.size(); i++)
				if (livingBeings[i]->getType() != _Player)
					RPG::GetInstance()->UpdateLivingBeingsCollisions(player, livingBeings[i]);

			RPG::GetInstance()->UpdateCamera(worldMap);
		}

		RPG::GetInstance()->UpdateAnimationsFrame(livingBeings);
		RPG::GetInstance()->UpdateAnimationsFrame(portals);

		// sorting vector in the correct drawing order
		sort(livingBeings.begin(), livingBeings.end(), [](LivingBeing *a, LivingBeing *b) { return a->getY() < b->getY(); });

		return true;
	}

	return false;
}

void TutorialState::Draw() {
	DrawMap(worldMap);

	// drawing portals
	for (Portal *obj : portals)
		obj->Draw();

	// drawing switches
	for (Switch *obj : switches)
		obj->Draw();

	// drawing living beings
	for (unsigned int i = 0; i < livingBeings.size(); i++)
		livingBeings[i]->Draw();

	// drawing side bar
	al_draw_bitmap(side_bar, 600 + RPG::GetInstance()->cameraPosition[0], RPG::GetInstance()->cameraPosition[1], NULL);

	// drawing dialogs
	/*
	if (show_tutorial_dialog_1) { al_draw_bitmap(tutorial_dialog_1, 300 + RPG::GetInstance()->cameraPosition[0] - al_get_bitmap_width(tutorial_dialog_1)/2, RPG::GetInstance()->cameraPosition[1] + ScreenHeight/4, NULL); }
	else if (show_tutorial_dialog_2) { al_draw_bitmap(tutorial_dialog_2, 300 + RPG::GetInstance()->cameraPosition[0] - al_get_bitmap_width(tutorial_dialog_2)/2, RPG::GetInstance()->cameraPosition[1] + ScreenHeight - al_get_bitmap_height(tutorial_dialog_2), NULL); }
	else if (show_steve_dialog_1) { al_draw_bitmap(steve_dialog_1, steve->getX()-85, steve->getY()-al_get_bitmap_height(steve_dialog_1), NULL); }
	else if (show_steve_dialog_2) { al_draw_bitmap(steve_dialog_2, steve->getX()-85, steve->getY()-al_get_bitmap_height(steve_dialog_2), NULL); }
	*/

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

}