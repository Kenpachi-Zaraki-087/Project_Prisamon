#pragma once

// Core state
extern int x;
extern int y;
extern int gameState;
extern int previousGameState;
extern int battleReturnState;
extern int imagesLoaded;

// Mouse
extern int hoverX;
extern int hoverY;
extern int lastClickX;
extern int lastClickY;

// Animation
extern int currentFrame;

// Progression
extern int isFirstTimeMapTour;
extern int heroPageVisited;
extern int currentActiveNode;

// Inventory
extern int bagSelection;
extern int bagMenuCooldown;
extern int coins;
extern int evolutionStones;
extern int xpCandies;
extern int potionCount;
extern int dragonBalls;
extern char itemDescLine1[7][100];
extern char itemDescLine2[7][100];

// Fade transition
extern int isFading;
extern float fadeAlpha;
extern int fadeDirection;
extern int nextGameState;

// Misc global
extern int totalEnemies;
extern int currentPrisamonIndex;
extern int selectedPrisamon;
extern int activeButton;

// Grinding
extern long long lastGrindTime;
extern int grindCooldown;
extern int canGrind;

// Dystopian
extern int totalDystopianEnemies;

// Player dimensions
extern int playerWidth;
extern int playerHeight;

// Prisadex
extern int prisadexSelection;
extern int prisadexTopIndex;
extern int totalPrisamon;
extern char prisadexNames[60][30];
extern char prisadexTypes[60][20];
