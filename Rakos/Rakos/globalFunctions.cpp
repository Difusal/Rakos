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
void DrawMap(const vector<vector<int> > &WorldMap, unsigned int SeaAnimationFrame) {
	for(unsigned int i = 0; i < WorldMap.size(); i++) {
		for(unsigned int j = 0; j < WorldMap[i].size(); j++) {
			// drawing sea animation
			al_draw_bitmap_region(RPG::GetInstance()->GetSeaBitmap(), SeaAnimationFrame, SeaAnimationFrame, WorldBlockSize, WorldBlockSize, j*WorldBlockSize, i*WorldBlockSize, NULL);

			// drawing tile
			if (WorldMap[i][j] != 0)
				al_draw_bitmap_region(RPG::GetInstance()->GetTileSet(), WorldMap[i][j] * WorldBlockSize, 10, WorldBlockSize, WorldBlockSize, j * WorldBlockSize, i * WorldBlockSize, NULL);
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

int getLengthOfBiggestSentenceOnVector(vector<string> &vec) {
	unsigned int max = 0;

	for (unsigned int i = 0; i < vec.size(); i++)
		if (vec[i].length() > max)
			max = vec[i].length();

	return max;
}

unsigned int computeLevel(unsigned int Experience) {
	unsigned int level;

	if (Experience < 5)
		level = 1;
	else if (Experience < 10)
		level = 2;
	else if (Experience < 20)
		level = 3;
	else if (Experience < 40)
		level = 4;
	else if (Experience < 60)
		level = 5;
	else if (Experience < 80)
		level = 6;
	else if (Experience < 110)
		level = 7;
	else if (Experience < 140)
		level = 8;
	else if (Experience < 170)
		level = 9;
	else if (Experience < 200)
		level = 10;
	else if (Experience < 240)
		level = 11;
	else if (Experience < 280)
		level = 12;
	else if (Experience < 320)
		level = 13;
	else if (Experience < 360)
		level = 14;
	else if (Experience < 400)
		level = 15;
	else if (Experience < 450)
		level = 16;
	else if (Experience < 500)
		level = 17;
	else
		level = 999;

	return level;
}

unsigned int calculateMaximumExperienceOfLevel(unsigned int Level) {
	switch (Level) {
	default: return 0;
	case 1: return 5;
	case 2: return 10;
	case 3: return 20;
	case 4: return 40;
	case 5: return 60;
	case 6: return 80;
	case 7: return 110;
	case 8: return 140;
	case 9: return 170;
	case 10: return 200;
	case 11: return 240;
	case 12: return 280;
	case 13: return 320;
	case 14: return 360;
	case 15: return 400;
	case 16: return 450;
	case 17: return 500;
	}
}