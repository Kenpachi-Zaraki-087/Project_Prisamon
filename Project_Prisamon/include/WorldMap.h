#pragma once
#include "Globals.h"
#include "ResourceManager.h"
#include "BattleSystem.h"
#include <stdlib.h>

extern int map1Completed;
extern int map2Completed;
extern int map3Completed;
extern int lockScreenTimer;
extern int mapTourTimer;
extern int nodesCleared;
extern int nodeX[6];
extern int nodeY[6];
extern int currentImgPlayer;
extern int playerX;
extern int playerY;
extern int targetPlayerX;
extern int targetPlayerY;
extern int isPlayerMoving;
extern char wildNames[6][20];

int isInsideGrass(int px, int py);
int isInsideTrees16(int px, int py);
int isWalkable15(int px, int py);
int isWalkable16(int px, int py);
void updatePlayerMovement();
