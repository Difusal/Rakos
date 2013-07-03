#include "TutorialState.h"
#include "StateControl.h"
#include "FileManager.h"

void drawLifeBar(MovingObject *obj)
{
	int bar_width = 40, bar_height = 5;
	int pos_x = obj->getX() + al_get_bitmap_width(obj->getBitmap())/4/2 - bar_width/2;
	int pos_y = obj->getY() - 5;
	ALLEGRO_COLOR color;

	float percentage = obj->getHP() * 100.0 / obj->getMaxHP();

	if (percentage >= 50) { color = Green; }
	else if (percentage >= 25) { color = Yellow; }
	else { color = Red; }
	
	int hp_width = bar_width * percentage / 100.0;

	al_draw_filled_rectangle(pos_x-1, pos_y-1, pos_x+bar_width+1, pos_y+bar_height+1, Black);
	al_draw_filled_rectangle(pos_x, pos_y, pos_x+hp_width, pos_y+bar_height, color);
}

void TutorialState::LoadWeapons()
{
	no_weapon = new Weapon();
	knife = new Weapon("knife", 1, 2);
}

bool TutorialState::mapCollision(int Dir, const vector<int> &tiles)
{
	int north_scan = world_map[(player->getFeetY()-15)/WorldBlockSize][player->getFeetX()/WorldBlockSize];
	int ne_scan = world_map[(player->getFeetY()-15)/WorldBlockSize][(player->getFeetX()+25)/WorldBlockSize];
	int east_scan = world_map[player->getFeetY()/WorldBlockSize][(player->getFeetX()+25)/WorldBlockSize];
	int se_scan = world_map[(player->getFeetY()+25)/WorldBlockSize][(player->getFeetX()+25)/WorldBlockSize];
	int south_scan = world_map[(player->getFeetY()+25)/WorldBlockSize][player->getFeetX()/WorldBlockSize];
	int sw_scan = world_map[(player->getFeetY()+25)/WorldBlockSize][(player->getFeetX()-25)/WorldBlockSize];
	int west_scan = world_map[player->getFeetY()/WorldBlockSize][(player->getFeetX()-25)/WorldBlockSize];
	int nw_scan = world_map[(player->getFeetY()-15)/WorldBlockSize][(player->getFeetX()-25)/WorldBlockSize];

	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		switch (Dir)
		{
		case UP:
			if (north_scan == tiles[i] || east_scan == tiles[i] ||
				west_scan == tiles[i] || ne_scan == tiles[i] ||
				nw_scan == tiles[i])
				return 1;
			break;
		case DOWN:
			if (east_scan == tiles[i] || south_scan == tiles[i] ||
				west_scan == tiles[i] || se_scan == tiles[i] ||
				sw_scan == tiles[i])
				return 1;
			break;
		case LEFT:
			if (north_scan == tiles[i] || south_scan == tiles[i] ||
				west_scan == tiles[i] || sw_scan == tiles[i] ||
				nw_scan == tiles[i])
				return 1;
			break;
		case RIGHT:
			if (north_scan == tiles[i] || east_scan == tiles[i] ||
				south_scan == tiles[i] || ne_scan == tiles[i] ||
				se_scan == tiles[i])
				return 1;
			break;
		}
	}

	return 0;
}


void TutorialState::updateRunningState()
{
	if (al_key_down(&keyState, ALLEGRO_KEY_LSHIFT))
	{
		player->setMoveSpeed(HumansRunningSpeed);
		if (!player->getRunningState())
			al_set_timer_speed(StateControl::GetInstance()->GetTimer(2), 1.0/(1.5*drawFPS));
		player->setRunningState(true);
	}
	else
	{
		player->setMoveSpeed(HumansWalkingSpeed);
		if (player->getRunningState())
			al_set_timer_speed(StateControl::GetInstance()->GetTimer(2), 1.0/drawFPS);
		player->setRunningState(false);
	}
}

