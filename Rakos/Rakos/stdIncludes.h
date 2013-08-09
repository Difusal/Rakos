#pragma once

/* allegro includes */
#include "allegro5\allegro.h"
#include "allegro5\allegro_native_dialog.h"
#include "allegro5\allegro_primitives.h"
#include "allegro5\allegro_image.h"
#include "allegro5\allegro_font.h"
#include "allegro5\allegro_ttf.h"
#include "allegro5\allegro_audio.h"
#include "allegro5\allegro_acodec.h"

/* standard includes */
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <fstream>
#include <algorithm>
//#include <direct.h>

using namespace std;

/* global variables */
#define GameTitle "Rakos"
#define ScreenWidth 800
#define ScreenHeight 600
#define WorldBlockSize 40
#define xCollisionCorrection 15
#define yCollisionCorrection 25
const float FPS = 60.0;
const float drawFPS = 8.0;
const float AttackRate = FPS*0.8;
const float HumansWalkingSpeed = FPS;
const float HumansRunningSpeed = FPS*3/2.0;
const float NPCWalkingSpeed = FPS/2.0;
const float SlowCreaturesSpeed = FPS/2.5;

/* user friendly names */
#define Black al_map_rgb(0, 0, 0)
#define DarkGray al_map_rgb(64, 64, 64)
#define Gray al_map_rgb(128, 128, 128)
#define LightGray al_map_rgb(192, 192, 192)
#define DarkBlue al_map_rgb(0, 0, 150)
#define Blue al_map_rgb(0, 0, 255)
#define LightBlue al_map_rgb(14, 108, 150)
#define DarkGreen al_map_rgb(0, 200, 0)
#define Green al_map_rgb(0, 255, 0)
#define DarkRed al_map_rgb(200, 0, 0)
#define Red al_map_rgb(255, 0, 0)
#define Yellow al_map_rgb(255, 255, 0)
#define White al_map_rgb(255, 255, 255)

/* fonts */
#define ConsolaTTF "res//fonts//consola.ttf"

/* images */
#define MouseCursorPng "res//images//mouse_cursor.png"
#define LoadingGameBackgroundPath "res//images//loading_game_bg.png"
#define SideBarPath "res//images//side_bar.png"

/* character sprites */
#define playerPng "res//sprites//living beings//noob_yellow.png"
#define explorer_greenPng "res//sprites//living beings//explorer_green.png"
#define knight_whitePng "res//sprites//living beings//knight_white.png"
#define sorcerer_bluePng "res//sprites//living beings//sorcerer_blue.png"
#define warrior_yellowPng "res//sprites//living beings//warrior_yellow.png"
#define rabbitPng "res//sprites//living beings//rabbit.png"

/* sprites */
#define SwordsPng "res//sprites//swords.png"
#define PortalPng "res//sprites//portal.png"
#define SwitchPng "res//sprites//switch.png"

/* world maps */
#define TutorialWorldMapPath "res//maps//tutorial.txt"

/* dialogs */
#define TutorialDialog1 "res//images//tutorial_dialog_1.png"
#define TutorialDialog2 "res//images//tutorial_dialog_2.png"
#define SteveDialog1 "res//images//steve_dialog_1.png"
#define SteveDialog2 "res//images//steve_dialog_2.png"