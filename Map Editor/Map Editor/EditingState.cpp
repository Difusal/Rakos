#include "EditingState.h"
#include "globalFunctions.h"

void EditingState::Initialize() {
	// loading tile set and map
	LoadMapAndTileSet(MapBeingEdited, worldMap, &tileSet);
	
	sideBar = new SideBar();

	// setting camera start position
	cameraCenterX = (ScreenWidth - sideBar->Width())/2.0;
	cameraCenterY = ScreenHeight/2.0;
}

bool EditingState::Update(ALLEGRO_EVENT *ev) {
	cameraCenterX -= Editor::GetInstance()->Mouse->xDraggingDisplacement;
	cameraCenterY -= Editor::GetInstance()->Mouse->yDraggingDisplacement;
	
	CameraUpdate(worldMap, Editor::GetInstance()->cameraPosition, &cameraCenterX, &cameraCenterY, sideBar->Width());
	al_identity_transform(&Editor::GetInstance()->camera);
	al_translate_transform(&Editor::GetInstance()->camera, -Editor::GetInstance()->cameraPosition[0], -Editor::GetInstance()->cameraPosition[1]);
	al_use_transform(&Editor::GetInstance()->camera);

	sideBar->Update();

	return false;
}

void EditingState::Draw() {
	// drawing world map
	DrawMap(worldMap, &tileSet);

	sideBar->Draw();
}

void EditingState::Terminate() {
	// clearing map vector
	worldMap.clear();

	// destroying tile set bitmap
	al_destroy_bitmap(tileSet);
}