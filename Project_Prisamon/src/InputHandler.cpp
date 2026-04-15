#define _CRT_SECURE_NO_WARNINGS
#include "InputHandler.h"
#include "glut.h"
#include <mmsystem.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

// ================= MOUSE CLICK HANDLER =================
void handleMouseClick(int mx, int my) {
	lastClickX = mx;
	lastClickY = my;
	printf("Mouse Clicked - X: %d, Y: %d\n", mx, my);

	if (isFading) {
		return;
	}
	if (lockScreenTimer > 0) {
		lockScreenTimer = 0;
		return;
	}

	if (gameState == 0) {
		if (mx >= 100 && mx <= 450 && my >= 700 && my <= 760) {
			// NEW GAME - reset everything
			partySize = 0;
			currentActivePokemon = 0;

			for (int i = 0; i < 6; i++) {
				partyIDs[i] = -1;
				partyHP[i] = 0;
				partyMaxHP[i] = 0;
				partyLevel[i] = 0;
				partyAttack[i] = 0;
				partyEXP[i] = 0;
			}
			for (int i = 0; i < 30; i++) {
				pcBoxIDs[i] = -1;
				pcBoxHP[i] = 0;
				pcBoxMaxHP[i] = 0;
				pcBoxLevel[i] = 0;
				pcBoxAttack[i] = 0;
				pcBoxEXP[i] = 0;
			}

			playerLevel = 1;
			playerEXP = 0;
			myMaxHP = 120;
			myHP = 120;
			playerAttack = 21;
			potionCount = 3;
			prisaballs = 5;
			coins = 0;
			nodesCleared = 0;
			heroPageVisited = 0;
			isFirstTimeMapTour = 1;
			dragonBalls = 0;
			evolutionStones = 0;
			xpCandies = 0;
			hasSeenWildIntro = 0;
			hasSeenGrindIntro = 0;
			selectedPrisamon = -1;
			for (int i = 0; i < 6; i++) {
				caughtWild[i] = 0;
			}
			gameState = 1;
		}
		else if (mx >= 100 && mx <= 450 && my >= 600 && my <= 660) {
			// CURRENT GAME - load saved state or return to previous
			if (previousGameState == 15 || previousGameState == 16) {
				gameState = previousGameState;
			}
			else {
				loadGameState();
			}
		}
	}
	else if (gameState == 2 && showDialogue) {
		if (++currentDialogueIndex >= totalDialogues) {
			showDialogue = 0;
			triggerTransition(3);
		}
		currentCharCount = 0;
	}
	else if (gameState == 3) {
		if (mx >= 870 && mx <= 1090 && my >= 300 && my <= 360) {
			currentPrisamonIndex = (currentPrisamonIndex + 1) % 3;
		}
		else if (mx >= 440 && mx <= 680 && my >= 315 && my <= 365) {
			selectedPrisamon = currentPrisamonIndex;

			partyIDs[0] = selectedPrisamon;
			partyHP[0] = 120;
			partyMaxHP[0] = 120;
			partyLevel[0] = 1;
			partyAttack[0] = 21;
			partyEXP[0] = 0;
			partySize = 1;
			currentActivePokemon = 0;

			loadActivePokemon();
			saveGameState();
			triggerTransition(4);
			currentCharCount = 0;
		}
	}
	else if (gameState == 4) {
		if (++currentEndDialogueIndex >= totalEndDialogues) {
			triggerTransition(6);
			currentCharCount = 0;
		}
		else {
			currentCharCount = 0;
		}
	}
	else if (gameState == 6) {
		if (++currentPikachuDialogueIndex >= totalPikachuDialogues) {
			if (partySize < 6) {
				partyIDs[partySize] = 3;
				partyHP[partySize] = 120;
				partyMaxHP[partySize] = 120;
				partyLevel[partySize] = 1;
				partyAttack[partySize] = 25;
				partyEXP[partySize] = 0;
				partySize++;
			}
			saveGameState();
			triggerTransition(7);
			heroPageX = 0;
		}
		else {
			currentCharCount = 0;
		}
	}
	else if (gameState == 7) {
		if (!heroPageVisited) {
			if (heroPageX <= -1024) {
				heroPageVisited = 1;
				triggerTransition(8);
			}
		}
		else {
			if (showOakGrindIntro) {
				if (++currentOakGrindIntroIndex >= totalOakGrindIntros) {
					showOakGrindIntro = 0;
				}
				currentCharCount = 0;
				return;
			}

			int relativeX = mx - heroPageX;

			if (relativeX >= 1050 && relativeX <= 1200 && my >= 200 && my <= 400) {
				triggerTransition(19);
			}
			else if (relativeX >= 2100 && relativeX <= 2400 && my >= 450 && my <= 750) {
				triggerTransition(18);
			}
			else if (relativeX >= 2100 && relativeX <= 2400 && my >= 200 && my <= 400) {
				triggerTransition(15);
				if (!hasSeenWildIntro) {
					showOakWildIntro = 1;
					hasSeenWildIntro = 1;
					currentOakWildIntroIndex = 0;
					currentCharCount = 0;
				}
			}
			else if (relativeX >= 1825 && relativeX <= 2100 && my >= 200 && my <= 400) {
				triggerTransition(8);
			}
			else if (relativeX >= 1250 && relativeX <= 1350 && my >= 200 && my <= 400) {
				triggerTransition(26);
			}
			else if (relativeX >= 800 && relativeX <= 950 && my >= 200 && my <= 400) {
				triggerTransition(25);
			}
			else {
				if (mx >= 900) {
					if (panIndex < 9) {
						panIndex++;
						heroPageX = panPositions[panIndex];
					}
				}
				else if (mx <= 100) {
					if (panIndex > 0) {
						panIndex--;
						heroPageX = panPositions[panIndex];
					}
				}
			}
		}
	}
	else if (gameState >= 8 && gameState <= 11) {
		if (mx >= 5 && mx <= 126 && my >= 970 && my <= 1021) {
			triggerTransition(7);
			return;
		}

		if (gameState == 8) {
			if (showOakMapDialogue && isFirstTimeMapTour == 0) {
				if (++currentOakMapDialogueIndex >= totalOakMapDialogues) {
					showOakMapDialogue = 0;
				}
				currentCharCount = 0;
				return;
			}

			if (isFirstTimeMapTour == 0) {
				if (nodesCleared >= 6) {
					triggerTransition(9);
				}
				else {
					if (mx >= 50 && mx <= 974 && my >= 100 && my <= 924) {
						int targetNode = nodesCleared + 1;
						if (targetNode > 6) {
							targetNode = 6;
						}
						for (int i = 0; i < nodesCleared; i++) {
							if (abs(mx - nodeX[i]) <= 30 && abs(my - nodeY[i]) <= 30) {
								targetNode = i + 1;
								break;
							}
						}
						startNodeBattle(targetNode);
					}
				}
			}
			else {
				triggerTransition(9);
			}
		}
		else if (gameState == 9) {
			if (isFirstTimeMapTour) {
				triggerTransition(10);
			}
			else {
				if (mx >= 50 && mx <= 974 && my >= 100 && my <= 924) {
					int targetNode = nodesCleared + 1;
					if (targetNode > 12) {
						targetNode = 12;
					}
					int maxClickable = nodesCleared - 6;
					if (maxClickable > 6) maxClickable = 6;
					for (int i = 0; i < maxClickable; i++) {
						if (abs(mx - nodeX[i]) <= 30 && abs(my - nodeY[i]) <= 30) {
							targetNode = i + 7;
							break;
						}
					}
					startNodeBattle(targetNode);
				}
			}
		}
		else if (gameState == 10) {
			if (isFirstTimeMapTour) {
				triggerTransition(11);
			}
		}
		else if (gameState == 11) {
			if (isFirstTimeMapTour) {
				triggerTransition(8);
				isFirstTimeMapTour = 0;
			}
		}
	}
	else if ((gameState == 12 || gameState == 121) && playerTurn == 1) {

		// --- [CUSTOMIZE] BATTLE PARTY UI HITBOXES (MOUSE) ---
		if (isChoosingAttack == 0) {
			for (int i = 0; i < 6; i++) {
				int slotX = 70 + i * 45;
				int slotY = 205;

				if (mx >= slotX && mx <= slotX + 35 && my >= slotY && my <= slotY + 35) {
					if (i < partySize && partyHP[i] > 0 && i != currentActivePokemon) {
						syncCurrentPokemon();
						currentActivePokemon = i;
						loadActivePokemon();
						sprintf(battleMessage, "Go! Pokemon %d!", i + 1);
						waitingForEnemy = 1;
						delayCounter = 0;
						playerTurn = 0;
						isChoosingAttack = 0;
						return;
					}
				}
			}
		}

		if (isChoosingAttack == 0) {
			if (mx >= 960 && mx <= 1060 && my >= 310 && my <= 350) {
				isChoosingAttack = 1;
			}
			else if (mx >= 1150 && mx <= 1260 && my >= 310 && my <= 350) {
				if (potionCount > 0) {
					myHP += 45;
					if (myHP > myMaxHP) {
						myHP = myMaxHP;
					}
					potionCount--;
					syncCurrentPokemon();
					sprintf(battleMessage, "Used Potion!");
					waitingForEnemy = 1;
					delayCounter = 0;
					playerTurn = 0;
				}
				else {
					sprintf(battleMessage, "No Potion Left!");
				}
			}
			else if (mx >= 960 && mx <= 1060 && my >= 250 && my <= 309) {
				if (gameState == 121) {
					sprintf(battleMessage, "Can't catch Dystopian Prisamon!");
				}
				else if (!isWildEncounter) {
					sprintf(battleMessage, "Can't catch Trainer's Prisamon!");
				}
				else if (caughtWild[currentOpponent] == 1 || isBallThrowing || ballHit) {
					sprintf(battleMessage, "You already caught this Prisamon!");
				}
				else if (strcmp(enemyBattleTypes[currentEnemyIndex], "Dragon") == 0) {
					if (dragonBalls > 0) {
						dragonBalls--;
						caughtWild[currentOpponent] = 1;
						lastCaughtId = currentOpponent;
						
						isBallThrowing = 1;
						ballT = 0.0f;
						ballHit = 0;
					}
					else {
						sprintf(battleMessage, "No Dragon Balls Left!");
					}
				}
				else if (prisaballs > 0) {
					prisaballs--;
					caughtWild[currentOpponent] = 1;
					lastCaughtId = currentOpponent;

					isBallThrowing = 1;
					ballT = 0.0f;
					ballHit = 0;
				}
				else {
					sprintf(battleMessage, "No Prisaballs Left!");
				}
			}
			else if (mx >= 1150 && mx <= 1260 && my >= 250 && my <= 309) {
				if (gameState == 121) {
					sprintf(battleMessage, "You can't run from a Grind Battle!");
				}
				else {
					healAllPokemon();
					sprintf(battleMessage, "Got away safely!");
					if (isWildEncounter) {
						triggerTransition(previousGameState);
					}
					else {
						triggerTransition(8);
					}
				}
			}
		}
		else if (isChoosingAttack == 1) {
			if (mx >= 120 && mx <= 220 && my >= 270 && my <= 310) {
				isChoosingAttack = 0;
				playerAttackMove(0);
			}
			else if (mx >= 450 && mx <= 570 && my >= 270 && my <= 310) {
				isChoosingAttack = 0;
				playerAttackMove(1);
			}
			else if (mx >= 650 && mx <= 750 && my >= 100 && my <= 140) {
				isChoosingAttack = 0;
			}
		}
	}
	else if (gameState == 18) {
		if (mx >= 5 && mx <= 126 && my >= 970 && my <= 1021) {
			triggerTransition(7);
		}
		else if (canGrind) {
			startDystopianGrindBattle();
		}
	}
	else if (gameState == 24) {
		potionCount += 10;
		prisaballs += 5;
		coins += 100;
		xpCandies += 2;
		lastGrindTime = time(NULL);
		canGrind = 0;
		saveGameState();
		triggerTransition(18);
	}
	else if (gameState == 25) {
		if (mx >= 5 && mx <= 126 && my >= 970 && my <= 1021) {
			triggerTransition(7);
			return;
		}
	}
	else if (gameState == 26) {
		if (mx >= 5 && mx <= 126 && my >= 970 && my <= 1021) {
			triggerTransition(7);
			return;
		}
	}
	else if (gameState == 27) {
		if (mx >= 5 && mx <= 126 && my >= 970 && my <= 1021) {
			triggerTransition(battleReturnState);
			return;
		}
	}
	else if (gameState == 13 || gameState == 14 || gameState == 20) {
		if (gameState == 20) {
			if (!hasSeenGrindIntro) {
				hasSeenGrindIntro = 1;
				showOakGrindIntro = 1;
				currentOakGrindIntroIndex = 0;
				currentCharCount = 0;
				heroPageX = -1024;
			}
			triggerTransition(7);
		}
		else {
			if (isWildEncounter) {
				triggerTransition(previousGameState);
			}
			else {
				triggerTransition(7);
			}
		}
	}
	else if ((gameState == 15 || gameState == 16) && !isPlayerMoving) {
		if (showOakWildIntro) {
			if (++currentOakWildIntroIndex >= totalOakWildIntros) {
				showOakWildIntro = 0;
			}
			currentCharCount = 0;
			return;
		}
		if (showOakBlockDialogue) {
			if (++currentOakBlockIndex >= totalOakBlocks) {
				showOakBlockDialogue = 0;
			}
			currentCharCount = 0;
			return;
		}

		if (mx >= 5 && mx <= 126 && my >= 970 && my <= 1021) {
			triggerTransition(7);
			return;
		}
		else if (mx >= 0 && mx <= 400 && my >= 700 && my <= 1024) {
			previousGameState = gameState;
			gameState = 0;
			return;
		}
	}
	else if (gameState == 19) {
		if (mx >= 5 && mx <= 126 && my >= 970 && my <= 1021) {
			triggerTransition(previousGameState);
			return;
		}
	}
}

