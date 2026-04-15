#pragma once
#include "Globals.h"
#include <string.h>

extern int partyIDs[6];
extern int partyHP[6];
extern int partyMaxHP[6];
extern int partyLevel[6];
extern int partyAttack[6];
extern int partyEXP[6];
extern int partySize;
extern int currentActivePokemon;
extern char activePokeNames[10][20];
extern int partyToPrisadex[10];
extern int pcBoxIDs[30];
extern int pcBoxHP[30];
extern int pcBoxMaxHP[30];
extern int pcBoxLevel[30];
extern int pcBoxAttack[30];
extern int pcBoxEXP[30];
extern int pcCursorArea;
extern int pcCursorRow;
extern int pcCursorCol;
extern int pcMenuCooldown;
extern int pcSwapState;
extern int pcSrcArea;
extern int pcSrcRow;
extern int pcSrcCol;
extern int pcDestArea;
extern int pcDestRow;
extern int pcDestCol;
extern int confirmAnimTicks;
extern int playerLevel;
extern int playerEXP;
extern int myMaxHP;
extern int myHP;
extern int playerAttack;

void syncCurrentPokemon();
void loadActivePokemon();
void prepBattlePokemon();
void healAllPokemon();
void compactParty();
void doPCSwap();
void getTypeColor(const char* type, int* r, int* g, int* b);
void getStrongAgainst(const char* type, char* result);
void getWeakAgainst(const char* type, char* result);
float getTypeMultiplier(const char* attackerType, const char* defenderType);
