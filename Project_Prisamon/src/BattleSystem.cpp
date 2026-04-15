#define _CRT_SECURE_NO_WARNINGS
#include "BattleSystem.h"
#include <math.h>

int prisaballs = 5;
int enemyImages[5];
int currentEnemyIndex = 0;
char enemyBattleTypes[5][20];
int isEnemyGhost = 0;
int projColorR = 255;
int projColorG = 255;
int projColorB = 255;
int caughtWild[6] = { 0, 0, 0, 0, 0, 0 };
int dystopianEnemyImages[3];
int dystopianEnemyBackImages[3];
int currentDystopianEnemyIndex = 0;
int playerTurn = 1;
int waitingForEnemy = 0;
int delayCounter = 0;
int isChoosingAttack = 0;
int enemyLevel;
int oppMaxHP;
int oppHP;
int enemyAttack;
int projectileX;
int projectileY;
int projectileActive = 0;
int projectileDirection = 1;
char battleMessage[150] = "What will you do?";
int playerHitEffect = 0;
int playerBlink = 0;
int playerTrembleOffset = 0;
int effectCounter = 0;
int isBallThrowing = 0;
float ballT = 0.0f;
float ballX0 = 200, ballY0 = 300;
float ballX1 = 467, ballY1 = 1200;
float ballX2 = 735, ballY2 = 615;
int ballHit = 0;
int caughtWaitTimer = 0;
int currentOpponent = -1;
int isWildEncounter = 0;
int lastCaughtId = -1;
int poisonTimer = 0;

void createEnemy() {
	enemyLevel = playerLevel + rand() % 2;
	oppMaxHP = 95 + enemyLevel * 25;
	oppHP = oppMaxHP;
	enemyAttack = (int)((13 + enemyLevel * 4) * pow(1.25, currentEnemyIndex));
}

void startNewBattle() {
	currentActivePokemon = 0;
	prepBattlePokemon();
	isWildEncounter = 1;
	currentEnemyIndex = 0;
	totalEnemies = 1;
	enemyImages[0] = imgWildPoke[currentOpponent];

	if (currentOpponent == 0) {
		isEnemyGhost = 1;
		strcpy(enemyBattleTypes[0], "Ghost");
	}
	else if (currentOpponent == 1) {
		isEnemyGhost = 0;
		strcpy(enemyBattleTypes[0], "Normal");
	}
	else if (currentOpponent == 2) {
		isEnemyGhost = 0;
		strcpy(enemyBattleTypes[0], "Flying");
	}
	else if (currentOpponent == 3) {
		isEnemyGhost = 0;
		strcpy(enemyBattleTypes[0], "Water");
	}
	else if (currentOpponent == 4) {
		isEnemyGhost = 0;
		strcpy(enemyBattleTypes[0], "Flying");
	}
	else {
		isEnemyGhost = 0;
		strcpy(enemyBattleTypes[0], "Grass");
	}

	createEnemy();
	playerTurn = 1;
	waitingForEnemy = 0;
	projectileActive = 0;
	potionCount = 3;
	isChoosingAttack = 0;
	strcpy(battleMessage, "A Wild Pokemon Appeared!");
	triggerTransition(12);
}

void startDystopianGrindBattle() {
	currentActivePokemon = 0;
	prepBattlePokemon();
	isWildEncounter = 0;
	currentDystopianEnemyIndex = 0;
	totalDystopianEnemies = 3;
	potionCount = 3;
	playerTurn = 1;
	waitingForEnemy = 0;
	projectileActive = 0;
	isChoosingAttack = 0;

	isEnemyGhost = 1;
	strcpy(enemyBattleTypes[0], "Ghost");
	strcpy(enemyBattleTypes[1], "Ghost");
	strcpy(enemyBattleTypes[2], "Ghost");

	createEnemy();
	strcpy(battleMessage, "Dystopian Champion Appears!");
	triggerTransition(121);
}

