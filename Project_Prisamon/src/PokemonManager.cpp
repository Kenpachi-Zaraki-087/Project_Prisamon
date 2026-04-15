#define _CRT_SECURE_NO_WARNINGS
#include "PokemonManager.h"

int partyIDs[6] = { -1, -1, -1, -1, -1, -1 };
int partyHP[6] = { 0 };
int partyMaxHP[6] = { 0 };
int partyLevel[6] = { 0 };
int partyAttack[6] = { 0 };
int partyEXP[6] = { 0 };
int partySize = 0;
int currentActivePokemon = 0;

char activePokeNames[10][20] = {
	"Bulbasaur",
	"Charmander",
	"Squirtle",
	"Pikachu",
	"Duskull",
	"Rattata",
	"Spearow",
	"Magikarp",
	"Pidgeotto",
	"Scyther"
};

int partyToPrisadex[10] = { 0, 3, 6, 19, 29, 15, 17, 26, 13, 33 };

int pcBoxIDs[30];
int pcBoxHP[30];
int pcBoxMaxHP[30];
int pcBoxLevel[30];
int pcBoxAttack[30];
int pcBoxEXP[30];
int pcCursorArea = 0;
int pcCursorRow = 0;
int pcCursorCol = 0;
int pcMenuCooldown = 0;
int pcSwapState = 0;
int pcSrcArea = -1;
int pcSrcRow = -1;
int pcSrcCol = -1;
int pcDestArea = -1;
int pcDestRow = -1;
int pcDestCol = -1;
int confirmAnimTicks = 0;

int playerLevel = 1;
int playerEXP = 0;
int myMaxHP = 120;
int myHP = 120;
int playerAttack = 21;

// ================= PARTY HELPERS =================
void syncCurrentPokemon() {
	if (currentActivePokemon >= 0 && currentActivePokemon < partySize) {
		partyHP[currentActivePokemon] = myHP;
		partyMaxHP[currentActivePokemon] = myMaxHP;
		partyLevel[currentActivePokemon] = playerLevel;
		partyAttack[currentActivePokemon] = playerAttack;
		partyEXP[currentActivePokemon] = playerEXP;
	}
}

void loadActivePokemon() {
	if (currentActivePokemon >= 0 && currentActivePokemon < partySize) {
		myHP = partyHP[currentActivePokemon];
		myMaxHP = partyMaxHP[currentActivePokemon];
		playerLevel = partyLevel[currentActivePokemon];
		playerAttack = partyAttack[currentActivePokemon];
		playerEXP = partyEXP[currentActivePokemon];
	}
}

void prepBattlePokemon() {
	if (partyHP[currentActivePokemon] <= 0) {
		int found = 0;
		for (int i = 0; i < partySize; i++) {
			if (partyHP[i] > 0) {
				currentActivePokemon = i;
				found = 1;
				break;
			}
		}
		if (!found && partySize > 0) {
			partyHP[0] = 1;
			currentActivePokemon = 0;
		}
	}
	loadActivePokemon();
}

void healAllPokemon() {
	for (int i = 0; i < partySize; i++) {
		if (partyMaxHP[i] > 0) {
			partyHP[i] = partyMaxHP[i];
		}
	}
	if (currentActivePokemon >= 0 && currentActivePokemon < partySize) {
		myHP = partyMaxHP[currentActivePokemon];
	}
}

void compactParty() {
	int tempIDs[6];
	int tempHP[6];
	int tempMaxHP[6];
	int tempLvl[6];
	int tempAtk[6];
	int tempExp[6];
	int count = 0;

	for (int i = 0; i < 6; i++) {
		if (partyIDs[i] != -1) {
			tempIDs[count] = partyIDs[i];
			tempHP[count] = partyHP[i];
			tempMaxHP[count] = partyMaxHP[i];
			tempLvl[count] = partyLevel[i];
			tempAtk[count] = partyAttack[i];
			tempExp[count] = partyEXP[i];
			count++;
		}
	}

	for (int i = 0; i < 6; i++) {
		if (i < count) {
			partyIDs[i] = tempIDs[i];
			partyHP[i] = tempHP[i];
			partyMaxHP[i] = tempMaxHP[i];
			partyLevel[i] = tempLvl[i];
			partyAttack[i] = tempAtk[i];
			partyEXP[i] = tempExp[i];
		}
		else {
			partyIDs[i] = -1;
		}
	}
	partySize = count;
	if (currentActivePokemon >= partySize) {
		currentActivePokemon = 0;
	}
}

