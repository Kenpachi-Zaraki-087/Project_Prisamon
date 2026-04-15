#pragma once
#include "Globals.h"
#include "PokemonManager.h"
#include "ResourceManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int nodesCleared;

extern int prisaballs;
extern int enemyImages[5];
extern int currentEnemyIndex;
extern char enemyBattleTypes[5][20];
extern int isEnemyGhost;
extern int projColorR;
extern int projColorG;
extern int projColorB;
extern int caughtWild[6];
extern int dystopianEnemyImages[3];
extern int dystopianEnemyBackImages[3];
extern int currentDystopianEnemyIndex;
extern int playerTurn;
extern int waitingForEnemy;
extern int delayCounter;
extern int isChoosingAttack;
extern int enemyLevel;
extern int oppMaxHP;
extern int oppHP;
extern int enemyAttack;
extern int projectileX;
extern int projectileY;
extern int projectileActive;
extern int projectileDirection;
extern char battleMessage[150];
extern int playerHitEffect;
extern int playerBlink;
extern int playerTrembleOffset;
extern int effectCounter;
extern int isBallThrowing;
extern float ballT;
extern float ballX0;
extern float ballY0;
extern float ballX1;
extern float ballY1;
extern float ballX2;
extern float ballY2;
extern int ballHit;
extern int caughtWaitTimer;
extern int currentOpponent;
extern int isWildEncounter;
extern int lastCaughtId;
extern int poisonTimer;

void createEnemy();
void startNewBattle();
void startDystopianGrindBattle();
void startNodeBattle(int node);
void drawHPBar(int x, int y, int current, int max, int width, int height);
void checkLevelUp();
void playerAttackMove(int special);
void enemyAttackMove();
void updateBattleAnimations();
