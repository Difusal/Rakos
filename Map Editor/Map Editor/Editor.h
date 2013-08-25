#pragma once

#include "stdIncludes.h"
#include "globalEnums.h"
#include "state.h"
#include "Mouse.h"

class Editor {
public:
	static Editor *GetInstance();
	void ChangeState(EditorState newState);
	void RestartState(EditorState State);

	void StartAllegro5();
	void CreateAllegroDisplay();
	void DisplayLoadingSplashScreen();
	void StartMouseCursor();
	void LoadFonts();
	void CreateTimers();
	void CreateEventQueue();
	void LoadSoundSamples();
	void InitializeVariables();
	void StartTimers();

	void StartControlCycle();
	void Initialize();
	void Update();
	void Draw();
	void FinishControlCycle() { done = true; }
	void Terminate();

	void CameraReset();
	void SaveMap(const char *filename, vector<vector<int> > &map, vector<vector<int> > &mapLevel2, string &tileSetPath);

	ALLEGRO_DISPLAY *GetDisplay() { return display; }
	ALLEGRO_TIMER *GetTimer(TimerType Timer);


	// Public Variables
	unsigned int ScreenWidth;
	unsigned int ScreenHeight;

	bool creatingNewMap;

	MouseCursor *Mouse;

	ALLEGRO_TRANSFORM camera;
	float cameraPosition[2];

	vector<ALLEGRO_FONT*> fonts;
	ALLEGRO_FONT *extraLargeFont;
	ALLEGRO_FONT *largeFont;
	ALLEGRO_FONT *mediumFont;

private:
	static Editor *instance;
	vector<State*> states;
	int state;

	vector<ALLEGRO_TIMER*> timers;
	ALLEGRO_TIMER *timer;
		
	bool done, draw;

	ALLEGRO_DISPLAY *display;

	ALLEGRO_EVENT_QUEUE *eventQueue;
	ALLEGRO_EVENT ev;
};