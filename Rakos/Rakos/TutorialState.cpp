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

void TutorialState::UpdateAnimations(ALLEGRO_EVENT *ev) {
	// creatures and npcs
	if (ev->timer.source == RPG::GetInstance()->GetTimer(_DrawTimer))
		for (LivingBeing *obj : livingBeings)
			if (obj->getType() != _Player)
				obj->UpdateAnimationFrame();

	// player
	if (ev->timer.source == RPG::GetInstance()->GetTimer(_PlayerAnimTimer))
		player->UpdateAnimationFrame();
}

void TutorialState::CheckIfAnyLivingBeingWasKilled() {
	for (unsigned int i = 1; i < livingBeings.size(); i++)
		if (livingBeings[i]->isDead())
			livingBeings.erase(livingBeings.begin() + i);
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
	portal1 = new Portal();

	switch_cooldown = 0;
	switch_pressed = false;
}

bool TutorialState::Update(ALLEGRO_EVENT *ev) {
	al_get_keyboard_state(&keyState);

	CheckIfAnyLivingBeingWasKilled();

	if (ev->type == ALLEGRO_EVENT_TIMER) {
		if (ev->timer.source == RPG::GetInstance()->GetTimer(_RegularTimer)) {
			player->ControlAttackRate();

			// player used portal
			if (switch_pressed &&
				(483 <= player->getFeetX() && player->getFeetX() <= 515) &&
				(123 <= player->getFeetY() && player->getFeetY() <= 156)) {
				player->setX(700-16);
				player->setY(142-32);
			}
			
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

			// --- interactive tiles --- //
			// portal
			if ((126 <= player->getFeetX() && player->getFeetX() <= 155) && (130 <= player->getFeetY() && player->getFeetY() <= 155))
				switch_pressed = true;
			else {
				if (switch_pressed)
					switch_cooldown++;
				if (switch_cooldown > FPS*4.6) {
					switch_cooldown = 0;
					switch_pressed = false;
				}
			}

			// moving npcs and creatures
			for (unsigned int i = 1; i < livingBeings.size(); i++)
				if (!livingBeings[i]->isDead())
					livingBeings[i]->Move();

			//  Collisions
			player->CorrectPositionIfCollidingWithMapLimits(worldMap, unaccessibleTiles);
			for (unsigned int i = 0; i < livingBeings.size(); i++)
				if (livingBeings[i]->getType() != _Player)
					RPG::GetInstance()->UpdateLivingBeingsCollisions(player, livingBeings[i]);

			RPG::GetInstance()->UpdateCamera(worldMap);
		}

		UpdateAnimations(ev);

		// sorting vector in the correct drawing order
		sort(livingBeings.begin(), livingBeings.end(), [](LivingBeing *a, LivingBeing *b) { return a->getY() < b->getY(); });

		return true;
	}

	return false;
}

void TutorialState::Draw()
{
	/* drawing world map */
	for(unsigned int i = 0; i < worldMap.size(); i++) {
		for(unsigned int j = 0; j < worldMap[i].size(); j++) {
			if (switch_pressed && worldMap[i][j] == 14)
				al_draw_bitmap_region(RPG::GetInstance()->GetTileSet(), 15 * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL);
			else if (!switch_pressed && worldMap[i][j] == 16)
				al_draw_bitmap_region(RPG::GetInstance()->GetTileSet(), 1 * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL);
			else
				al_draw_bitmap_region(RPG::GetInstance()->GetTileSet(), worldMap[i][j] * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL);
		}
	}

	/* drawing moving things */
	for (unsigned int i = 0; i < livingBeings.size(); i++) {
		livingBeings[i]->Draw();
	}

	/* drawing side bar */
	al_draw_bitmap(side_bar, 600 + RPG::GetInstance()->cameraPosition[0], RPG::GetInstance()->cameraPosition[1], NULL);

	/* drawing dialogs */
	/*
	if (show_tutorial_dialog_1) { al_draw_bitmap(tutorial_dialog_1, 300 + RPG::GetInstance()->cameraPosition[0] - al_get_bitmap_width(tutorial_dialog_1)/2, RPG::GetInstance()->cameraPosition[1] + ScreenHeight/4, NULL); }
	else if (show_tutorial_dialog_2) { al_draw_bitmap(tutorial_dialog_2, 300 + RPG::GetInstance()->cameraPosition[0] - al_get_bitmap_width(tutorial_dialog_2)/2, RPG::GetInstance()->cameraPosition[1] + ScreenHeight - al_get_bitmap_height(tutorial_dialog_2), NULL); }
	else if (show_steve_dialog_1) { al_draw_bitmap(steve_dialog_1, steve->getX()-85, steve->getY()-al_get_bitmap_height(steve_dialog_1), NULL); }
	else if (show_steve_dialog_2) { al_draw_bitmap(steve_dialog_2, steve->getX()-85, steve->getY()-al_get_bitmap_height(steve_dialog_2), NULL); }
	*/
	/*
	// player temp coords
	cout << "Player coords: " << player->getFeetX() << " " << player->getFeetY()
		<< "\t\t" << player->getX() << " " << player->getY() << endl;
	// -----------------
	*/
}

void TutorialState::Terminate() {
	unaccessibleTiles.clear();
	al_destroy_bitmap(tutorial_dialog_1);
	al_destroy_bitmap(tutorial_dialog_2);
	al_destroy_bitmap(steve_dialog_1);
	al_destroy_bitmap(steve_dialog_2);
}