void startNodeBattle(int node) {
	currentActivePokemon = 0;
	prepBattlePokemon();
	isWildEncounter = 0;
	currentActiveNode = node;
	currentEnemyIndex = 0;
	potionCount = 3;
	playerTurn = 1;
	waitingForEnemy = 0;
	projectileActive = 0;
	isChoosingAttack = 0;

	isEnemyGhost = 0;

	if (node == 1) {
		enemyImages[0] = imgCaterpieFront;
		strcpy(enemyBattleTypes[0], "Normal");
		totalEnemies = 1;
	}
	else if (node == 2) {
		enemyImages[0] = imgNormal[3];
		enemyImages[1] = imgNormal[2];
		strcpy(enemyBattleTypes[0], "Normal");
		strcpy(enemyBattleTypes[1], "Normal");
		totalEnemies = 2;
	}
	else if (node == 3) {
		enemyImages[0] = imgRock[0];
		enemyImages[1] = imgFlying[2];
		strcpy(enemyBattleTypes[0], "Rock");
		strcpy(enemyBattleTypes[1], "Flying");
		totalEnemies = 2;
	}
	else if (node == 4) {
		enemyImages[0] = imgWater[3];
		enemyImages[1] = imgWater[3];
		enemyImages[2] = imgWater[4];
		strcpy(enemyBattleTypes[0], "Water");
		strcpy(enemyBattleTypes[1], "Water");
		strcpy(enemyBattleTypes[2], "Water");
		totalEnemies = 3;
	}
	else if (node == 5) {
		enemyImages[0] = imgElectric[0];
		enemyImages[1] = imgElectric[2];
		enemyImages[2] = imgElectric[1];
		strcpy(enemyBattleTypes[0], "Electric");
		strcpy(enemyBattleTypes[1], "Electric");
		strcpy(enemyBattleTypes[2], "Electric");
		totalEnemies = 3;
	}
	else if (node == 6) {
		enemyImages[0] = imgRock[3];
		enemyImages[1] = imgRock[1];
		enemyImages[2] = imgFlying[0];
		strcpy(enemyBattleTypes[0], "Rock");
		strcpy(enemyBattleTypes[1], "Rock");
		strcpy(enemyBattleTypes[2], "Flying");
		totalEnemies = 3;
	}
	else if (node == 7) {
		enemyImages[0] = imgMap2Normal[0];
		enemyImages[1] = imgMap2Normal[1];
		enemyImages[2] = imgMap2Normal[2];
		strcpy(enemyBattleTypes[0], "Normal");
		strcpy(enemyBattleTypes[1], "Normal");
		strcpy(enemyBattleTypes[2], "Normal");
		totalEnemies = 3;
	}
	else if (node >= 8) {
		enemyImages[0] = imgMap2Psychic[0];
		enemyImages[1] = imgMap2Psychic[1];
		enemyImages[2] = imgMap2Psychic[2];
		strcpy(enemyBattleTypes[0], "Psychic");
		strcpy(enemyBattleTypes[1], "Psychic");
		strcpy(enemyBattleTypes[2], "Psychic");
		totalEnemies = 3;
	}

	if (node == 9) {
		enemyImages[0] = imgNode9[0];
		enemyImages[1] = imgNode9[1];
		enemyImages[2] = imgNode9[2];
		enemyImages[3] = imgNode9[3];
		strcpy(enemyBattleTypes[0], "Flying");
		strcpy(enemyBattleTypes[1], "Grass");
		strcpy(enemyBattleTypes[2], "Flying");
		strcpy(enemyBattleTypes[3], "Grass");
		totalEnemies = 4;
	}
	else if (node == 10) {
		enemyImages[0] = imgNode10[0];
		enemyImages[1] = imgNode10[1];
		enemyImages[2] = imgNode10[2];
		enemyImages[3] = imgNode10[3];
		strcpy(enemyBattleTypes[0], "Grass");
		strcpy(enemyBattleTypes[1], "Grass");
		strcpy(enemyBattleTypes[2], "Fighting");
		strcpy(enemyBattleTypes[3], "Fighting");
		totalEnemies = 4;
	}
	else if (node == 11) {
		enemyImages[0] = imgNode11[0];
		enemyImages[1] = imgNode11[1];
		enemyImages[2] = imgNode11[2];
		strcpy(enemyBattleTypes[0], "Dragon");
		strcpy(enemyBattleTypes[1], "Dragon");
		strcpy(enemyBattleTypes[2], "Dragon");
		totalEnemies = 3;
	}
	else if (node == 12) {
		enemyImages[0] = imgNode12[0];
		enemyImages[1] = imgNode12[1];
		enemyImages[2] = imgNode12[2];
		strcpy(enemyBattleTypes[0], "Flying");
		strcpy(enemyBattleTypes[1], "Dragon");
		strcpy(enemyBattleTypes[2], "Dragon");
		totalEnemies = 3;
	}

	createEnemy();
	strcpy(battleMessage, "Trainer wants to battle!");
	triggerTransition(12);
}

void drawHPBar(int x, int y, int current, int max, int width, int height) {
	iSetColor(100, 100, 100);
	iFilledRectangle(x, y, width, height);
	double ratio = (double)current / max;
	if (ratio < 0) {
		ratio = 0;
	}
	int hpWidth = (int)(width * ratio);
	if (ratio > 0.5) {
		iSetColor(0, 255, 0);
	}
	else if (ratio > 0.25) {
		iSetColor(255, 165, 0);
	}
	else {
		iSetColor(255, 0, 0);
	}
	iFilledRectangle(x, y, hpWidth, height);
}