void TutorialState::updatePlayerPosition()
{
	player->setActiveState(true);
	if(al_key_down(&keyState, ALLEGRO_KEY_S))
	{
		if (!player_has_talked_to_steve)
		{
			show_tutorial_dialog_1 = false;
			show_tutorial_dialog_2 = true;
		}

		player->setY(player->getY() + player->getMoveSpeed());

		if (player->getY() > world_map.size()*WorldBlockSize - 32)
			player->setY(world_map.size()*WorldBlockSize - 32);

		player->setDir(DOWN);
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_W))
	{
		if (!player_has_talked_to_steve)
		{
			show_tutorial_dialog_1 = false;
			show_tutorial_dialog_2 = true;
		}

		player->setY(player->getY() - player->getMoveSpeed());

		if (player->getY() < 0)
			player->setY(0);

		player->setDir(UP);
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_D))
	{
		if (!player_has_talked_to_steve)
		{
			show_tutorial_dialog_1 = false;
			show_tutorial_dialog_2 = true;
		}

		player->setX(player->getX() + player->getMoveSpeed());

		if (player->getX() > world_map[0].size()*WorldBlockSize - 32)
			player->setX(world_map[0].size()*WorldBlockSize - 32);

		player->setDir(RIGHT);
	}
	else if(al_key_down(&keyState, ALLEGRO_KEY_A))
	{
		if (!player_has_talked_to_steve)
		{
			show_tutorial_dialog_1 = false;
			show_tutorial_dialog_2 = true;
		}

		player->setX(player->getX() - player->getMoveSpeed());

		if (player->getX() < 0)
			player->setX(0);

		player->setDir(LEFT);
	}
	else
		player->setActiveState(false);
}

void TutorialState::updateMovingObjectsCollisions(MovingObject *a, MovingObject *b)
{
	if(b->getActiveState() && boxCollision(b->getX(), b->getY(), a->getX(), a->getY(), 32, 32))
	{
		if (b->getDir() == 0) { b->setY(b->getY() - b->getMoveSpeed()); }
		else if (b->getDir() == 1) { b->setX(b->getX() + b->getMoveSpeed()); }
		else if (b->getDir() == 2) { b->setX(b->getX() - b->getMoveSpeed()); }
		else if (b->getDir() == 3) { b->setY(b->getY() + b->getMoveSpeed()); }
	}
	if(a->getActiveState() && boxCollision(a->getX(), a->getY(), b->getX(), b->getY(), 32, 32))
	{
		if (a->getDir() == 0) { a->setY(a->getY() - a->getMoveSpeed()); }
		else if (a->getDir() == 1) { a->setX(a->getX() + a->getMoveSpeed()); }
		else if (a->getDir() == 2) { a->setX(a->getX() - a->getMoveSpeed()); }
		else if (a->getDir() == 3) { a->setY(a->getY() + a->getMoveSpeed()); }
	}
}

void TutorialState::updateAnimationFrame(MovingObject *obj)
{
	if(obj->getActiveState())
		obj->setBitmapSourceX(obj->getBitmapSourceX() + al_get_bitmap_width(obj->getBitmap())/4);
	else
		obj->setBitmapSourceX(32);

	if(obj->getBitmapSourceX() >= al_get_bitmap_width(obj->getBitmap()))
		obj->setBitmapSourceX(0);

	obj->setBitmapSourceY(obj->getDir());
}

