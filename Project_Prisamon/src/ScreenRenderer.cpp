#define _CRT_SECURE_NO_WARNINGS
#include "ScreenRenderer.h"
#include "glut.h"
#include <stdio.h>
#include <string.h>

// ================= MAIN MENU (gameState 0) =================
void drawMainMenu() {
  iShowImage(0, 0, 1024, 1024, imgLoading1);

  iSetColor(255, 102, 0);
  iFilledRectangle(100, 670, 350, 60);
  iSetColor(0, 0, 0);
  iText(200, 690, "NEW GAME", GLUT_BITMAP_TIMES_ROMAN_24);

  iSetColor(255, 102, 0);
  iFilledRectangle(100, 570, 350, 60);
  iSetColor(0, 0, 0);
  iText(160, 590, "CURRENT GAME", GLUT_BITMAP_TIMES_ROMAN_24);

  iSetColor(170, 230, 200);
  iText(350, 80, "NOW LOADING... O", GLUT_BITMAP_TIMES_ROMAN_24);
}

// ================= LOADING SCREEN (gameState 1) =================
void drawLoadingScreen() {
  int frames[] = {imgLoading1, imgLoading2, imgLoading3, imgLoading4};
  iShowImage(0, 0, 1024, 1024, frames[currentFrame - 1]);
}

// ================= OAK DIALOGUE (gameState 2) =================
void drawOakDialogue() {
  iShowImage(heroPageX, 0, 2048, 1024, imgHeroPage);
  if (showDialogue) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.75f);
    iFilledRectangle(0, 0, 1024, 1024);
    glDisable(GL_BLEND);

    iShowImage(650, 175, 300, 400, imgOak);
    iShowImage(112, 30, 800, 150, imgChatbox);
    iSetColor(0, 0, 0);
    char buf[100];
    strncpy(buf, dialogueArray[currentDialogueIndex], currentCharCount);
    buf[currentCharCount] = '\0';
    iText(150, 80, buf, GLUT_BITMAP_TIMES_ROMAN_24);
  }
}

// ================= PRISAMON SELECTION (gameState 3) =================
void drawPrisamonSelection() {
  iShowImage(0, 0, 1024, 1024, prisamonPaths[currentPrisamonIndex]);
}

// ================= END DIALOGUE / PIKACHU (gameState 4, 6) =================
void drawEndDialogue() {
  iShowImage(heroPageX, 0, 2048, 1024, imgHeroPage);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(0.0f, 0.0f, 0.0f, 0.25f);
  iFilledRectangle(0, 0, 1024, 1024);
  glDisable(GL_BLEND);

  if (gameState == 4) {
    iShowImage(150, 180, 250, 250, prisamonProfilePaths[selectedPrisamon]);
  } else {
    iShowImage(150, 180, 250, 250, imgPikachuProfile);
  }

  iShowImage(650, 175, 300, 400, imgOak);
  iShowImage(112, 30, 800, 150, imgChatbox);
  iSetColor(0, 0, 0);

  char buf[100];
  if (gameState == 4) {
    strncpy(buf, endDialogueArray[currentEndDialogueIndex], currentCharCount);
  } else {
    strncpy(buf, pikachuDialogueArray[currentPikachuDialogueIndex],
            currentCharCount);
  }
  buf[currentCharCount] = '\0';
  iText(150, 80, buf, GLUT_BITMAP_TIMES_ROMAN_24);
}

// ================= HERO PAGE (gameState 7) =================
void drawHeroPage() {
  iShowImage(heroPageX, 0, 2048, 1024, imgHeroPage);

  if (!heroPageVisited && heroPageX <= -1024) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
    double scL = 506;
    double scR = 726;
    double scB = 30;
    double scT = 230;

    iFilledRectangle(0, scT, 1024, 1024 - scT);
    iFilledRectangle(0, 0, 1024, scB);
    iFilledRectangle(0, scB, scL, scT - scB);
    iFilledRectangle(scR, scB, 1024 - scR, scT - scB);
    glDisable(GL_BLEND);

    iSetColor(255, 255, 255);
    iText(scL, scT + 15, "Click ANYWHERE to proceed!",
          GLUT_BITMAP_HELVETICA_18);
  }

  if (showOakGrindIntro) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
    iFilledRectangle(0, 0, 1024, 1024);
    glDisable(GL_BLEND);

    iShowImage(650, 175, 300, 400, imgOak);
    iShowImage(112, 30, 800, 150, imgChatbox);
    iSetColor(0, 0, 0);

    char buf[100];
    strncpy(buf, oakGrindIntroArray[currentOakGrindIntroIndex],
            currentCharCount);
    buf[currentCharCount] = '\0';
    iText(150, 80, buf, GLUT_BITMAP_TIMES_ROMAN_24);
  }
}