void checkLevelUp() {
	if (playerEXP >= 100) {
		playerLevel++;
		playerEXP -= 100;
		myMaxHP += 25;
		playerAttack += 5;
		myHP = myMaxHP;
		syncCurrentPokemon();
	}
}

void playerAttackMove(int special) {
	projectileX = 350;
	projectileY = 350;
	projectileDirection = 1;
	projectileActive = 1;

	int pID = partyIDs[currentActivePokemon];

	// --- [CUSTOMIZE] PLAYER PROJECTILE COLORS HERE ---
	if (pID != -1 && pID < 10) {
		int prisadexIdx = partyToPrisadex[pID];
		getTypeColor(prisadexTypes[prisadexIdx], &projColorR, &projColorG, &projColorB);
	}

	// Get player type for multiplier
	const char* playerType = "Normal";
	if (pID != -1 && pID < 10) {
		playerType = prisadexTypes[partyToPrisadex[pID]];
	}
	const char* enemyType = enemyBattleTypes[currentEnemyIndex];
	if (gameState == 121) {
		enemyType = enemyBattleTypes[currentDystopianEnemyIndex];
	}
	float typeMult = getTypeMultiplier(playerType, enemyType);

	int damage;
	if (special) {
		if (rand() % 4 == 0) {
			sprintf(battleMessage, "Special Missed!");
			waitingForEnemy = 1;
			delayCounter = 0;
			playerTurn = 0;
			return;
		}
		damage = (int)((playerAttack * 2 + rand() % 15) * typeMult);
		if (typeMult > 1.0f) sprintf(battleMessage, "Special Attack! It's super effective!");
		else if (typeMult < 1.0f) sprintf(battleMessage, "Special Attack! Not very effective...");
		else sprintf(battleMessage, "Special Attack!");
	}
	else {
		if (isEnemyGhost == 1) {
			damage = 0;
			sprintf(battleMessage, "It doesn't affect the Ghost Prisamon!");
		}
		else {
			damage = (int)((playerAttack + rand() % 8) * typeMult);
			if (typeMult > 1.0f) sprintf(battleMessage, "Normal Attack! It's super effective!");
			else if (typeMult < 1.0f) sprintf(battleMessage, "Normal Attack! Not very effective...");
			else sprintf(battleMessage, "Normal Attack!");
		}
	}
	oppHP -= damage;

	if (oppHP <= 0) {
		oppHP = 0;
		playerEXP += 60;
		checkLevelUp();
		syncCurrentPokemon();

		if (gameState == 121) {
			if (currentDystopianEnemyIndex < totalDystopianEnemies - 1) {
				currentDystopianEnemyIndex++;
				createEnemy();
				sprintf(battleMessage, "Next opponent approaches!");
				playerTurn = 1;
				waitingForEnemy = 0;
				return;
			}
			else {
				healAllPokemon();
				saveGameState();
				gameState = 24;
				return;
			}
		}

		if (currentEnemyIndex < totalEnemies - 1) {
			currentEnemyIndex++;
			createEnemy();
			sprintf(battleMessage, "Opponent sent out next Prisamon!");
			playerTurn = 1;
			waitingForEnemy = 0;
			return;
		}
		else {
			healAllPokemon();
			gameState = 13;
			if (!isWildEncounter) {
				if (currentActiveNode > nodesCleared) {
					nodesCleared = currentActiveNode;
				}
			}
			saveGameState();
			return;
		}
	}
	waitingForEnemy = 1;
	delayCounter = 0;
	playerTurn = 0;
}

