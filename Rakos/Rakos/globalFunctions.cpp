#include "globalFunctions.h"
#include "RPG.h"

/* generates random numbers */
int randomNumber (int min, int max) {
	max++;

	return ((rand() % (max-min)) + min);
	//return ((rand() % (max+1-min)) + min);
}


// checks if a file exists
bool fileExists (const string &filename) {
	/* trying to open input file stream */
	ifstream infile(filename);

	return infile.good();
}

// loads world maps from text files
void LoadMap(const char *filename, vector<vector<int> > &map) {
	int state = NULL;
	enum LoadState {
		TileSet,
		Map
	};
	
	ifstream openfile(filename);
	if(openfile.is_open()) {
		string line, value;

		while(!openfile.eof()) {
			getline(openfile, line);

			if(line.find("[TileSet]") != string::npos) {
				state = TileSet;
				continue;
			}
			else if (line.find("[Map]") != string::npos) {
				state = Map;
				continue;
			}

			switch(state)
			{
			case TileSet:
				if(line.length() > 0)
					RPG::GetInstance()->SetTileSet(al_load_bitmap(line.c_str()));
				break;
			case Map: 
				stringstream str(line);
				vector<int> tempVector;

				while(!str.eof()) {
					getline(str, value, ' ');
					if(value.length() > 0)
						tempVector.push_back(atoi(value.c_str()));
				}
				map.push_back(tempVector);
				break;
			}
		}
	}
	else {
		al_show_native_message_box(RPG::GetInstance()->GetDisplay(), "Error", "Could not load world map.", "Your game folder must be corrupt.\nQuitting game.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
}

// draws world map to display
void DrawMap(const vector<vector<int> > &worldMap) {
	for(unsigned int i = 0; i < worldMap.size(); i++) {
		for(unsigned int j = 0; j < worldMap[i].size(); j++) {
			al_draw_bitmap_region(RPG::GetInstance()->GetTileSet(), worldMap[i][j] * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL);
			/*
			if (switch_pressed && worldMap[i][j] == 14)
				al_draw_bitmap_region(RPG::GetInstance()->GetTileSet(), 15 * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL);
			else if (!switch_pressed && worldMap[i][j] == 16)
				al_draw_bitmap_region(RPG::GetInstance()->GetTileSet(), 1 * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL);
			else
				al_draw_bitmap_region(RPG::GetInstance()->GetTileSet(), worldMap[i][j] * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL);
				*/
		}
	}
}


/* updates camera position */
void CameraUpdate(vector<vector<int> > &worldMap, float *cameraPosition, float x, float y, int width, int height) {
	cameraPosition[0] = -((ScreenWidth-200) / 2) + (x + width / 2); 
	cameraPosition[1] = -(ScreenHeight / 2) + (y + height / 2);

	if(cameraPosition[0] < 0)
		cameraPosition[0] = 0; 
	if(cameraPosition[1] < 0)
		cameraPosition[1] = 0;
	if(cameraPosition[0] > WorldBlockSize*worldMap[0].size() - (ScreenWidth-200))
		cameraPosition[0] = WorldBlockSize*worldMap[0].size() - (ScreenWidth-200);
	if(cameraPosition[1] > WorldBlockSize*worldMap.size() - ScreenHeight)
		cameraPosition[1] = WorldBlockSize*worldMap.size() - ScreenHeight;
}

/* returns true if bounding boxes are colliding */
bool boxCollision(float x, float y, float ex, float ey, int width, int height) {
	if (x + width - xCollisionCorrection < ex || x > ex + width - xCollisionCorrection ||
		y + height - yCollisionCorrection < ey || y > ey + height - yCollisionCorrection) {
		return false;
	}

	return true;
}

/* calculates distance between 2 points */
float calculateDistance(float p1_x, float p1_y, float p2_x, float p2_y) {
	return sqrt(pow(p2_y-p1_y, 2) + pow(p2_x-p1_x, 2));
}