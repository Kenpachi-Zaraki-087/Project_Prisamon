#pragma once
#include "Globals.h"
#include "PokemonManager.h"
#include <windows.h>
#include "glut.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// Forward declarations of iGraphics functions
// NOTE: iGraphics.h may ONLY be #included in iMain.cpp (it defines STB_IMAGE_IMPLEMENTATION)
// Return types here MUST match the actual declarations in iGraphics.h exactly.
unsigned int iLoadImage(char filename[]);
void iSetColor(double r, double g, double b);
void iFilledRectangle(double left, double bottom, double dx, double dy);
void iText(double x, double y, char *str, void* font);
void iShowImage(int x, int y, int width, int height, unsigned int texture);
void iRectangle(double left, double bottom, double dx, double dy);
void iLine(double x1, double y1, double x2, double y2);
void iFilledCircle(double x, double y, double r, int slices);
void iCircle(double x, double y, double r, int slices);
int isKeyPressed(unsigned char key);
int isSpecialKeyPressed(unsigned char key);

// ---- WorldMap variables used by ResourceManager ----
// (WorldMap.h cannot be included here due to circular dependency; externs declared directly)
extern int map1Completed;
extern int map2Completed;
extern int map3Completed;
extern int lockScreenTimer;
extern int mapTourTimer;
extern int nodesCleared;
extern int currentImgPlayer;

// ---- BattleSystem variables used by ResourceManager ----
extern int prisaballs;
extern int caughtWild[6];
extern int dystopianEnemyImages[3];

// ---- ResourceManager-owned image IDs ----
extern int totalLoadingTicks;
extern int heroPageX;
extern int panSpeed;
extern int panPositions[10];
extern int panIndex;
extern int panCooldown;
extern int showDialogue;
extern int currentDialogueIndex;
extern int totalDialogues;
extern int currentCharCount;
extern int imgLoading1;
extern int imgLoading2;
extern int imgLoading3;
extern int imgLoading4;
extern int imgHeroPage;
extern int imgOak;
extern int imgChatbox;
extern int imgMap1;
extern int imgMap2;
extern int imgMap3;
extern int imgMap4;
extern int prisamonPaths[3];
extern int prisamonProfilePaths[3];
extern int imgPikachuProfile;
extern int imgOpenWorldBG;
extern int imgVillage16;
extern int imgBag;
extern int imgItemUI;
extern int imgGrindBattle;
extern int imgPrisadex;
extern int imgTraining;
extern int imgPartyIndex;
extern int imgFire[3];
extern int imgWater[5];
extern int imgGrass[3];
extern int imgFlying[7];
extern int imgElectric[3];
extern int imgRock[4];
extern int imgNormal[4];
extern int imgSmall[10];
extern int imgMap2Normal[3];
extern int imgMap2Psychic[3];
extern int imgNode9[4];
extern int imgNode10[4];
extern int imgNode11[3];
extern int imgNode12[3];
extern int imgDragonBall;
extern int imgCaveBattleground;
extern int imgGrassBattleground;
extern int imgPrisamonBack[3];
extern int imgPikachuBack;
extern int imgCaterpieFront;
extern int imgMyHPBox;
extern int imgOppHPBox;
extern int imgBattleDashboard;
extern int imgPointer;
extern int imgWildPoke[6];
extern int imgWildPokeBack[6];
extern char dialogueArray[5][100];
extern int currentEndDialogueIndex;
extern int totalEndDialogues;
extern char endDialogueArray[4][100];
extern int currentPikachuDialogueIndex;
extern int totalPikachuDialogues;
extern char pikachuDialogueArray[2][100];
extern int showOakMapDialogue;
extern int currentOakMapDialogueIndex;
extern int totalOakMapDialogues;
extern char oakMapDialogueArray[3][100];
extern int hasSeenWildIntro;
extern int showOakWildIntro;
extern int currentOakWildIntroIndex;
extern int totalOakWildIntros;
extern char oakWildIntroArray[3][100];
extern int showOakBlockDialogue;
extern int currentOakBlockIndex;
extern int totalOakBlocks;
extern char oakBlockArray[1][100];
extern int hasSeenGrindIntro;
extern int showOakGrindIntro;
extern int currentOakGrindIntroIndex;
extern int totalOakGrindIntros;
extern char oakGrindIntroArray[2][100];
extern int imgGastly;
extern int imgHaunter;
extern int imgGengar;
extern char currentMusic[20];
extern int imgPokeball1;
extern int imgPlayerUp;
extern int imgPlayerDown;
extern int imgPlayerLeft;
extern int imgPlayerRight;

// ---- Function declarations ----
void triggerTransition(int targetState);
unsigned int safeLoadImage(const char* path);
void loadAllImages();
void updateLoadingScreen();
void updateTypewriter();
void updateFade();
void updateAutoPan();
void updateLockScreen();
void drawLockScreen();
void updateAutoMapTour();
void saveGameState();
void loadGameState();