void doPCSwap() {
	int tID = -1;
	int tHP = 0;
	int tMax = 0;
	int tLvl = 0;
	int tAtk = 0;
	int tExp = 0;

	if (pcSrcArea == 0) {
		tID = partyIDs[pcSrcRow];
		tHP = partyHP[pcSrcRow];
		tMax = partyMaxHP[pcSrcRow];
		tLvl = partyLevel[pcSrcRow];
		tAtk = partyAttack[pcSrcRow];
		tExp = partyEXP[pcSrcRow];
	}
	else {
		int qIdx = pcSrcRow * 5 + pcSrcCol;
		tID = pcBoxIDs[qIdx];
		tHP = pcBoxHP[qIdx];
		tMax = pcBoxMaxHP[qIdx];
		tLvl = pcBoxLevel[qIdx];
		tAtk = pcBoxAttack[qIdx];
		tExp = pcBoxEXP[qIdx];
	}

	if (pcDestArea == 0) {
		if (pcSrcArea == 0) {
			partyIDs[pcSrcRow] = partyIDs[pcDestRow];
			partyHP[pcSrcRow] = partyHP[pcDestRow];
			partyMaxHP[pcSrcRow] = partyMaxHP[pcDestRow];
			partyLevel[pcSrcRow] = partyLevel[pcDestRow];
			partyAttack[pcSrcRow] = partyAttack[pcDestRow];
			partyEXP[pcSrcRow] = partyEXP[pcDestRow];
		}
		else {
			int qIdx = pcSrcRow * 5 + pcSrcCol;
			pcBoxIDs[qIdx] = partyIDs[pcDestRow];
			pcBoxHP[qIdx] = partyHP[pcDestRow];
			pcBoxMaxHP[qIdx] = partyMaxHP[pcDestRow];
			pcBoxLevel[qIdx] = partyLevel[pcDestRow];
			pcBoxAttack[qIdx] = partyAttack[pcDestRow];
			pcBoxEXP[qIdx] = partyEXP[pcDestRow];
		}
	}
	else {
		int qDestIdx = pcDestRow * 5 + pcDestCol;
		if (pcSrcArea == 0) {
			partyIDs[pcSrcRow] = pcBoxIDs[qDestIdx];
			partyHP[pcSrcRow] = pcBoxHP[qDestIdx];
			partyMaxHP[pcSrcRow] = pcBoxMaxHP[qDestIdx];
			partyLevel[pcSrcRow] = pcBoxLevel[qDestIdx];
			partyAttack[pcSrcRow] = pcBoxAttack[qDestIdx];
			partyEXP[pcSrcRow] = pcBoxEXP[qDestIdx];
		}
		else {
			int qSrcIdx = pcSrcRow * 5 + pcSrcCol;
			pcBoxIDs[qSrcIdx] = pcBoxIDs[qDestIdx];
			pcBoxHP[qSrcIdx] = pcBoxHP[qDestIdx];
			pcBoxMaxHP[qSrcIdx] = pcBoxMaxHP[qDestIdx];
			pcBoxLevel[qSrcIdx] = pcBoxLevel[qDestIdx];
			pcBoxAttack[qSrcIdx] = pcBoxAttack[qDestIdx];
			pcBoxEXP[qSrcIdx] = pcBoxEXP[qDestIdx];
		}
	}

	if (pcDestArea == 0) {
		partyIDs[pcDestRow] = tID;
		partyHP[pcDestRow] = tHP;
		partyMaxHP[pcDestRow] = tMax;
		partyLevel[pcDestRow] = tLvl;
		partyAttack[pcDestRow] = tAtk;
		partyEXP[pcDestRow] = tExp;
	}
	else {
		int qIdx = pcDestRow * 5 + pcDestCol;
		pcBoxIDs[qIdx] = tID;
		pcBoxHP[qIdx] = tHP;
		pcBoxMaxHP[qIdx] = tMax;
		pcBoxLevel[qIdx] = tLvl;
		pcBoxAttack[qIdx] = tAtk;
		pcBoxEXP[qIdx] = tExp;
	}

	compactParty();
}