// ================= KEYBOARD HANDLER =================
void handleKeyPress(unsigned char key) {
	if (key == 'q' || key == 'Q') {
		if (gameState != 26 && gameState != 27) {
			exit(0);
		}
	}

	if (isFading) {
		return;
	}

	if (key == 27) {
		if (gameState == 27) {
			triggerTransition(battleReturnState);
		}
		else if (gameState > 0 && gameState != 12 && gameState != 121) {
			triggerTransition(previousGameState);
		}
	}

	if (gameState == 19) {
		if (key == ' ' || key == '\r') {
			// Used to handle going back, but now we use standard back buttons or ESC
		}
	}

	if (key == ' ' || key == '\r') {
		if (gameState == 0) {
			gameState = 1;
		}
		else if (gameState == 13 || gameState == 14 || gameState == 20) {
			if (gameState == 20) {
				if (!hasSeenGrindIntro) {
					hasSeenGrindIntro = 1;
					showOakGrindIntro = 1;
					currentOakGrindIntroIndex = 0;
					currentCharCount = 0;
					heroPageX = -1024;
				}
				triggerTransition(7);
			}
			else {
				if (isWildEncounter) {
					triggerTransition(previousGameState);
				}
				else {
					triggerTransition(7);
				}
			}
		}
		else if (gameState == 24) {
			potionCount += 10;
			prisaballs += 5;
			coins += 100;
			xpCandies += 2;
			lastGrindTime = time(NULL);
			canGrind = 0;
			saveGameState();
			triggerTransition(18);
		}
	}

	if (key == 's' || key == 'S') {
		if (gameState == 8) {
			triggerTransition(9);
		}
	}

	if ((gameState == 12 || gameState == 121) && playerTurn) {
		if (isChoosingAttack) {
			if (key == '1') {
				isChoosingAttack = 0;
				playerAttackMove(0);
			}
			if (key == '2') {
				isChoosingAttack = 0;
				playerAttackMove(1);
			}
		}
		else {
			if (key == '1') {
				isChoosingAttack = 1;
			}
			else if (key == '2') {
				if (potionCount > 0) {
					myHP += 45;
					if (myHP > myMaxHP) {
						myHP = myMaxHP;
					}
					potionCount--;
					syncCurrentPokemon();
					sprintf(battleMessage, "Used Potion!");
					waitingForEnemy = 1;
					delayCounter = 0;
					playerTurn = 0;
				}
				else {
					sprintf(battleMessage, "No Potion Left!");
				}
			}
			else if (key == '3') {
				if (gameState == 121) {
					sprintf(battleMessage, "You can't run from a Grind Battle!");
				}
				else {
					healAllPokemon();
					sprintf(battleMessage, "Got away safely!");
					if (isWildEncounter) {
						triggerTransition(previousGameState);
					}
					else {
						triggerTransition(8);
					}
				}
			}
			else if (key == '4') {
				if (gameState == 121) {
					sprintf(battleMessage, "Can't catch Dystopian Prisamon!");
				}
				else if (!isWildEncounter) {
					sprintf(battleMessage, "Can't catch Trainer's Prisamon!");
				}
				else if (caughtWild[currentOpponent] == 1 || isBallThrowing || ballHit) {
					sprintf(battleMessage, "You already caught this Prisamon!");
				}
				else if (strcmp(enemyBattleTypes[currentEnemyIndex], "Dragon") == 0) {
					if (dragonBalls > 0) {
						dragonBalls--;
						caughtWild[currentOpponent] = 1;
						lastCaughtId = currentOpponent;
						isBallThrowing = 1;
						ballT = 0.0f;
						ballHit = 0;
					}
					else {
						sprintf(battleMessage, "No Dragon Balls Left!");
					}
				}
				else if (prisaballs > 0) {
					prisaballs--;
					caughtWild[currentOpponent] = 1;
					lastCaughtId = currentOpponent;
					
					isBallThrowing = 1;
					ballT = 0.0f;
					ballHit = 0;
				}
				else {
					sprintf(battleMessage, "No Prisaballs Left!");
				}
			}
		}
	}

	if (gameState == 26 || gameState == 27) {
		// Handled in fixedUpdate
	}
}

