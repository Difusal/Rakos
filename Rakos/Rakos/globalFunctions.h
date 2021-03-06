#pragma once

#include "stdIncludes.h"
#include "LivingBeing.h"

int randomNumber (int min, int max);

bool fileExists(const string &filename);
void LoadMap(const char *filename, vector<vector<int> > *mapLevel1, vector<vector<int> > *mapLevel2);
void DrawMap(const vector<vector<int> > &WorldMapLevel1, const vector<vector<int> > &WorldMapLevel2, unsigned int SeaAnimationFrame);

void CameraUpdate(vector<vector<int> > &worldMap, float *cameraPosition, float x, float y, int width, int height);
bool boxCollision(float x, float y, float ex, float ey, int width, int height);
float calcDistance(float p1_x, float p1_y, float p2_x, float p2_y);

int getLengthOfBiggestSentenceOnVector(vector<string> &vec);

unsigned int computeLevel(unsigned int Experience);
unsigned int calculateMaximumExperienceOfLevel(unsigned int Level);