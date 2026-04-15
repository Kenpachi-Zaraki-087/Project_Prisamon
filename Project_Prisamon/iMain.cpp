#define _CRT_SECURE_NO_WARNINGS
#include "iGraphics.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#include "Globals.h"
#include "PokemonManager.h"
#include "BattleSystem.h"
#include "WorldMap.h"
#include "ResourceManager.h"
#include "ScreenRenderer.h"
#include "InputHandler.h"

// ================= DRAW =================
void iDraw() {
	if (imagesLoaded == 0) {
		loadAllImages();
		imagesLoaded = 1;
	}
	iClear();

	if (gameState == 0) drawMainMenu();
	else if (gameState == 1) drawLoadingScreen();
	else if (gameState == 2) drawOakDialogue();
	else if (gameState == 3) drawPrisamonSelection();
	else if (gameState == 4 || gameState == 6) drawEndDialogue();
	else if (gameState == 7) drawHeroPage();
	else if (gameState >= 8 && gameState <= 11) drawMapScreen();
	else if (gameState == 12 || gameState == 121) drawBattleScreen();
	else if (gameState == 13) drawWinScreen();
	else if (gameState == 14) drawGameOverScreen();
	else if (gameState == 15 || gameState == 16) drawOpenWorld();
	else if (gameState == 18) drawItemUI();
	else if (gameState == 19) drawBagScreen();
	else if (gameState == 20) drawCaptureScreen();
	else if (gameState == 24) drawRewardScreen();
	else if (gameState == 25) drawPrisadex();
	else if (gameState == 26 || gameState == 27) drawPCBox();

	if (isFading) drawFadeOverlay();
}

// ================= INPUTS =================
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		handleMouseClick(mx, my);
	}
}

void iKeyboard(unsigned char key) {
	handleKeyPress(key);
}

void iMouseMove(int mx, int my) {
	hoverX = mx;
	hoverY = my;
}

void iPassiveMouseMove(int mx, int my) {
	hoverX = mx;
	hoverY = my;
}

void fixedUpdate() {
	handleContinuousInput();
}

int main() {
	srand((unsigned int)time(NULL));

	iSetTimer(150, updateLoadingScreen);
	iSetTimer(40, updateTypewriter);
	iSetTimer(25, updateFade);
	iSetTimer(25, updateAutoPan);
	iSetTimer(50, updateLockScreen);
	iSetTimer(30, updateAutoMapTour);
	iSetTimer(20, updateBattleAnimations);
	iSetTimer(50, updatePlayerMovement);

	mciSendString("open \"C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\music\\game_music-1.mp3\" alias music1", NULL, 0, NULL);
	mciSendString("open \"C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\music\\game_music-2.mp3\" alias music2", NULL, 0, NULL);
	mciSendString("open \"C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\music\\game_music-3.mp3\" alias music3", NULL, 0, NULL);

	iInitialize(1024, 1024, "Project Prisamon");
	iStart();
	return 0;
}
