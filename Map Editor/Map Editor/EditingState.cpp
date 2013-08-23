#include "EditingState.h"
#include "globalFunctions.h"

void EditingState::Initialize() {
	if (Editor::GetInstance()->creatingNewMap) {
		// displaying warning box
		al_show_native_message_box(Editor::GetInstance()->GetDisplay(), "Rakos: Map Editor", "You chose to create a new map.", "Switch to the console to type the name of the new map and then press <Enter>. Example: \"city\".\n\nYou can now press OK to dismiss this warning and switch to the console.", NULL, ALLEGRO_MESSAGEBOX_WARN);

		// waiting for user input
		cout << "---------------------------------------------------------" << endl;
		cout << "Please type the name of the text file you want to create:" << endl;
		cout << "> ";
		getline(cin, MapBeingEdited);
		cout << endl;
		cout << "Thank you!" << endl;
		cout << "---------------------------------------------------------" << endl;

		// completing file path
		stringstream strstrm;
		strstrm << "res//maps//" << MapBeingEdited << ".txt";
		MapBeingEdited = strstrm.str();

		// creating a new map
		worldMapLevel1.clear();
		for (unsigned int i = 0; i < 3; i++)
			worldMapLevel1.push_back(vector<int> (3, 0));
		worldMapLevel2.clear();
		for (unsigned int i = 0; i < 3; i++)
			worldMapLevel2.push_back(vector<int> (3, 0));

		// loading default tile set
		tileSetPath = DefaultTileSetPath;
		tileSet = al_load_bitmap(tileSetPath.c_str());

		// registering number of tiles on tile set
		numberOfTiles = al_get_bitmap_width(tileSet)/WorldBlockSize;

		// saving map already
		Editor::GetInstance()->SaveMap(MapBeingEdited.c_str(), worldMapLevel1, worldMapLevel2, tileSetPath);
	}
	else {
		// displaying warning box
		al_show_native_message_box(Editor::GetInstance()->GetDisplay(), "Rakos: Map Editor", "You chose to edit an existing map.", "To load the map you want, switch to the console.\nType the name of the text file which contains your map and then press <Enter>. Example: \"city\".\n\nYou can now press OK to dismiss this warning and switch to the console.", NULL, ALLEGRO_MESSAGEBOX_WARN);

		// waiting for user input
		cout << "-------------------------------------------------------" << endl;
		cout << "Please type the name of the text file you want to edit:" << endl;
		cout << "> ";
		getline(cin, MapBeingEdited);
		cout << endl;
		cout << "Thank you!" << endl;
		cout << "-------------------------------------------------------" << endl;

		// completing file path
		stringstream strstrm;
		strstrm << "res//maps//" << MapBeingEdited << ".txt";
		MapBeingEdited = strstrm.str();

		// loading map, tile set and tiles
		LoadMapAndTileSet(strstrm.str().c_str(), &worldMapLevel1, &worldMapLevel2, tileSetPath, &tileSet, numberOfTiles);
	}

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
			CameraUpdate(worldMapLevel1, Editor::GetInstance()->cameraPosition, &cameraCenterX, &cameraCenterY, sideBar->Width());
			al_identity_transform(&Editor::GetInstance()->camera);
			al_translate_transform(&Editor::GetInstance()->camera, -Editor::GetInstance()->cameraPosition[0], -Editor::GetInstance()->cameraPosition[1]);
			al_use_transform(&Editor::GetInstance()->camera);
		}		

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

						// if selected tile is sea, clear tiles from both levels
						if (sideBar->GetTileSet()->GetSelectedTile() == 0) {
							worldMapLevel1[selectedTileY][selectedTileX] = sideBar->GetTileSet()->GetSelectedTile();
							worldMapLevel2[selectedTileY][selectedTileX] = sideBar->GetTileSet()->GetSelectedTile();
						}
						else {
							// if first level tile is set, set an additional tile
							if (worldMapLevel1[selectedTileY][selectedTileX] != 0)
								worldMapLevel2[selectedTileY][selectedTileX] = sideBar->GetTileSet()->GetSelectedTile();
							else
								worldMapLevel1[selectedTileY][selectedTileX] = sideBar->GetTileSet()->GetSelectedTile();
						}
					}
				}
				else
					drawSelectedTile = false;
		}

		// updating side bar
		sideBar->Update(MapBeingEdited, tileSetPath, worldMapLevel1, worldMapLevel2);

		return true;
	}	

	return false;
}

void EditingState::Draw() {
	// drawing world map
	DrawMap(worldMapLevel1, worldMapLevel2, &tileSet);

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
	worldMapLevel1.clear();
	worldMapLevel2.clear();

	// destroying tile set bitmap
	al_destroy_bitmap(tileSet);

	// destroying side bar
	delete sideBar;
}