void TutorialState::moveObject(MovingObjectSon *obj)
{
	if (obj->getActiveState() && obj->getType() != playerType)
	{
		switch (obj->getDir())
		{
		default:
		case DOWN:
			obj->setY(obj->getY() + obj->getMoveSpeed());
			if (obj->getY() > obj->getP2_y())
			{
				obj->setY(obj->getP2_y());
				obj->setDir(RIGHT);
			}	
			break;
		case RIGHT:
			obj->setX(obj->getX() + obj->getMoveSpeed());
			if (obj->getX() > obj->getP2_x())
			{
				obj->setX(obj->getP2_x());
				obj->setDir(UP);
			}				
			break;
		case UP:
			obj->setY(obj->getY() - obj->getMoveSpeed());
			if (obj->getY() < obj->getP1_y())
			{
				obj->setY(obj->getP1_y());
				obj->setDir(LEFT);
			}
			break;
		case LEFT:
			obj->setX(obj->getX() - obj->getMoveSpeed());
			if (obj->getX() < obj->getP1_x())
			{
				obj->setX(obj->getP1_x());
				obj->setDir(DOWN);
			}	
			break;
		}
	}
}


void TutorialState::Initialize()
{
	/* loading map */
	LoadMap(TutorialWorldMap, world_map);
	unaccessible_tiles.push_back(0);

	/* loading equipment */
	LoadWeapons();

	/* loading images */
	side_bar = al_load_bitmap(SideBar);
	if (!side_bar)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load side bar bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* loading npc dialogs */
	tutorial_dialog_1 = al_load_bitmap(TutorialDialog1);
	tutorial_dialog_2 = al_load_bitmap(TutorialDialog2);
	steve_dialog_1 = al_load_bitmap(SteveDialog1);
	steve_dialog_2 = al_load_bitmap(SteveDialog2);
	if (!tutorial_dialog_1 || !tutorial_dialog_2 || !steve_dialog_1 || !steve_dialog_2)
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load one or more dialogs.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	// initializing player, npcs, creatures, etc.
	player = new Player(no_weapon, 480, 580);

	steve = new NPC("Steve", 160, 200, 230, 320, explorer_greenPng);
	knight = new NPC("White Knight", 670, 180, 740, 240, knight_whitePng);
	sorcerer = new NPC("Sorcerer", 985, 90, sorcerer_bluePng);
	warrior = new NPC("Warrior", 985, 250, warrior_yellowPng);

	rabbit = new Rabbit(180, 390, 240, 390);

	portal1 = new Portal();

	if (!player->getBitmap() || !rabbit->getBitmap() || !steve->getBitmap() ||
		!knight->getBitmap() || !sorcerer->getBitmap() || !warrior->getBitmap())
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load player bitmap or npc bitmap.", "Your resources folder must be corrupt, please download it again.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}

	/* initializing useful vectors */
	movingCreaturesAndNpcs.clear();
	movingCreaturesAndNpcs.push_back(rabbit);
	movingCreaturesAndNpcs.push_back(steve);
	movingCreaturesAndNpcs.push_back(knight);
	movingCreaturesAndNpcs.push_back(sorcerer);
	movingCreaturesAndNpcs.push_back(warrior);
	allMovingStuff.clear();
	allMovingStuff.push_back(player);
	for (unsigned int i = 0; i < movingCreaturesAndNpcs.size(); i++)
		allMovingStuff.push_back(movingCreaturesAndNpcs[i]);

	attack_cooldown = 0;
	player_can_attack = true;
	switch_cooldown = 0;

	show_tutorial_dialog_1 = true;
	show_tutorial_dialog_2 = false;
	show_steve_dialog_1 = false;
	show_steve_dialog_2 = false;
	player_has_talked_to_steve = false;
	switch_pressed = false;
}