// ================= MAP SCREENS (gameState 8-11) =================
void drawMapScreen() {
  iSetColor(0, 0, 0);
  iFilledRectangle(0, 0, 1024, 1024);
  int mX = 50;
  int mY = 100;
  int mW = 924;
  int mH = 824;

  if (gameState == 8) {
    iShowImage(mX, mY, mW, mH, imgMap1);
    if (isFirstTimeMapTour == 0) {
      for (int i = 0; i < 6; i++) {
        if (nodesCleared == i) {
          glEnable(GL_BLEND);
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
          iFilledCircle(nodeX[i], nodeY[i], 30, 100);
          glDisable(GL_BLEND);
        } else if (nodesCleared > i) {
          iSetColor(0, 200, 0);
          iFilledCircle(nodeX[i], nodeY[i], 30, 100);
          iSetColor(255, 255, 255);
          for (int j = -2; j <= 2; j++) {
            iLine(nodeX[i] - 15, nodeY[i] - 4 + j, nodeX[i] - 7,
                  nodeY[i] - 12 + j);
            iLine(nodeX[i] - 7, nodeY[i] - 12 + j, nodeX[i] + 8,
                  nodeY[i] + 8 + j);
          }
        }
      }
    }

    if (showOakMapDialogue && isFirstTimeMapTour == 0) {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
      iFilledRectangle(0, 0, 1024, 1024);
      glDisable(GL_BLEND);

      iShowImage(650, 175, 300, 400, imgOak);
      iShowImage(112, 30, 800, 150, imgChatbox);
      iSetColor(0, 0, 0);

      char buf[100];
      strncpy(buf, oakMapDialogueArray[currentOakMapDialogueIndex],
              currentCharCount);
      buf[currentCharCount] = '\0';
      iText(150, 80, buf, GLUT_BITMAP_TIMES_ROMAN_24);
    }
  } else if (gameState == 9) {
    iShowImage(mX, mY, mW, mH, imgMap2);
    if (isFirstTimeMapTour == 0) {
      for (int i = 0; i < 6; i++) {
        int checkNode = i + 6;
        if (nodesCleared == checkNode) {
          glEnable(GL_BLEND);
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
          iFilledCircle(nodeX[i], nodeY[i], 30, 100);
          glDisable(GL_BLEND);
        } else if (nodesCleared > checkNode) {
          iSetColor(0, 200, 0);
          iFilledCircle(nodeX[i], nodeY[i], 30, 100);
          iSetColor(255, 255, 255);
          for (int j = -2; j <= 2; j++) {
            iLine(nodeX[i] - 15, nodeY[i] - 4 + j, nodeX[i] - 7,
                  nodeY[i] - 12 + j);
            iLine(nodeX[i] - 7, nodeY[i] - 12 + j, nodeX[i] + 8,
                  nodeY[i] + 8 + j);
          }
        }
      }
    }
  } else if (gameState == 10) {
    iShowImage(mX, mY, mW, mH, imgMap3);
  } else if (gameState == 11) {
    iShowImage(mX, mY, mW, mH, imgMap4);
  }

  if (lockScreenTimer > 0) {
    drawLockScreen();
  }

  iSetColor(50, 50, 50);
  iFilledRectangle(5, 970, 121, 51);
  iSetColor(255, 255, 255);
  iText(40, 987, "BACK", GLUT_BITMAP_HELVETICA_18);
}

