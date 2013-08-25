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
		player->Move(keyState, worldMapLevel1, worldMapLevel2, level1AccessibleTiles, level2AccessibleTiles);
	for (unsigned int i = 1; i < livingBeings.size(); i++)
		if (!livingBeings[i]->isDead())
			if (ev->timer.source == RPG::GetInstance()->GetTimer(livingBeings[i]->getTimerType()))
				livingBeings[i]->Move();

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
	// loading map
	LoadMap(RakosMapPath, &worldMapLevel1, &worldMapLevel2);
	seaAnimationFrame = 0;

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

	// initializing side bar
	sideBar = new SideBar(&livingBeings);

	InitializeLivingBeings();
	InitializeDialogs();
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
		if (RPG::GetInstance()->Mouse->left_mouse_button_released)
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