// ================= TYPE COLOR HELPER =================
void getTypeColor(const char* type, int* r, int* g, int* b) {
	if (strcmp(type, "Fire") == 0) {
		*r = 252; *g = 122; *b = 8;
	}
	else if (strcmp(type, "Water") == 0) {
		*r = 102; *g = 178; *b = 255;
	}
	else if (strcmp(type, "Grass") == 0) {
		*r = 0; *g = 153; *b = 76;
	}
	else if (strcmp(type, "Electric") == 0) {
		*r = 255; *g = 255; *b = 0;
	}
	else if (strcmp(type, "Normal") == 0) {
		*r = 160; *g = 160; *b = 160;
	}
	else if (strcmp(type, "Flying") == 0) {
		*r = 135; *g = 206; *b = 235;
	}
	else if (strcmp(type, "Rock") == 0) {
		*r = 160; *g = 140; *b = 100;
	}
	else if (strcmp(type, "Ghost") == 0) {
		*r = 128; *g = 70; *b = 160;
	}
	else if (strcmp(type, "Psychic") == 0) {
		*r = 255; *g = 105; *b = 180;
	}
	else if (strcmp(type, "Fighting") == 0) {
		*r = 192; *g = 48; *b = 40;
	}
	else if (strcmp(type, "Dragon") == 0) {
		*r = 112; *g = 56; *b = 248;
	}
	else {
		*r = 255; *g = 255; *b = 255;
	}
}

// ================= TYPE EFFECTIVENESS =================
void getStrongAgainst(const char* type, char* result) {
	if (strcmp(type, "Fire") == 0)          strcpy(result, "Grass");
	else if (strcmp(type, "Water") == 0)     strcpy(result, "Fire, Rock");
	else if (strcmp(type, "Grass") == 0)     strcpy(result, "Water, Rock");
	else if (strcmp(type, "Electric") == 0)  strcpy(result, "Water, Flying");
	else if (strcmp(type, "Flying") == 0)    strcpy(result, "Grass, Fighting");
	else if (strcmp(type, "Rock") == 0)      strcpy(result, "Fire, Flying");
	else if (strcmp(type, "Ghost") == 0)     strcpy(result, "Ghost, Psychic");
	else if (strcmp(type, "Psychic") == 0)   strcpy(result, "Fighting");
	else if (strcmp(type, "Fighting") == 0)  strcpy(result, "Normal, Rock");
	else if (strcmp(type, "Dragon") == 0)    strcpy(result, "Dragon");
	else if (strcmp(type, "Normal") == 0)    strcpy(result, "None");
	else                                    strcpy(result, "None");
}

void getWeakAgainst(const char* type, char* result) {
	if (strcmp(type, "Fire") == 0)          strcpy(result, "Water, Rock");
	else if (strcmp(type, "Water") == 0)     strcpy(result, "Grass, Electric");
	else if (strcmp(type, "Grass") == 0)     strcpy(result, "Fire, Flying");
	else if (strcmp(type, "Electric") == 0)  strcpy(result, "Rock");
	else if (strcmp(type, "Flying") == 0)    strcpy(result, "Electric, Rock");
	else if (strcmp(type, "Rock") == 0)      strcpy(result, "Water, Grass, Fighting");
	else if (strcmp(type, "Ghost") == 0)     strcpy(result, "Ghost");
	else if (strcmp(type, "Psychic") == 0)   strcpy(result, "Ghost");
	else if (strcmp(type, "Fighting") == 0)  strcpy(result, "Flying, Psychic");
	else if (strcmp(type, "Dragon") == 0)    strcpy(result, "Dragon");
	else if (strcmp(type, "Normal") == 0)    strcpy(result, "Fighting");
	else                                    strcpy(result, "None");
}

float getTypeMultiplier(const char* attackerType, const char* defenderType) {
	char strong[60];
	char weak[60];
	getStrongAgainst(attackerType, strong);
	getWeakAgainst(attackerType, weak);

	// Check if attacker is strong against defender
	if (strstr(strong, defenderType) != NULL) {
		return 1.25f;
	}
	// Check if attacker is weak against defender
	if (strstr(weak, defenderType) != NULL) {
		return 0.75f;
	}
	return 1.0f;
}
