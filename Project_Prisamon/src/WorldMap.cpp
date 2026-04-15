#define _CRT_SECURE_NO_WARNINGS
#include "WorldMap.h"

int map1Completed = 0;
int map2Completed = 0;
int map3Completed = 0;
int lockScreenTimer = 0;
int mapTourTimer = 0;
int nodesCleared = 0;
int nodeX[6] = { 223, 350, 590, 525, 592, 785 };
int nodeY[6] = { 435, 730, 715, 545, 415, 605 };
int currentImgPlayer;
int playerX = 400;
int playerY = 677;
int targetPlayerX = 400;
int targetPlayerY = 677;
int isPlayerMoving = 0;
char wildNames[6][20] = { "Duskull", "Rattata", "Spearow", "Magikarp", "Pidgeotto", "Scyther" };
int isInsideGrass(int px, int py) {
	if (px >= 130 && px <= 300 && py >= 450 && py <= 580) {
		return 1;
	}
	if (px >= 510 && px <= 750 && py >= 115 && py <= 650) {
		return 1;
	}
	return 0;
}

int isInsideTrees16(int px, int py) {
	if (px >= 450 && px <= 1024 && py >= 223 && py <= 450) {
		return 1;
	}
	if (px >= 0 && px <= 150 && py >= 223 && py <= 800) {
		return 1;
	}
	if (px >= 500 && px <= 800 && py >= 500 && py <= 650) {
		return 1;
	}
	return 0;
}

int isWalkable15(int px, int py) {
	if (px < 0 || px > 1024 - 48) {
		return 0;
	}
	if (py < 100 || py > 900) {
		return 0;
	}
	if (px >= 120 && px <= 1024 && py >= 115 && py <= 230) {
		return 1;
	}
	if (px >= 410 && px <= 510 && py >= 230 && py <= 450) {
		return 1;
	}
	if (px >= 130 && px <= 300 && py >= 450 && py <= 580) {
		return 1;
	}
	if (px >= 250 && px <= 410 && py >= 300 && py <= 750) {
		return 1;
	}
	if (px >= 130 && px <= 750 && py >= 650 && py <= 750) {
		return 1;
	}
	if (px >= 410 && px <= 520 && py >= 450 && py <= 900) {
		return 1;
	}
	if (px >= 510 && px <= 750 && py >= 115 && py <= 650) {
		return 1;
	}
	if (px >= 380 && px <= 410 && py >= 700 && py <= 780) {
		return 1;
	}
	if (px >= 520 && px <= 600 && py >= 700 && py <= 780) {
		return 1;
	}
	return 0;
}

int isWalkable16(int px, int py) {
	if (px < 0 || px > 1024 - 48) {
		return 0;
	}
	if (py < 100 || py > 900) {
		return 0;
	}
	if (px >= 100 && px <= 1024 && py >= 115 && py <= 180) {
		return 1;
	}
	if (px >= 100 && px <= 200 && py >= 150 && py <= 350) {
		return 1;
	}
	if (px >= 150 && px <= 450 && py >= 300 && py <= 380) {
		return 1;
	}
	if (px >= 350 && px <= 480 && py >= 350 && py <= 520) {
		return 1;
	}
	if (px >= 300 && px <= 350 && py >= 380 && py <= 430) {
		return 1;
	}
	if (px >= 450 && px <= 850 && py >= 450 && py <= 550) {
		return 1;
	}
	if (px >= 750 && px <= 880 && py >= 350 && py <= 700) {
		return 1;
	}
	if (px >= 850 && px <= 910 && py >= 400 && py <= 450) {
		return 1;
	}
	if (px >= 750 && px <= 950 && py >= 650 && py <= 750) {
		return 1;
	}
	if (px >= 900 && px <= 1000 && py >= 750 && py <= 900) {
		return 1;
	}
	if (px >= 50 && px <= 100 && py >= 450 && py <= 520) {
		return 1;
	}
	return 0;
}

void updatePlayerMovement() {
	if ((gameState == 15 || gameState == 16) && isPlayerMoving && !isFading) {
		if (playerX < targetPlayerX) {
			playerX += 48;
			currentImgPlayer = imgPlayerRight;
		}
		else if (playerX > targetPlayerX) {
			playerX -= 48;
			currentImgPlayer = imgPlayerLeft;
		}
		else if (playerY < targetPlayerY) {
			playerY += 27;
			currentImgPlayer = imgPlayerUp;
		}
		else if (playerY > targetPlayerY) {
			playerY -= 27;
			currentImgPlayer = imgPlayerDown;
		}

		if (playerX == targetPlayerX && playerY == targetPlayerY) {
			isPlayerMoving = 0;

			if (gameState == 15 && playerY >= 790 && playerX >= 350 && playerX <= 650) {
				if (nodesCleared < 3) {
					showOakBlockDialogue = 1;
					currentOakBlockIndex = 0;
					currentCharCount = 0;
					playerY -= 27;
					targetPlayerY = playerY;
				}
				else {
					triggerTransition(16);
					playerX = 850;
					playerY = 160;
					targetPlayerX = playerX;
					targetPlayerY = playerY;
				}
			}
			else if (gameState == 16 && playerY <= 150 && playerX >= 700 && playerX <= 1000) {
				triggerTransition(15);
				playerX = 480;
				playerY = 750;
				targetPlayerX = playerX;
				targetPlayerY = playerY;
			}
			else if (gameState == 15 && isInsideGrass(playerX, playerY)) {
				if (rand() % 100 < 15) {
					isWildEncounter = 1;
					currentOpponent = rand() % 3;
					startNewBattle();
				}
			}
			else if (gameState == 16 && isInsideTrees16(playerX, playerY)) {
				if (rand() % 100 < 15) {
					isWildEncounter = 1;
					currentOpponent = 3 + (rand() % 3);
					startNewBattle();
				}
			}
		}
	}
}