void enemyAttackMove() {
	projectileX = 650;
	projectileY = 550;
	projectileDirection = -1;
	projectileActive = 1;

	// --- [CUSTOMIZE] ENEMY PROJECTILE MATCHES ENEMY TYPE ---
	if (gameState == 121) {
		getTypeColor(enemyBattleTypes[currentDystopianEnemyIndex], &projColorR, &projColorG, &projColorB);
	}
	else {
		getTypeColor(enemyBattleTypes[currentEnemyIndex], &projColorR, &projColorG, &projColorB);
	}

	int isPlayerGhost = 0;
	if (partyIDs[currentActivePokemon] == 4) {
		isPlayerGhost = 1;
	}

	// Get enemy type for multiplier
	const char* eType = enemyBattleTypes[currentEnemyIndex];
	if (gameState == 121) {
		eType = enemyBattleTypes[currentDystopianEnemyIndex];
	}
	const char* pType = "Normal";
	int pID = partyIDs[currentActivePokemon];
	if (pID != -1 && pID < 10) {
		pType = prisadexTypes[partyToPrisadex[pID]];
	}
	float eMult = getTypeMultiplier(eType, pType);

	int damage = 0;

	if (rand() % 100 < 70) {
		if (isPlayerGhost == 1) {
			damage = 0;
			sprintf(battleMessage, "Enemy attack phased right through!");
		}
		else {
			damage = (int)((enemyAttack + rand() % 10) * eMult);
			if (eMult > 1.0f) sprintf(battleMessage, "Enemy Attacked! Super effective!");
			else if (eMult < 1.0f) sprintf(battleMessage, "Enemy Attacked! Not very effective...");
			else sprintf(battleMessage, "Enemy Attacked!");
		}
	}
	else {
		damage = (int)((enemyAttack * 1.5 + rand() % 10) * eMult);
		if (rand() % 6 == 0) {
			damage *= 2;
			sprintf(battleMessage, "Enemy CRITICAL Special!");
		}
		else {
			if (eMult > 1.0f) sprintf(battleMessage, "Enemy Special! Super effective!");
			else if (eMult < 1.0f) sprintf(battleMessage, "Enemy Special! Not very effective...");
			else sprintf(battleMessage, "Enemy used a Special Attack!");
		}
	}

	if (currentActiveNode == 9 && poisonTimer == 0) {
		if (rand() % 100 < 25) {
			poisonTimer = 3;
			sprintf(battleMessage, "You have been Poisoned!");
		}
	}

	if (currentActiveNode == 12 && currentEnemyIndex > 0) {
		if (rand() % 100 < 50) {
			damage = myHP;
			sprintf(battleMessage, "Instant Elimination Attack!");
		}
	}

	myHP -= damage;
	playerHitEffect = 1;
	effectCounter = 0;

	if (poisonTimer > 0) {
		int poisonDam = (int)(myMaxHP * 0.02f);
		if (poisonDam < 1) poisonDam = 1;
		myHP -= poisonDam;
		poisonTimer--;
	}

	if (myHP <= 0) {
		myHP = 0;
		syncCurrentPokemon();

		int nextPoke = -1;
		for (int i = 0; i < partySize; i++) {
			if (partyHP[i] > 0) {
				nextPoke = i;
				break;
			}
		}

		if (nextPoke != -1) {
			currentActivePokemon = nextPoke;
			loadActivePokemon();
			sprintf(battleMessage, "Prisamon fainted! Swapped!");
			playerTurn = 1;
			waitingForEnemy = 0;
			poisonTimer = 0;
			return;
		}
		else {
			healAllPokemon();
			gameState = 14;
			waitingForEnemy = 0;
			poisonTimer = 0;
			return;
		}
	}
	playerTurn = 1;
	waitingForEnemy = 0;
}

void updateBattleAnimations() {
	if (gameState != 12 && gameState != 121) {
		return;
	}

	if (projectileActive) {
		projectileX += 30 * projectileDirection;
		projectileY += 20 * projectileDirection;
		if (projectileDirection == 1 && projectileX >= 650) {
			projectileActive = 0;
		}
		else if (projectileDirection == -1 && projectileX <= 350) {
			projectileActive = 0;
		}
	}

	if (waitingForEnemy) {
		delayCounter++;
		if (delayCounter > 30) {
			enemyAttackMove();
			delayCounter = 0;
		}
	}
	if (playerHitEffect) {
		effectCounter++;
		playerBlink = effectCounter % 4;
		if (effectCounter % 2 == 0) {
			playerTrembleOffset = -10;
		}
		else {
			playerTrembleOffset = 10;
		}
		if (effectCounter > 20) {
			playerHitEffect = 0;
			playerBlink = 0;
			playerTrembleOffset = 0;
		}
	}

	if (isBallThrowing) {
		ballT += 0.03f;
		if (ballT >= 1.0f) {
			ballT = 1.0f;
			isBallThrowing = 0;
			ballHit = 1;
			caughtWaitTimer = 30; // delay in ticks before catching
		}
	}
	else if (ballHit) {
		if (caughtWaitTimer > 0) {
			caughtWaitTimer--;
		}
		else {
			ballHit = 0;
			if (partySize < 6) {
				partyIDs[partySize] = currentOpponent + 4;
				partyHP[partySize] = oppMaxHP;
				partyMaxHP[partySize] = oppMaxHP;
				partyLevel[partySize] = enemyLevel;
				partyAttack[partySize] = enemyAttack;
				partyEXP[partySize] = 0;
				partySize++;
			}
			else {
				for (int i = 0; i < 30; i++) {
					if (pcBoxIDs[i] == -1) {
						pcBoxIDs[i] = currentOpponent + 4;
						pcBoxHP[i] = oppMaxHP;
						pcBoxMaxHP[i] = oppMaxHP;
						pcBoxLevel[i] = enemyLevel;
						pcBoxAttack[i] = enemyAttack;
						pcBoxEXP[i] = 0;
						break;
					}
				}
			}
			healAllPokemon();
			saveGameState();
			gameState = 20;
		}
	}
}

