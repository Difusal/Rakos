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

using namespace std;

/* global variables */
#define ProgramTitle "Rakos"
const unsigned int DefaultScreenWidth = 800;
const unsigned int DefaultScreenHeight = 600;
#define WorldBlockSize 40
#define xCollisionCorrection 15
#define yCollisionCorrection 25
const float FPS = 60.0;
const float drawFPS = 8.0;
const float AttackRate = FPS*0.8;
const float HumansWalkingSpeed = FPS;
const float HumansRunningSpeed = FPS+FPS/3;
const float NPCWalkingSpeed = FPS/2.0;
const float SlowCreaturesSpeed = FPS/2.5;

/* user friendly names */
#define Black al_map_rgb(0, 0, 0)
#define DarkerGray al_map_rgb(32, 32, 32)
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
#define CalibriTTF "res//fonts//calibri.ttf"

/* images */
#define MouseCursorPng "res//images//mouse_cursor.png"
#define MainMenuBackgroundPath "res//images//main_menu_bg.png"
#define LoadingGameBackgroundPath "res//images//loading_game_bg.png"
#define SideBarPath "res//images//side_bar.png"
#define ForbiddenPngPath "res//images//forbidden.png"
#define ToggleFullscreenPngPath "res//images//toggle_fullscreen.png"
#define ToggleMusicPngPath "res//images//toggle_music.png"
#define ToggleSoundsPngPath "res//images//toggle_sounds.png"

/* character sprites */
#define playerPng "res//living beings sprites//noob_yellow.png"
#define explorer_greenPng "res//living beings sprites//explorer_green.png"
#define knight_whitePng "res//living beings sprites//knight_white.png"
#define mage_bluePng "res//living beings sprites//mage_blue.png"
#define warrior_yellowPng "res//living beings sprites//warrior_yellow.png"
#define rabbitPng "res//living beings sprites//rabbit.png"
#define spiderPng "res//living beings sprites//spider.png"

/* sprites */
#define PortalPng "res//sprites//portal.png"
#define SwitchPng "res//sprites//switch.png"
#define SeaPng "res//sprites//sea.png"

/* shield sprites */
#define WoodenShieldPng "res//shield sprites//woodenShield.png"

/* shield thumbnails */
#define NoShieldThumb "res//shield thumbnails//NoShield.png"
#define WoodenShieldThumb "res//shield thumbnails//WoodenShield.png"

/* weapon sprites */
#define SwordsPng "res//weapon sprites//swords.png"
#define WandsPng "res//weapon sprites//wands.png"

/* weapon thumbnails */
#define NoWeaponThumb "res//weapon thumbnails//NoWeapon.png"
#define KnifeThumb "res//weapon thumbnails//Knife.png"
#define WandThumb "res//weapon thumbnails//Wand.png"
#define SwordThumb "res//weapon thumbnails//Sword.png"

/* world maps */
#define TutorialMapPath "res//maps//tutorial.txt"
#define RakosMapPath "res//maps//rakos.txt"