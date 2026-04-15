#define _CRT_SECURE_NO_WARNINGS
#include "Globals.h"

// Core state
int x = 0;
int y = 0;
int gameState = 0;
int previousGameState = 0;
int battleReturnState = 0;
int imagesLoaded = 0;

// Mouse
int hoverX = 0;
int hoverY = 0;
int lastClickX = -1;
int lastClickY = -1;

// Animation
int currentFrame = 1;

// Progression
int isFirstTimeMapTour = 1;
int heroPageVisited = 0;
int currentActiveNode = 0;

// Inventory
int bagSelection = 0;
int bagMenuCooldown = 0;
int coins = 0;
int evolutionStones = 0;
int xpCandies = 0;
int potionCount = 3;

int dragonBalls = 0;

char itemDescLine1[7][100] = {
	"A medicinal spray that restores 45 HP to your Prisamon,",
	"The shimmering currency of this world, used to trade",
	"A specialized capture device that refracts light to",
	"A mysterious, radiant mineral that triggers a permanent",
	"A concentrated burst of energy that instantly boosts",
	"A specialized multi-colored ball designed uniquely for",
	""
};

char itemDescLine2[7][100] = {
	"mending wounds sustained in the heat of battle.",
	"with merchants for better gear and supplies.",
	"tether and claim a wild Prisamon as your own.",
	"transformation in certain species of Prisamon.",
	"your Prisamon's experience points.",
	"capturing the elusive and powerful Dragon type Prisamon.",
	""
};

// Fade transition
int isFading = 0;
float fadeAlpha = 0.0f;
int fadeDirection = 0;
int nextGameState = -1;

// Misc global
int totalEnemies = 1;
int currentPrisamonIndex = 0;
int selectedPrisamon = -1;
int activeButton = 0;

// Grinding
long long lastGrindTime = 0;
int grindCooldown = 600;
int canGrind = 1;

// Dystopian
int totalDystopianEnemies = 3;

// Player dimensions
int playerWidth = 48;
int playerHeight = 27;

// Prisadex
int prisadexSelection = 0;
int prisadexTopIndex = 0;
int totalPrisamon = 54;
char prisadexNames[60][30] = {
	"Bulbasaur", "Ivysaur", "Venusaur",
	"Charmander", "Charmeleon", "Charizard",
	"Squirtle", "Wartortle", "Blastoise",
	"Caterpie", "Metapod", "Butterfree",
	"Pidgey", "Pidgeotto", "Pidgeot",
	"Rattata", "Raticate", "Spearow", "Fearow",
	"Pikachu", "Voltorb", "Electrode",
	"Geodude", "Graveler", "Golem", "Onix",
	"Magikarp", "Gyarados", "Articuno",
	"Duskull", "Gastly", "Haunter", "Gengar",
	"Scyther", "Whismur", "Loudred", "Exploud",
	"Abra", "Kadabra", "Alakazam",
	"Zubat", "Diglett", "Golbat", "Dugtrio",
	"Paras", "Parasect", "Makuhita", "Hariyama",
	"Deino", "Zweilous", "Hydreigon",
	"Aerodactyl", "Aurorus", "Tyrantrum"
};
char prisadexTypes[60][20] = {
	"Grass", "Grass", "Grass",
	"Fire", "Fire", "Fire",
	"Water", "Water", "Water",
	"Normal", "Normal", "Flying",
	"Flying", "Flying", "Flying",
	"Normal", "Normal", "Flying", "Flying",
	"Electric", "Electric", "Electric",
	"Rock", "Rock", "Rock", "Rock",
	"Water", "Water", "Flying",
	"Ghost", "Ghost", "Ghost", "Ghost",
	"Grass", "Normal", "Normal", "Normal",
	"Psychic", "Psychic", "Psychic",
	"Flying", "Grass", "Flying", "Grass",
	"Grass", "Grass", "Fighting", "Fighting",
	"Dragon", "Dragon", "Dragon",
	"Flying", "Dragon", "Dragon"
};