// ================= BATTLE SCREEN (gameState 12, 121) =================
void drawBattleScreen() {
  if (gameState == 121) {
    iShowImage(0, 0, 1024, 1024, imgGrindBattle);
  } else {
    if (!isWildEncounter && currentActiveNode >= 7 && currentActiveNode <= 12) {
      iShowImage(0, 0, 1024, 1024, imgCaveBattleground);
    } else {
      iShowImage(0, 0, 1024, 1024, imgGrassBattleground);
    }
  }

  int currentFoeImg = imgWildPoke[0];
  if (gameState == 121) {
    currentFoeImg = dystopianEnemyImages[currentDystopianEnemyIndex];
  } else {
    currentFoeImg = enemyImages[currentEnemyIndex];
  }

  if (!ballHit) {
    iShowImage(610, 490, 250, 250, currentFoeImg);
  }

  if (isBallThrowing) {
    float x = (1 - ballT) * (1 - ballT) * ballX0 +
              2 * (1 - ballT) * ballT * ballX1 + ballT * ballT * ballX2;
    float y = (1 - ballT) * (1 - ballT) * ballY0 +
              2 * (1 - ballT) * ballT * ballY1 + ballT * ballT * ballY2;
    if (strcmp(enemyBattleTypes[currentEnemyIndex], "Dragon") == 0) {
      iShowImage((int)x - 25, (int)y - 25, 50, 50, imgDragonBall);
    } else {
      iShowImage((int)x - 25, (int)y - 25, 50, 50, imgPokeball1);
    }
  } else if (ballHit) {
    if (strcmp(enemyBattleTypes[currentEnemyIndex], "Dragon") == 0) {
      iShowImage((int)ballX2 - 25, (int)ballY2 - 25, 50, 50, imgDragonBall);
    } else {
      iShowImage((int)ballX2 - 25, (int)ballY2 - 25, 50, 50, imgPokeball1);
    }
  }

  if (!(playerHitEffect && playerBlink == 0)) {
    int currentId = partyIDs[currentActivePokemon];
    int backImg = -1;
    if (currentId >= 0 && currentId <= 2) {
      backImg = imgPrisamonBack[currentId];
    } else if (currentId == 3) {
      backImg = imgPikachuBack;
    } else if (currentId >= 4 && currentId <= 9) {
      backImg = imgWildPokeBack[currentId - 4];
    }

    if (backImg != -1) {
      iShowImage(150 + playerTrembleOffset, 235, 300, 300, backImg);
    }
  }

  drawHPBar(50, 950, myHP, myMaxHP, 400, 30);
  drawHPBar(574, 950, oppHP, oppMaxHP, 400, 30);

  iSetColor(18, 18, 224);
  iFilledRectangle(0, 0, 1024, 150);

  iSetColor(255, 255, 255);
  iRectangle(0, 0, 614, 150);
  iRectangle(614, 0, 410, 150);

  if (projectileActive) {
    iSetColor(projColorR, projColorG, projColorB);
    iFilledCircle(projectileX, projectileY, 20, 100);
  }

  iSetColor(255, 255, 255);
  iText(10, 215, "Party:", GLUT_BITMAP_HELVETICA_18);

  // --- [CUSTOMIZE] BATTLE PARTY UI VISUALS (DRAW) ---
  for (int i = 0; i < 6; i++) {
    int slotX = 70 + i * 45;
    int slotY = 205;

    if (i < partySize) {
      if (partyHP[i] > 0) {
        if (i == currentActivePokemon) {
          iSetColor(0, 255, 0);
        } else {
          iSetColor(255, 255, 0);
        }
      } else {
        iSetColor(255, 0, 0);
      }
      iFilledRectangle(slotX, slotY, 35, 35);
      iSetColor(0, 0, 0);
      char slotTxt[5];
      sprintf(slotTxt, "%d", i + 1);
      iText(slotX + 12, slotY + 10, slotTxt, GLUT_BITMAP_HELVETICA_18);
    } else {
      iSetColor(100, 100, 100);
      iFilledRectangle(slotX, slotY, 35, 35);
    }
  }

  if (playerTurn == 1) {
    if (isChoosingAttack == 1) {
      if (hoverX >= 80 && hoverX <= 220 && hoverY >= 50 && hoverY <= 100) {
        iSetColor(255, 255, 0);
      } else {
        iSetColor(255, 255, 255);
      }
      iText(90, 70, "NORMAL", GLUT_BITMAP_HELVETICA_18);

      if (hoverX >= 310 && hoverX <= 450 && hoverY >= 50 && hoverY <= 100) {
        iSetColor(255, 255, 0);
      } else {
        iSetColor(255, 255, 255);
      }
      iText(320, 70, "SPECIAL", GLUT_BITMAP_HELVETICA_18);
    } else {
      iSetColor(255, 255, 255);
      iText(90, 120, battleMessage, GLUT_BITMAP_TIMES_ROMAN_24);
    }

    if (hoverX >= 650 && hoverX <= 750 && hoverY >= 100 && hoverY <= 140) {
      iSetColor(255, 255, 0);
    } else {
      iSetColor(255, 255, 255);
    }
    iText(665, 120, "FIGHT", GLUT_BITMAP_HELVETICA_18);

    if (isChoosingAttack == 0 && hoverX >= 770 && hoverX <= 880 &&
        hoverY >= 100 && hoverY <= 140) {
      iSetColor(255, 255, 0);
    } else {
      iSetColor(255, 255, 255);
    }
    iText(780, 120, "POTION", GLUT_BITMAP_HELVETICA_18);

    if (isChoosingAttack == 0 && hoverX >= 650 && hoverX <= 750 &&
        hoverY >= 40 && hoverY <= 90) {
      iSetColor(255, 255, 0);
    } else {
      iSetColor(255, 255, 255);
    }
    iText(665, 60, "CATCH", GLUT_BITMAP_HELVETICA_18);

    if (isChoosingAttack == 0 && hoverX >= 770 && hoverX <= 880 &&
        hoverY >= 40 && hoverY <= 90) {
      iSetColor(255, 255, 0);
    } else {
      iSetColor(255, 255, 255);
    }
    iText(780, 60, "RUN", GLUT_BITMAP_HELVETICA_18);
  }

  if (gameState == 121) {
    char opponentText[50];
    sprintf(opponentText, "Opponent: %d / %d", currentDystopianEnemyIndex + 1,
            totalDystopianEnemies);
    iSetColor(255, 255, 100);
    iText(450, 120, opponentText, GLUT_BITMAP_HELVETICA_18);
  }
}

