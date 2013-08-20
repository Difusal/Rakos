#include "EditingState.h"
#include "globalFunctions.h"

void EditingState::Initialize() {
	// loading map, tile set and tiles
	LoadMapAndTileSet(MapBeingEdited, worldMap, tileSetPath, &tileSet, numberOfTiles);

	// creating side bar
	sideBar = new SideBar(&tileSet, numberOfTiles);

	// setting camera start position
	cameraCenterX = (ScreenWidth - sideBar->Width())/2.0;
	cameraCenterY = ScreenHeight/2.0;

	// initializing bool variables
	drawSelectedTile = false;
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
		sideBar->Update(tileSetPath, worldMap);

		// checking if new tile was placed on map
		if (Editor::GetInstance()->cameraPosition[0] < Editor::GetInstance()->Mouse->x && Editor::GetInstance()->Mouse->x < sideBar->X() &&
			Editor::GetInstance()->cameraPosition[1] < Editor::GetInstance()->Mouse->y && Editor::GetInstance()->Mouse->y < Editor::GetInstance()->cameraPosition[1] + ScreenHeight) {
				if (sideBar->GetTileSet()->GetSelectedTile() != -1) {
					drawSelectedTile = true;

					selectedTileX = (int)Editor::GetInstance()->Mouse->x/WorldBlockSize;
					selectedTileY = (int)Editor::GetInstance()->Mouse->y/WorldBlockSize;

					// if player presses mouse button, place tile on map
					if (Editor::GetInstance()->Mouse->leftMouseButtonPressed) {
						cout << "Tile set at: " << selectedTileX << " " << selectedTileY << endl;
						worldMap[selectedTileY][selectedTileX] = sideBar->GetTileSet()->GetSelectedTile();
					}
				}
				else
					drawSelectedTile = false;
		}

		return true;
	}	

	return false;
}

void EditingState::Draw() {
	// drawing world map
	DrawMap(worldMap, &tileSet);

	// drawing tile to be placed on map
	if (drawSelectedTile) {
		unsigned int x1 = selectedTileX*WorldBlockSize;
		unsigned int y1 = selectedTileY*WorldBlockSize;
		unsigned int x2 = selectedTileX*WorldBlockSize + WorldBlockSize;
		unsigned int y2 = selectedTileY*WorldBlockSize + WorldBlockSize;

		al_draw_bitmap_region(tileSet, sideBar->GetTileSet()->GetSelectedTile()*WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, x1, y1, ALLEGRO_ALIGN_LEFT);
		al_draw_line(x1, Editor::GetInstance()->cameraPosition[1], x1, Editor::GetInstance()->cameraPosition[1] + ScreenHeight, Yellow, 1.0);
		al_draw_line(x2, Editor::GetInstance()->cameraPosition[1], x2, Editor::GetInstance()->cameraPosition[1] + ScreenHeight, Yellow, 1.0);
		al_draw_line(Editor::GetInstance()->cameraPosition[0], y1, Editor::GetInstance()->cameraPosition[0] + ScreenWidth, y1, Yellow, 1.0);
		al_draw_line(Editor::GetInstance()->cameraPosition[0], y2, Editor::GetInstance()->cameraPosition[0] + ScreenWidth, y2, Yellow, 1.0);
	}

	// drawing side bar
	sideBar->Draw();
}

void EditingState::Terminate() {
	// clearing map vector
	worldMap.clear();

	// destroying tile set bitmap
	al_destroy_bitmap(tileSet);
}