// ================= CONTINUOUS INPUT (fixedUpdate) =================
void handleContinuousInput() {
	if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP)) {
		y = 400 - 150;
	}
	if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		x--;
	}
	if (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {
		y--;
	}
	if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		x++;
	}
	if (isKeyPressed(' ')) {
		mciSendString("play ggsong from 0", NULL, 0, NULL);
	}

	if (!canGrind) {
		if (time(NULL) - lastGrindTime >= grindCooldown) {
			canGrind = 1;
		}
	}

	if (gameState == 7 && heroPageVisited) {
		if (showOakGrindIntro) {
			return;
		}

		if (panCooldown == 0) {
			if (isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
				if (panIndex < 9) {
					panIndex++;
					heroPageX = panPositions[panIndex];
					panCooldown = 8;
				}
			}
			if (isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
				if (panIndex > 0) {
					panIndex--;
					heroPageX = panPositions[panIndex];
					panCooldown = 8;
				}
			}
		}
		if (panCooldown > 0) {
			panCooldown--;
		}
	}

	if (gameState == 25) {
		if (bagMenuCooldown == 0) {
			if (isKeyPressed('w') || isKeyPressed('W') || isSpecialKeyPressed(GLUT_KEY_UP)) {
				prisadexSelection--;
				if (prisadexSelection < 0) {
					prisadexSelection = 0;
				}
				if (prisadexSelection < prisadexTopIndex) {
					prisadexTopIndex = prisadexSelection;
				}
				bagMenuCooldown = 6;
			}
			else if (isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {
				prisadexSelection++;
				if (prisadexSelection >= totalPrisamon) {
					prisadexSelection = totalPrisamon - 1;
				}
				if (prisadexSelection >= prisadexTopIndex + 12) {
					prisadexTopIndex = prisadexSelection - 11;
				}
				bagMenuCooldown = 6;
			}
		}
		if (bagMenuCooldown > 0) {
			bagMenuCooldown--;
		}
	}

	if (gameState == 26 || gameState == 27) {
		if (pcSwapState != 2) {
			if (pcMenuCooldown == 0) {
				if (isKeyPressed('w') || isSpecialKeyPressed(GLUT_KEY_UP)) {
					if (pcCursorRow > 0) {
						pcCursorRow--;
					}
					pcMenuCooldown = 8;
				}
				else if (isKeyPressed('s') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {
					if (pcCursorRow < 5) {
						pcCursorRow++;
					}
					pcMenuCooldown = 8;
				}
				else if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
					if (pcCursorArea == 1) {
						if (pcCursorCol > 0) {
							pcCursorCol--;
						}
						else {
							pcCursorArea = 0;
							pcCursorCol = 0;
						}
					}
					pcMenuCooldown = 8;
				}
				else if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
					if (pcCursorArea == 0) {
						pcCursorArea = 1;
						pcCursorCol = 0;
					}
					else {
						if (pcCursorCol < 4) {
							pcCursorCol++;
						}
					}
					pcMenuCooldown = 8;
				}
				else if (isKeyPressed('q') || isKeyPressed('Q')) {
					if (pcSwapState == 0) {
						int hasPoke = 0;
						if (pcCursorArea == 0) {
							if (pcCursorRow < partySize && partyIDs[pcCursorRow] != -1) hasPoke = 1;
						} else {
							int idx = pcCursorRow * 5 + pcCursorCol;
							if (pcBoxIDs[idx] != -1) hasPoke = 1;
						}
						
						if (hasPoke) {
							pcSwapState = 1;
							pcSrcArea = pcCursorArea;
							pcSrcRow = pcCursorRow;
							pcSrcCol = pcCursorCol;
						}
					} else if (pcSwapState == 1) {
						pcSwapState = 0; // cancel
					}
					pcMenuCooldown = 15;
				}
				else if (isKeyPressed('e') || isKeyPressed('E')) {
					if (pcSwapState == 1) {
						if (pcSrcArea == pcCursorArea && pcSrcRow == pcCursorRow && pcSrcCol == pcCursorCol) {
							pcSwapState = 0; // cancel
						} else {
							pcDestArea = pcCursorArea;
							pcDestRow = pcCursorRow;
							pcDestCol = pcCursorCol;
							doPCSwap();
							pcSwapState = 0;
						}
					}
					pcMenuCooldown = 15;
				}
			}
		}
		if (pcMenuCooldown > 0) {
			pcMenuCooldown--;
		}
		if (pcSwapState == 2) {
			if (confirmAnimTicks < 20) {
				confirmAnimTicks++;
			}
		}
	}

	if ((gameState == 15 || gameState == 16) && !isPlayerMoving && !isFading && !showOakWildIntro && !showOakBlockDialogue) {
		int nextX = playerX;
		int nextY = playerY;

		if (isKeyPressed('w') || isKeyPressed('W') || isSpecialKeyPressed(GLUT_KEY_UP)) {
			nextY += 27;
			currentImgPlayer = imgPlayerUp;
		}
		else if (isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {
			nextY -= 27;
			currentImgPlayer = imgPlayerDown;
		}
		else if (isKeyPressed('a') || isKeyPressed('A') || isSpecialKeyPressed(GLUT_KEY_LEFT)) {
			nextX -= 48;
			currentImgPlayer = imgPlayerLeft;
		}
		else if (isKeyPressed('d') || isKeyPressed('D') || isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
			nextX += 48;
			currentImgPlayer = imgPlayerRight;
		}

		if (nextX != playerX || nextY != playerY) {
			if (gameState == 15 && isWalkable15(nextX, nextY) == 0) {
				return;
			}
			if (gameState == 16 && isWalkable16(nextX, nextY) == 0) {
				return;
			}

			targetPlayerX = nextX;
			targetPlayerY = nextY;
			isPlayerMoving = 1;
		}
	}

	if (gameState == 19) {
		if (bagMenuCooldown == 0) {
			if (isKeyPressed('w') || isKeyPressed('W') || isSpecialKeyPressed(GLUT_KEY_UP)) {
				bagSelection--;
				if (bagSelection < 0) {
					bagSelection = 5;
				}
				bagMenuCooldown = 8;
			}
			else if (isKeyPressed('s') || isKeyPressed('S') || isSpecialKeyPressed(GLUT_KEY_DOWN)) {
				bagSelection++;
				if (bagSelection > 5) {
					bagSelection = 0;
				}
				bagMenuCooldown = 8;
			}
		}
		if (bagMenuCooldown > 0) {
			bagMenuCooldown--;
		}
	}
}