// ================= WIN SCREEN (gameState 13) =================
void drawWinScreen() {
  iSetColor(0, 0, 0);
  iFilledRectangle(0, 0, 1024, 1024);
  iSetColor(0, 255, 0);
  iText(420, 550, "YOU WIN!", GLUT_BITMAP_TIMES_ROMAN_24);
  iSetColor(255, 255, 255);
  iText(350, 480, "Press SPACE or Click ANYWHERE to continue",
        GLUT_BITMAP_HELVETICA_18);
}

// ================= GAME OVER (gameState 14) =================
void drawGameOverScreen() {
  iSetColor(0, 0, 0);
  iFilledRectangle(0, 0, 1024, 1024);
  iSetColor(255, 0, 0);
  iText(420, 550, "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);
  iSetColor(255, 255, 255);
  iText(350, 480, "Press SPACE or Click ANYWHERE to continue",
        GLUT_BITMAP_HELVETICA_18);
}

// ================= OPEN WORLD (gameState 15, 16) =================
void drawOpenWorld() {
  if (gameState == 15) {
    iShowImage(0, 102, 1024, 820, imgOpenWorldBG);
  } else {
    iShowImage(0, 102, 1024, 820, imgVillage16);
  }

  iShowImage(playerX, playerY, playerWidth, playerHeight, currentImgPlayer);
  iSetColor(50, 50, 50);
  iFilledRectangle(5, 970, 121, 51);
  iSetColor(255, 255, 255);
  iText(40, 987, "BACK", GLUT_BITMAP_HELVETICA_18);

  if (showOakWildIntro || showOakBlockDialogue) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
    iFilledRectangle(0, 0, 1024, 1024);
    glDisable(GL_BLEND);

    iShowImage(650, 175, 300, 400, imgOak);
    iShowImage(112, 30, 800, 150, imgChatbox);
    iSetColor(0, 0, 0);

    char buf[100];
    if (showOakWildIntro) {
      strncpy(buf, oakWildIntroArray[currentOakWildIntroIndex],
              currentCharCount);
    } else {
      strncpy(buf, oakBlockArray[currentOakBlockIndex], currentCharCount);
    }

    buf[currentCharCount] = '\0';
    iText(150, 80, buf, GLUT_BITMAP_TIMES_ROMAN_24);
  }
}

// ================= ITEM UI (gameState 18) =================
void drawItemUI() {
  iShowImage(0, 0, 1024, 1024, imgItemUI);
  iSetColor(50, 50, 50);
  iFilledRectangle(5, 970, 121, 51);
  iSetColor(255, 255, 255);
  iText(40, 987, "BACK", GLUT_BITMAP_HELVETICA_18);
}

