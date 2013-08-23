#pragma once

#include "stdIncludes.h"

#include "Editor.h"

//************************************
// Method:    fileExists
// FullName:  fileExists
// Access:    public 
// Returns:   bool
// Qualifier:
// Parameter: const string & filename
// Summary:   true if file exists, false otherwise
//************************************
bool fileExists(const string &filename) {
	// trying to open input file stream
	ifstream infile(filename);

	return infile.good();
}

//************************************
// Method:    LoadMapAndTileSet
// FullName:  LoadMapAndTileSet
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const char * filename
// Parameter: vector<vector<int> > & map
// Parameter: ALLEGRO_BITMAP **tileSet
// Summary:   reads map from text file and stores it on a vector passed by reference
//************************************
void LoadMapAndTileSet(const char *filename, vector<vector<int> > *mapLevel1, vector<vector<int> > *mapLevel2, string &tileSetPath, ALLEGRO_BITMAP **tileSet, unsigned int &numberOfTiles) {
	vector<vector<int> > *mapLevelBeingLoaded;

	// clearing vectors
	mapLevel1->clear();
	mapLevel2->clear();

	// loading state phases
	int state = NULL;
	enum LoadState {
		TileSet,
		Map
	};

	// opening input stream
	ifstream openfile(filename);
	if (openfile.is_open()) {
		string line, value;

		// while end of file is not reached
		while (!openfile.eof()) {
			// read a line
			getline(openfile, line);

			// if keyword found, start corresponding loading phase
			if (line.find("[TileSet]") != string::npos) {
				// loading tile set phase
				state = TileSet;
				continue;
			}
			else if (line.find("[MapLevel1]") != string::npos) {
				// loading map phase
				state = Map;
				mapLevelBeingLoaded = mapLevel1;
				continue;
			}
			else if (line.find("[MapLevel2]") != string::npos) {
				// loading map phase
				state = Map;
				mapLevelBeingLoaded = mapLevel2;
				continue;
			}
			////////////////////////
			// EDIT HERE TO ADD AN ELSE IF TO [Creatures]

			switch (state) {
			case TileSet:
				{
					// if loading tile set, assign tile set to the corresponding .png
					if (line.length() > 0) {
						tileSetPath = line;
						*tileSet = al_load_bitmap(line.c_str());
						if (!*tileSet) {
							al_show_native_message_box(Editor::GetInstance()->GetDisplay(), "Error", "Could not load tile set.", "Make sure you include the world tile set on the same folder as the map file and that the map file contains the correct path to the tile set png.\n\nThe program will now quit.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
							exit(-1);
						}

						// registering number of tiles on tile set
						numberOfTiles = al_get_bitmap_width(*tileSet)/WorldBlockSize;
					}
					break;
				}

				// loading map
			case Map:
				{
					stringstream str(line);
					vector<int> tempVector;

					// pushing value read to temporary vector
					while (!str.eof()) {
						getline(str, value, ' ');
						if (value.length() > 0)
							tempVector.push_back(atoi(value.c_str()));
					}

					// push back temporary vector to map vector and read next line
					mapLevelBeingLoaded->push_back(tempVector);

					break;
				}
			}
		}

		cout << "Map loaded." << endl;
	}
	else {
		// if input stream was not opened successfully
		al_show_native_message_box(Editor::GetInstance()->GetDisplay(), "Error", "Could not load world map.", "Make sure to include the file you want to edit in res/maps folder.\nIf the file is already on that folder you probably misspelled the text file name.\n\nPress OK to quit editor.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
}


//************************************
// Method:    DrawMap
// FullName:  DrawMap
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const vector<vector<int> > & WorldMap
// Parameter: ALLEGRO_BITMAP **tileSet
// Summary:   draws world map on display
//************************************
void DrawMap(const vector<vector<int> > &WorldMap, const vector<vector<int> > &WorldMapLevel2, ALLEGRO_BITMAP **tileSet) {
	for(unsigned int i = 0; i < WorldMap.size(); i++) {
		for(unsigned int j = 0; j < WorldMap[i].size(); j++) {
			// drawing sea animation
			al_draw_bitmap_region(*tileSet, 0, 10, WorldBlockSize, WorldBlockSize, j*WorldBlockSize, i*WorldBlockSize, NULL);

			// drawing level 1 tiles
			al_draw_bitmap_region(*tileSet, WorldMap[i][j] * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL);

			// drawing level 2 tiles
			if (WorldMapLevel2[i][j] != 0)
				al_draw_bitmap_region(*tileSet, WorldMapLevel2[i][j] * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL);
		}
	}
}

//************************************
// Method:    CameraUpdate
// FullName:  CameraUpdate
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: vector<vector<int> > & worldMap
// Parameter: float * cameraPosition
// Parameter: double * x
// Parameter: double * y
// Parameter: unsigned int sideBarWidth
// Summary:   updates camera position based on mouse dragging
//************************************
void CameraUpdate(vector<vector<int> > &worldMap, float *cameraPosition, double *x, double *y, unsigned int sideBarWidth) {
	cameraPosition[0] = *x - (ScreenWidth-sideBarWidth)/2.0; 
	cameraPosition[1] = *y - ScreenHeight/2.0;

	if(cameraPosition[0] < 0 || worldMap[0].size() < 18) {
		cameraPosition[0] = 0;
		*x = (ScreenWidth-sideBarWidth)/2.0;
	}
	if(cameraPosition[1] < 0 || worldMap.size() < 15) {
		cameraPosition[1] = 0;
		*y = ScreenHeight/2.0;
	}
	if(cameraPosition[0] > WorldBlockSize*worldMap[0].size() - (ScreenWidth-sideBarWidth)) {
		cameraPosition[0] = WorldBlockSize*worldMap[0].size() - (ScreenWidth-sideBarWidth);
		*x = WorldBlockSize*worldMap[0].size() - (ScreenWidth-sideBarWidth)/2.0;
	}
	if(cameraPosition[1] > WorldBlockSize*worldMap.size() - ScreenHeight) {
		cameraPosition[1] = WorldBlockSize*worldMap.size() - ScreenHeight;
		*y = WorldBlockSize*worldMap.size() - ScreenHeight/2.0;
	}
}