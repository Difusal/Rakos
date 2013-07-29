#include "globalFunctions.h"
#include "RPG.h"

/* generates random numbers */
int randomNumber (int min, int max) {
	max++;

	return ((rand() % (max-min)) + min);
	//return ((rand() % (max+1-min)) + min);
}


/* checks if a file exists */
bool fileExists (const string &filename) {
	/* trying to open input file stream */
	ifstream infile(filename);

	return infile.good();
}

/* loads world maps from text files */
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
	int x_correction = 15;
	int y_correction = 25;
	if (x + width - x_correction < ex || x > ex + width - x_correction ||
		y + height - y_correction < ey || y > ey + height - y_correction) {
		return false;
	}

	return true;
}

/* calculates distance between 2 points */
float calculateDistance(float p1_x, float p1_y, float p2_x, float p2_y) {
	return sqrt(pow(p2_y-p1_y, 2) + pow(p2_x-p1_x, 2));
}


/* draws living being life bar */
void drawLifeBar(LivingBeing *obj) {
	int bar_width = 40, bar_height = 5;

	int pos_x = obj->getX() + al_get_bitmap_width(obj->getBitmap())/4/2 - bar_width/2;
	int pos_y = obj->getY() - 5;

	float percentage = obj->getHP() * 100.0 / obj->getMaxHP();

	ALLEGRO_COLOR color;
	if (percentage >= 50) { color = Green; }
	else if (percentage >= 25) { color = Yellow; }
	else { color = Red; }

	int hp_width = bar_width * percentage / 100.0;

	al_draw_filled_rectangle(pos_x-1, pos_y-1, pos_x+bar_width+1, pos_y+bar_height+1, Black);
	al_draw_filled_rectangle(pos_x, pos_y, pos_x+hp_width, pos_y+bar_height, color);
}