// ================= BAG SCREEN (gameState 19) =================
void drawBagScreen() {
  iShowImage(0, 0, 1024, 1024, imgBag);

  int boxX = 485;
  int boxW = 500;
  int boxH = 80;
  int boxYArray[6] = {855, 755, 655, 555, 455, 355};
  iSetColor(0, 0, 0);

  int currentY = boxYArray[bagSelection];
  for (int w = 0; w < 5; w++) {
    iRectangle(boxX - w, currentY - w, boxW + (w * 2), boxH + (w * 2));
  }

  for (int i = 0; i < 6; i++) {
    int qty = 0;
    if (i == 0) {
      qty = potionCount;
    } else if (i == 1) {
      qty = coins;
    } else if (i == 2) {
      qty = prisaballs;
    } else if (i == 3) {
      qty = evolutionStones;
    } else if (i == 4) {
      qty = xpCandies;
    } else if (i == 5) {
      qty = dragonBalls;
    }

    char qtyText[20];
    sprintf(qtyText, "x %d", qty);
    iSetColor(0, 0, 0);

    int textY = boxYArray[i] + 25;
    iText(boxX + boxW - 80, textY, qtyText, GLUT_BITMAP_TIMES_ROMAN_24);
  }

  iSetColor(0, 0, 0);
  iText(60, 300, itemDescLine1[bagSelection], GLUT_BITMAP_TIMES_ROMAN_24);
  iText(60, 270, itemDescLine2[bagSelection], GLUT_BITMAP_TIMES_ROMAN_24);

  iSetColor(50, 50, 50);
  iFilledRectangle(5, 970, 121, 51);
  iSetColor(255, 255, 255);
  iText(40, 987, "BACK", GLUT_BITMAP_HELVETICA_18);
}

// ================= CAPTURE SCREEN (gameState 20) =================
void drawCaptureScreen() {
  iSetColor(0, 0, 0);
  iFilledRectangle(0, 0, 1024, 1024);
  iSetColor(255, 255, 255);

  char capMsg[100];
  if (lastCaughtId >= 0 && lastCaughtId < 6) {
    sprintf(capMsg, "Congratulations you captured %s!",
            wildNames[lastCaughtId]);
  } else {
    sprintf(capMsg, "Congratulations you captured a new Prisamon!");
  }

  iText(320, 550, capMsg, GLUT_BITMAP_TIMES_ROMAN_24);
  iText(350, 480, "Press SPACE or Click ANYWHERE to continue",
        GLUT_BITMAP_HELVETICA_18);
}

// ================= REWARD SCREEN (gameState 24) =================
void drawRewardScreen() {
  iSetColor(0, 0, 0);
  iFilledRectangle(0, 0, 1024, 1024);
  iSetColor(255, 255, 255);
  iText(200, 500, "REWARD: 10X Potion, 5X Prisaball, 100X coin, 2X XpCandy",
        GLUT_BITMAP_HELVETICA_18);
}

