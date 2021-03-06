#include <iostream>
#include "game.h"
#include "LoadMap.h"

using namespace std;

extern struct SGameChar g_sChar;
extern double  g_dElapsedTime;
extern double  g_dBounceTime;
extern unsigned int mapSizeWidth;
extern unsigned int mapSizeHeight;

extern struct teleporter portalPos[26];
extern bool newMap;
extern int *changeHealth;

void teleport_player();
void returnNextPosition(int currentPositionY, int currentPositionX);