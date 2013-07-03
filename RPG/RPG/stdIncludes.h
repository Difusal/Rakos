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

/* necessary includes */
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <direct.h>

using namespace std;

/* global variables */
#define GameTitle "Rakos"
#define ScreenWidth 800
#define ScreenHeight 600
#define WorldBlockSize 40
const float FPS = 60.0;
const float drawFPS = 8.0;

const float AttackRate = FPS*0.8;

const float HumansWalkingSpeed = 1.0;
const float HumansRunningSpeed = 1.7;
const float NPCWalkingSpeed = 0.5;
const float SlowCreaturesSpeed = 0.4;

/* defining user-friendly color names */
#define Black al_map_rgb(0, 0, 0)
#define DarkGray al_map_rgb(70, 70, 70)
#define LightGray al_map_rgb(110, 110, 110)
#define DarkBlue al_map_rgb(0, 0, 150)
#define Blue al_map_rgb(0, 0, 255)
#define DarkGreen al_map_rgb(0, 200, 0)
#define Green al_map_rgb(0, 255, 0)
#define LightBlue al_map_rgb(14, 108, 150)
#define DarkRed al_map_rgb(200, 0, 0)
#define Red al_map_rgb(255, 0, 0)
#define Yellow al_map_rgb(255, 255, 0)
#define White al_map_rgb(255, 255, 255)

/* world maps */
#define TutorialWorldMap "res//maps//tutorial.txt"

/* images */
#define SideBar "res//images//side_bar.png"

/* sprites */
#define playerPng "res//sprites//noob_yellow.png"
#define explorer_greenPng "res//sprites//explorer_green.png"
#define knight_whitePng "res//sprites//knight_white.png"
#define sorcerer_bluePng "res//sprites//sorcerer_blue.png"
#define warrior_yellowPng "res//sprites//warrior_yellow.png"
#define rabbitPng "res//sprites//rabbit.png"

/* dialogs */
#define TutorialDialog1 "res//images//tutorial_dialog_1.png"
#define TutorialDialog2 "res//images//tutorial_dialog_2.png"
#define SteveDialog1 "res//images//steve_dialog_1.png"
#define SteveDialog2 "res//images//steve_dialog_2.png"

/* fonts */
#define ConsolaTTF "res//fonts//consola.ttf"

struct Button { int p1_x; int p1_y; int p2_x; int p2_y; };