#include "FileManager.h"
#include "StateControl.h"

bool file_exists (const string & filename)
{
	/* trying to open input file stream */
	ifstream infile(filename);

	return infile.good();
}

void LoadMap(const char * filename, vector<vector<int> > & map)
{
	enum LoadState { TileSet, Map };
	int state = NULL;

	ifstream openfile(filename);
	if(openfile.is_open())
	{
		string line, value;

		while(!openfile.eof())
		{
			getline(openfile, line);

			if(line.find("[TileSet]") != string::npos)
			{
				state = TileSet;
				continue;
			}
			else if (line.find("[Map]") != string::npos)
			{
				state = Map;
				continue;
			}

			switch(state)
			{
			case TileSet:
				if(line.length() > 0)
					StateControl::GetInstance()->SetTileSet(al_load_bitmap(line.c_str()));
				break;
			case Map: 
				stringstream str(line);
				vector<int> tempVector;

				while(!str.eof())
				{
					getline(str, value, ' ');
					if(value.length() > 0)
						tempVector.push_back(atoi(value.c_str()));
				}
				map.push_back(tempVector);
				break;
			}
		}
	}
	else
	{
		al_show_native_message_box(StateControl::GetInstance()->GetDisplay(), "Error", "Could not load world map.", "Your game folder must be corrupt.\nQuitting game.", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
}