bool TutorialState::Update(ALLEGRO_EVENT * ev)
{
	al_get_keyboard_state(&keyState);

	/* updating useful vectors */
	int prev_size = movingCreaturesAndNpcs.size();
	for (unsigned int i = 0; i < movingCreaturesAndNpcs.size(); i++)
		if (movingCreaturesAndNpcs[i]->isDead())
			movingCreaturesAndNpcs.erase(movingCreaturesAndNpcs.begin() + i);
	if (prev_size != movingCreaturesAndNpcs.size())
	{
		allMovingStuff.clear();
		allMovingStuff.push_back(player);
		for (MovingObject* obj : movingCreaturesAndNpcs)
			allMovingStuff.push_back(obj);
	}

	if (ev->type == ALLEGRO_EVENT_TIMER)
	{
		if (ev->timer.source == StateControl::GetInstance()->GetTimer(0))
		{
			// attack rate control
			if (!player_can_attack)
				attack_cooldown++;
			if (attack_cooldown > AttackRate)
			{ attack_cooldown = 0; player_can_attack = true; }

			// player used portal
			if (switch_pressed &&
				(483 <= player->getFeetX() && player->getFeetX() <= 515) &&
				(123 <= player->getFeetY() && player->getFeetY() <= 156))
			{
				player->setX(700-16);
				player->setY(142-32);
			}
			
			// player wants to chat
			if (al_key_down(&keyState, ALLEGRO_KEY_C) &&
				calculateDistance(player->getX(), player->getY(), steve->getX(), steve->getY()) < 40)
			{
				show_tutorial_dialog_2 = false;

				if (rabbit->isDead())
					show_steve_dialog_2 = true;
				else
					show_steve_dialog_1 = true;

				player_has_talked_to_steve = true;
				player->setWeapon(knife);
				steve->setActiveState(false);
			}
			if (calculateDistance(player->getX(), player->getY(), steve->getX(), steve->getY()) > 60)
			{ show_steve_dialog_1 = false; show_steve_dialog_2 = false; steve->setActiveState(true); }
			
			// player attacks
			if (al_key_down(&keyState, ALLEGRO_KEY_K) && player_can_attack &&
				calculateDistance(player->getX(), player->getY(), rabbit->getX(), rabbit->getY()) < 40 &&
				((player->getDir() != UP && rabbit->getDir() != DOWN) || (player->getDir() != LEFT && rabbit->getDir() != RIGHT) ||
				(player->getDir() != RIGHT && rabbit->getDir() != LEFT) || (player->getDir() != DOWN && rabbit->getDir() != UP)))
			{
				player_can_attack = false;
				rabbit->setHP(rabbit->getHP() - player->getWeapon()->Damage());
				if (rabbit->getHP() <= 0) { rabbit->setDeadState(true); }
			}
			
			// moving player
			updateRunningState();
			updatePlayerPosition();
			player->updateFeetCoords();

			// --- interactive tiles --- //
			// portal
			if ((126 <= player->getFeetX() && player->getFeetX() <= 155) && (130 <= player->getFeetY() && player->getFeetY() <= 155))
			{ switch_pressed = true; }
			else
			{
				if (switch_pressed)
					switch_cooldown++;
				if (switch_cooldown > FPS*4.6)
				{
					switch_cooldown = 0;
					switch_pressed = false;
				}
			}

			// moving npcs and creatures
			for (unsigned int i = 0; i < movingCreaturesAndNpcs.size(); i++)
				if (!movingCreaturesAndNpcs[i]->isDead())
					moveObject(movingCreaturesAndNpcs[i]);

			////////////////////////
			/////  Collisions  /////
			////////////////////////
			// map collisions
			bool colliding = mapCollision(player->getDir(), unaccessible_tiles);
			switch (player->getDir())
			{
			default:
			case UP: { if (colliding) { player->setY(player->getY() + player->getMoveSpeed()); } break; }
			case DOWN: { if (colliding) { player->setY(player->getY() - player->getMoveSpeed()); } break; }
			case LEFT: { if (colliding) { player->setX(player->getX() + player->getMoveSpeed()); } break; }
			case RIGHT: { if (colliding) { player->setX(player->getX() - player->getMoveSpeed()); } break; }
			}
			// moving things collisions
			for (unsigned int i = 0; i < movingCreaturesAndNpcs.size(); i++)
				updateMovingObjectsCollisions(player, movingCreaturesAndNpcs[i]);

			// updating camera
			CameraUpdate(world_map, cameraPosition, player->getX(), player->getY(), 32, 32);
			al_identity_transform(StateControl::GetInstance()->GetCamera());
			al_translate_transform(StateControl::GetInstance()->GetCamera(), -cameraPosition[0], -cameraPosition[1]);
			al_use_transform(StateControl::GetInstance()->GetCamera());
		}

		//////////////////////////////
		/// controlling animations ///
		//////////////////////////////
		// creatures and npcs
		if (ev->timer.source == StateControl::GetInstance()->GetTimer(1))
			for (MovingObject* obj : allMovingStuff)
				if (obj->getType() != playerType)
					updateAnimationFrame(obj);
		// player
		if (ev->timer.source == StateControl::GetInstance()->GetTimer(2))
			updateAnimationFrame(player);

		/* updating drawing vector */
		sort(allMovingStuff.begin(), allMovingStuff.end(), [](MovingObject *a, MovingObject *b) { return a->getY() < b->getY(); });

		return true;
	}

	return false;
}

