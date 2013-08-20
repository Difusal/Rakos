#include "EditingState.h"
#include "globalFunctions.h"

void EditingState::Initialize() {
	// loading map, tile set and tiles
	LoadMapAndTileSet(MapBeingEdited, worldMap, &tileSet, numberOfTiles);

	// creating side bar
	sideBar = new SideBar(&tileSet, numberOfTiles);

	// setting camera start position
	cameraCenterX = (ScreenWidth - sideBar->Width())/2.0;
	cameraCenterY = ScreenHeight/2.0;
}

bool EditingState::Update(ALLEGRO_EVENT *ev) {
	if (ev->timer.source == Editor::GetInstance()->GetTimer(_RegularTimer)) {
		// dragging map if dragging is enabled and user actually dragged it
		if (sideBar->DraggingIsEnabled()) {
			// updating new camera center coords
			cameraCenterX -= Editor::GetInstance()->Mouse->xDraggingDisplacement;
			cameraCenterY -= Editor::GetInstance()->Mouse->yDraggingDisplacement;

			// updating camera
			CameraUpdate(worldMap, Editor::GetInstance()->cameraPosition, &cameraCenterX, &cameraCenterY, sideBar->Width());
			al_identity_transform(&Editor::GetInstance()->camera);
			al_translate_transform(&Editor::GetInstance()->camera, -Editor::GetInstance()->cameraPosition[0], -Editor::GetInstance()->cameraPosition[1]);
			al_use_transform(&Editor::GetInstance()->camera);
		}		

		// updating side bar
		sideBar->Update();

		return true;
	}	

	return false;
}

void EditingState::Draw() {
	// drawing world map
	DrawMap(worldMap, &tileSet);

	// drawing side bar
	sideBar->Draw();
}

void EditingState::Terminate() {
	// clearing map vector
	worldMap.clear();

	// destroying tile set bitmap
	al_destroy_bitmap(tileSet);
}