#include "RakosState.h"

void RakosState::InitializeLivingBeings() {
	livingBeings.clear();

	// initializing player
	player = RPG::GetInstance()->GetPlayer();
	player->setX(WorldBlockSize*23);
	player->setY(WorldBlockSize*53);
	livingBeings.push_back(player);


	// initializing npcs
	//Steve = new NPC("Steve", WorldBlockSize*5, WorldBlockSize*14, WorldBlockSize*7, WorldBlockSize*17, explorer_greenPng);
	//livingBeings.push_back(Steve);


	// initializing creatures
	//rabbit = new Rabbit(WorldBlockSize*5, WorldBlockSize*19, WorldBlockSize*7, WorldBlockSize*19);
	//livingBeings.push_back(rabbit);
}

void RakosState::InitializeDialogs() {

}

void RakosState::MoveLivingBeings( ALLEGRO_EVENT *ev ) {
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

void RakosState::UpdateDialogs() {
	
}

void RakosState::DrawDialogs() {
// 	for (TextBox *obj: textBoxes)
// 		obj->Draw();
}


void RakosState::Initialize() {
	// display loading splash screen
	ALLEGRO_BITMAP *loading_background = al_load_bitmap(LoadingGameBackgroundPath);
	if (!loading_background)
		cout << "Error loading loading game bitmap... Proceeding anyway." << endl;
	else
		al_draw_bitmap(loading_background, RPG::GetInstance()->cameraPosition[0], RPG::GetInstance()->cameraPosition[1], NULL);
	al_flip_display();

	// loading map
	LoadMap(RakosMapPath, &worldMapLevel1, &worldMapLevel2);
	worldMapLevels.push_back(&worldMapLevel1);
	worldMapLevels.push_back(&worldMapLevel2);

	RPG::GetInstance()->LoadAccessibleTiles(level1AccessibleTiles, level2AccessibleTiles);
	levelsAccessibleTiles.push_back(&level1AccessibleTiles);
	levelsAccessibleTiles.push_back(&level2AccessibleTiles);

	seaAnimationFrame = 0;

	// initializing side bar
	sideBar = new SideBar(&livingBeings);

	InitializeLivingBeings();
	InitializeDialogs();

	al_destroy_bitmap(loading_background);
}

bool RakosState::Update( ALLEGRO_EVENT *ev ) {
	bool draw = false;
	al_get_keyboard_state(&keyState);

	if (ev->type == ALLEGRO_EVENT_TIMER) {
		MoveLivingBeings(ev);

		if (ev->timer.source == RPG::GetInstance()->GetTimer(_RegularTimer)) {
			player->ControlAttackRate();
			RPG::GetInstance()->CheckIfPlayerAttackedSomething(livingBeings, keyState);
			RPG::GetInstance()->RemoveDeadLivingBeingsFromVector(livingBeings);

// 			UpdateSwitches();
// 			tutorialPortal->CheckIfPlayerPassedThrough(player);
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
//		RPG::GetInstance()->UpdateAnimationsFrame(portals);
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
	
	return draw;
}

void RakosState::Draw() {
	// drawing world map
	DrawMap(worldMapLevel1, worldMapLevel2, seaAnimationFrame);

// 	// drawing switches
// 	for (Switch *obj : switches)
// 		obj->Draw();
// 
// 	// drawing portals
// 	for (Portal *obj : portals)
// 		obj->Draw();

	// drawing living beings
	for (unsigned int i = 0; i < livingBeings.size(); i++)
		livingBeings[i]->Draw();

	// drawing side bar
	sideBar->Draw();

	// drawing dialogs
	DrawDialogs();
}

void RakosState::Terminate() {
	for (LivingBeing *being : livingBeings)
		delete being;
	livingBeings.clear();

// 	for (Switch *obj: switches)
// 		delete obj;
// 	switches.clear();
// 
// 	for (Portal *obj: portals)
// 		delete obj;
// 	portals.clear();
// 
// 	for (TextBox *obj: textBoxes)
// 		delete obj;
// 	textBoxes.clear();
// 
// 	for (SpeechBubble *obj: speechBubbles)
// 		delete obj;
// 	speechBubbles.clear();

	delete sideBar;
}