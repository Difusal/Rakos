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
// Method:    LoadMap
// FullName:  LoadMap
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: const char * filename
// Parameter: vector<vector<int> > & map
// Summary:   reads map from text file and stores it on a vector passed by reference
//************************************
void LoadMap(const char *filename, vector<vector<int> > &map, ALLEGRO_BITMAP *tileSet) {
	int state = NULL;

	// loading state phases
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
			else if (line.find("[Map]") != string::npos) {
				// loading map phase
				state = Map;
				continue;
			}
			////////////////////////
			// EDIT HERE TO ADD AN ELSE IF TO [Creatures]

			switch (state) {
			case TileSet:
				// if loading tile set, assign tile set to the corresponding .png
				if (line.length() > 0)
					tileSet = al_load_bitmap(line.c_str());
				break;
			case Map:
				// if loading map
				stringstream str(line);
				vector<int> tempVector;

				// pushing value read to temporary vector
				while (!str.eof()) {
					getline(str, value, ' ');
					if (value.length() > 0)
						tempVector.push_back(atoi(value.c_str()));
				}

				// push back temporary vector to map vector and read next line
				map.push_back(tempVector);
				break;
			}
		}
	}
	else {
		// if input stream was not opened successfully
		al_show_native_message_box(Editor::GetInstance()->GetDisplay(), "Error", "Could not load world map.", "Your game folder must be corrupt.\nQuitting game.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
}