// ================= PRISADEX (gameState 25) =================
void drawPrisadex() {
  iSetColor(0, 0, 0);
  iFilledRectangle(0, 0, 1024, 1024);
  iShowImage(0, 112, 1024, 800, imgPrisadex);

  int startY = 820;
  int listX = 640;
  int ySpacing = 55;

  for (int i = 0; i < 12; i++) {
    int currentIndex = prisadexTopIndex + i;

    if (currentIndex >= totalPrisamon) {
      break;
    }

    if (currentIndex == prisadexSelection) {
      iSetColor(0, 0, 0);
      iRectangle(listX - 5, startY - (i * ySpacing) - 5, 320, 35);
    }

    char rowText[100];
    sprintf(rowText, "%03d-   %s", currentIndex + 1,
            prisadexNames[currentIndex]);

    iSetColor(0, 0, 0);
    iText(listX, startY - (i * ySpacing), rowText, GLUT_BITMAP_TIMES_ROMAN_24);
  }

  int profileImg = -1;
  if (prisadexSelection >= 0 && prisadexSelection <= 2) {
    profileImg = imgGrass[prisadexSelection];
  } else if (prisadexSelection >= 3 && prisadexSelection <= 5) {
    profileImg = imgFire[prisadexSelection - 3];
  } else if (prisadexSelection >= 6 && prisadexSelection <= 8) {
    profileImg = imgWater[prisadexSelection - 6];
  } else if (prisadexSelection >= 9 && prisadexSelection <= 10) {
    profileImg = imgNormal[prisadexSelection - 9];
  } else if (prisadexSelection == 11) {
    profileImg = imgFlying[1];
  } else if (prisadexSelection >= 12 && prisadexSelection <= 14) {
    profileImg = imgFlying[prisadexSelection - 9];
  } else if (prisadexSelection == 15) {
    profileImg = imgNormal[3];
  } else if (prisadexSelection == 16) {
    profileImg = imgNormal[2];
  } else if (prisadexSelection >= 17 && prisadexSelection <= 18) {
    profileImg = imgFlying[prisadexSelection - 11];
  } else if (prisadexSelection == 19) {
    profileImg = imgElectric[1];
  } else if (prisadexSelection == 20) {
    profileImg = imgElectric[0];
  } else if (prisadexSelection == 21) {
    profileImg = imgElectric[2];
  } else if (prisadexSelection >= 22 && prisadexSelection <= 25) {
    profileImg = imgRock[prisadexSelection - 22];
  } else if (prisadexSelection == 26) {
    profileImg = imgWater[3];
  } else if (prisadexSelection == 27) {
    profileImg = imgWater[4];
  } else if (prisadexSelection == 28) {
    profileImg = imgFlying[0];
  } else if (prisadexSelection >= 29 && prisadexSelection <= 32) {
    if (prisadexSelection == 29) {
      profileImg = imgWildPoke[0];
    } else {
      profileImg = dystopianEnemyImages[prisadexSelection - 30];
    }
  } else if (prisadexSelection == 33) {
    profileImg = imgWildPoke[5]; // Scyther
  } else if (prisadexSelection >= 34 && prisadexSelection <= 36) {
    profileImg = imgMap2Normal[prisadexSelection - 34];
  } else if (prisadexSelection >= 37 && prisadexSelection <= 39) {
    profileImg = imgMap2Psychic[prisadexSelection - 37];
  } else if (prisadexSelection >= 40 && prisadexSelection <= 43) {
    profileImg = imgNode9[prisadexSelection - 40];
  } else if (prisadexSelection >= 44 && prisadexSelection <= 47) {
    profileImg = imgNode10[prisadexSelection - 44];
  } else if (prisadexSelection >= 48 && prisadexSelection <= 50) {
    profileImg = imgNode11[prisadexSelection - 48];
  } else if (prisadexSelection >= 51 && prisadexSelection <= 53) {
    profileImg = imgNode12[prisadexSelection - 51];
  }

  if (prisadexSelection == 17) {
    profileImg = imgFlying[6];
  }
  if (prisadexSelection == 18) {
    profileImg = imgFlying[2];
  }

  if (profileImg != -1) {
    iShowImage(100, 350, 300, 300, profileImg);
  }

  char typeText[50];
  sprintf(typeText, "Type: %s", prisadexTypes[prisadexSelection]);
  iSetColor(0, 0, 0);
  iText(180, 820, typeText, GLUT_BITMAP_TIMES_ROMAN_24);

  char strongBuf[60];
  char weakBuf[60];
  getStrongAgainst(prisadexTypes[prisadexSelection], strongBuf);
  getWeakAgainst(prisadexTypes[prisadexSelection], weakBuf);

  char strongText[100];
  char weakText[100];
  sprintf(strongText, "Strong against: %s", strongBuf);
  sprintf(weakText, "Weak against: %s", weakBuf);

  iSetColor(0, 120, 0);
  iText(70, 260, strongText, GLUT_BITMAP_HELVETICA_18);
  iSetColor(180, 0, 0);
  iText(70, 230, weakText, GLUT_BITMAP_HELVETICA_18);

  iSetColor(50, 50, 50);
  iFilledRectangle(5, 970, 121, 51);
  iSetColor(255, 255, 255);
  iText(40, 987, "BACK", GLUT_BITMAP_HELVETICA_18);
}