void TutorialState::Draw()
{
	/* drawing world map */
	for(unsigned int i = 0; i < world_map.size(); i++)
	{
		for(unsigned int j = 0; j < world_map[i].size(); j++)
		{
			if (switch_pressed && world_map[i][j] == 14)
			{ al_draw_bitmap_region(StateControl::GetInstance()->GetTileSet(), 15 * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL); }
			else if (!switch_pressed && world_map[i][j] == 16)
			{ al_draw_bitmap_region(StateControl::GetInstance()->GetTileSet(), 1 * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL); }
			else
			{ al_draw_bitmap_region(StateControl::GetInstance()->GetTileSet(), world_map[i][j] * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL); }
		}
	}

	/* drawing moving things */
	for (unsigned int i = 0; i < allMovingStuff.size(); i++)
	{
		/* bitmaps */
		al_draw_bitmap_region(allMovingStuff[i]->getBitmap(), allMovingStuff[i]->getBitmapSourceX(), allMovingStuff[i]->getBitmapSourceY() * al_get_bitmap_height(allMovingStuff[i]->getBitmap()) / 4, 32, 32, allMovingStuff[i]->getX(), allMovingStuff[i]->getY(), NULL);
		
		/* life bars */
		if (allMovingStuff[i]->getType() == creatureType)
			drawLifeBar(allMovingStuff[i]);
	}

	/* drawing side bar */
	al_draw_bitmap(side_bar, 600+cameraPosition[0], cameraPosition[1], NULL);

	/* drawing dialogs */
	if (show_tutorial_dialog_1) { al_draw_bitmap(tutorial_dialog_1, 300+cameraPosition[0] - al_get_bitmap_width(tutorial_dialog_1)/2, cameraPosition[1] + ScreenHeight/4, NULL); }
	else if (show_tutorial_dialog_2) { al_draw_bitmap(tutorial_dialog_2, 300+cameraPosition[0] - al_get_bitmap_width(tutorial_dialog_2)/2, cameraPosition[1] + ScreenHeight - al_get_bitmap_height(tutorial_dialog_2), NULL); }
	else if (show_steve_dialog_1) { al_draw_bitmap(steve_dialog_1, steve->getX()-85, steve->getY()-al_get_bitmap_height(steve_dialog_1), NULL); }
	else if (show_steve_dialog_2) { al_draw_bitmap(steve_dialog_2, steve->getX()-85, steve->getY()-al_get_bitmap_height(steve_dialog_2), NULL); }

	/*
	// player temp coords
	cout << "Player coords: " << player->getFeetX() << " " << player->getFeetY()
		<< "\t\t" << player->getX() << " " << player->getY() << endl;
	// -----------------
	*/
}

void TutorialState::Terminate()
{
	al_destroy_bitmap(player->getBitmap());
	al_destroy_bitmap(steve->getBitmap());
	al_destroy_bitmap(tutorial_dialog_1);
	al_destroy_bitmap(tutorial_dialog_2);
	al_destroy_bitmap(steve_dialog_1);
	al_destroy_bitmap(steve_dialog_2);
}