// ================= PC BOX (gameState 26, 27) =================
void drawPCBox() {
  iSetColor(0, 0, 0);
  iFilledRectangle(0, 0, 1024, 1024);

  if (gameState == 27) {
    iShowImage(0, 112, 1024, 800, imgPartyIndex);
  } else {
    iShowImage(0, 112, 1024, 800, imgTraining);
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  iFilledRectangle(60, 800, 140, 80);
  iSetColor(255, 255, 255);
  iText(65, 835, "Current Party", GLUT_BITMAP_HELVETICA_18);

  for (int i = 0; i < 6; i++) {
    int ry = 690 - (i * 110);
    int rw = 140;
    int rh = 80;
    int rx = 60;

    glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
    iFilledRectangle(rx, ry, rw, rh);

    int currentId = partyIDs[i];
    int drawImg = -1;

    if (currentId >= 0 && currentId <= 9) {
      drawImg = imgSmall[currentId];
    }

    if (drawImg != -1) {
      iSetColor(255, 255, 255);
      iShowImage(rx + 5, ry + 10, 60, 60, drawImg);
      iText(rx + 70, ry + 35, activePokeNames[currentId],
            GLUT_BITMAP_HELVETICA_12);
    }

    if (pcSwapState != 2) {
      if (pcCursorArea == 0) {
        if (pcCursorRow == i) {
          if (pcSwapState == 1) {
            iSetColor(255, 255, 0);
          } else {
            iSetColor(255, 255, 255);
          }
          iRectangle(rx, ry, rw, rh);
          iRectangle(rx - 1, ry - 1, rw + 2, rh + 2);
        }
      }
    }

    if (pcSwapState > 0) {
      if (pcSrcArea == 0) {
        if (pcSrcRow == i) {
          iSetColor(255, 0, 0);
          iRectangle(rx, ry, rw, rh);
          iRectangle(rx - 1, ry - 1, rw + 2, rh + 2);
        }
      }
    }
  }

  glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
  iFilledRectangle(260, 800, 380, 80);
  iSetColor(255, 255, 255);
  iText(380, 835, "Team In Queue", GLUT_BITMAP_HELVETICA_18);

  int startX = 260;
  int startY = 690;

  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 5; col++) {
      int sqX = startX + (col * 80);
      int sqY = startY - (row * 110);
      int sW = 60;
      int sH = 80;

      glColor4f(0.0f, 0.0f, 0.0f, 0.35f);
      iFilledRectangle(sqX, sqY, sW, sH);

      int qIdx = row * 5 + col;
      int qId = pcBoxIDs[qIdx];
      int qImg = -1;

      if (qId >= 0 && qId <= 9) {
        qImg = imgSmall[qId];
      }

      if (qImg != -1) {
        iSetColor(255, 255, 255);
        iShowImage(sqX + 5, sqY + 10, 50, 60, qImg);
      }

      if (pcSwapState != 2) {
        if (pcCursorArea == 1) {
          if (pcCursorRow == row) {
            if (pcCursorCol == col) {
              if (pcSwapState == 1) {
                iSetColor(255, 255, 0);
              } else {
                iSetColor(255, 255, 255);
              }
              iRectangle(sqX, sqY, sW, sH);
              iRectangle(sqX - 1, sqY - 1, sW + 2, sH + 2);
            }
          }
        }
      }

      if (pcSwapState > 0) {
        if (pcSrcArea == 1) {
          if (pcSrcRow == row) {
            if (pcSrcCol == col) {
              iSetColor(255, 0, 0);
              iRectangle(sqX, sqY, sW, sH);
              iRectangle(sqX - 1, sqY - 1, sW + 2, sH + 2);
            }
          }
        }
      }
    }
  }

  glDisable(GL_BLEND);

  iSetColor(50, 50, 50);
  iFilledRectangle(5, 970, 121, 51);
  iSetColor(255, 255, 255);
  iText(40, 987, "BACK", GLUT_BITMAP_HELVETICA_18);
}

// ================= FADE OVERLAY =================
void drawFadeOverlay() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(0.0f, 0.0f, 0.0f, fadeAlpha);
  iFilledRectangle(0, 0, 1024, 1024);
  glDisable(GL_BLEND);
}

// ================= LOCK SCREEN =================
void drawLockScreenOverlay() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
  iFilledRectangle(0, 0, 1024, 1024);
  glDisable(GL_BLEND);

  iSetColor(60, 60, 60);
  iFilledRectangle(462, 450, 100, 80);
  iSetColor(0, 0, 0);
  iText(365, 410, "complete previous stage to unlock it",
        GLUT_BITMAP_HELVETICA_18);
}
