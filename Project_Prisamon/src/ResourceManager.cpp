#define _CRT_SECURE_NO_WARNINGS
#include "ResourceManager.h"

int totalLoadingTicks = 0;
int heroPageX = 0;
int panSpeed = 50;
int panPositions[10] = { 0, -114, -228, -341, -455, -569, -683, -796, -910, -1024 };
int panIndex = 0;
int panCooldown = 0;
int showDialogue = 1;
int currentDialogueIndex = 0;
int totalDialogues = 5;
int currentCharCount = 0;

int imgLoading1;
int imgLoading2;
int imgLoading3;
int imgLoading4;
int imgHeroPage;
int imgOak;
int imgChatbox;
int imgMap1;
int imgMap2;
int imgMap3;
int imgMap4;
int prisamonPaths[3];
int prisamonProfilePaths[3];
int imgPikachuProfile;
int imgOpenWorldBG;
int imgVillage16;
int imgBag;
int imgItemUI;
int imgGrindBattle;
int imgPrisadex;
int imgTraining;
int imgPartyIndex;

int imgFire[3];
int imgWater[5];
int imgGrass[3];
int imgFlying[7];
int imgElectric[3];
int imgRock[4];
int imgNormal[4];
int imgSmall[10];

int imgMap2Normal[3];
int imgMap2Psychic[3];
int imgNode9[4];
int imgNode10[4];
int imgNode11[3];
int imgNode12[3];
int imgDragonBall;
int imgCaveBattleground;

int imgGrassBattleground;
int imgPrisamonBack[3];
int imgPikachuBack;
int imgCaterpieFront;
int imgMyHPBox;
int imgOppHPBox;
int imgBattleDashboard;
int imgPointer;

int imgWildPoke[6];
int imgWildPokeBack[6];

char dialogueArray[5][100] = {
	"Ah, there you are! You have that specific 'glow' about you.",
	"And no, I don't think it's just the sunlight hitting your jacket.",
	"In this world, every soul refracts light differently.",
	"We call that bond a Prisamon.",
	"Tell me, are you ready to see which Prisamon you'll claim today?"
};

int currentEndDialogueIndex = 0;
int totalEndDialogues = 4;
char endDialogueArray[4][100] = {
	"A brilliant match! See how it shines?",
	"That Prisamon's glow perfectly reflects your own spirit.",
	"You two are going to light up the world together.",
	"Now, get out and show them your true strength!"
};

int currentPikachuDialogueIndex = 0;
int totalPikachuDialogues = 2;
char pikachuDialogueArray[2][100] = {
	"I have another Prisamon for you, it is Pikachu.",
	"Take good care of it!"
};

int showOakMapDialogue = 1;
int currentOakMapDialogueIndex = 0;
int totalOakMapDialogues = 3;
char oakMapDialogueArray[3][100] = {
	"Here we are, the first region of your journey!",
	"Now is the perfect time to test your new Prisamon's power.",
	"Click on the first area (1-1) to begin your very first battle!"
};

int hasSeenWildIntro = 0;
int showOakWildIntro = 0;
int currentOakWildIntroIndex = 0;
int totalOakWildIntros = 3;
char oakWildIntroArray[3][100] = {
	"Welcome to the wild! This is where Prisamon roam free.",
	"Walk into the tall grass, and you might encounter one.",
	"Weaken them first, then use your Prisaballs to catch them!"
};

int showOakBlockDialogue = 0;
int currentOakBlockIndex = 0;
int totalOakBlocks = 1;
char oakBlockArray[1][100] = {
	"Wait! You must complete Stage 1-3 before going there."
};

int hasSeenGrindIntro = 0;
int showOakGrindIntro = 0;
int currentOakGrindIntroIndex = 0;
int totalOakGrindIntros = 2;
char oakGrindIntroArray[2][100] = {
	"Excellent catch! Your team is getting stronger.",
	"Click the ITEM menu to grind materials for your Prisamon!"
};

int imgGastly;
int imgHaunter;
int imgGengar;

char currentMusic[20] = "";

int imgPokeball1;
int imgPlayerUp;
int imgPlayerDown;
int imgPlayerLeft;
int imgPlayerRight;

// ================= HELPER FUNCTIONS =================
void triggerTransition(int targetState) {
	if (!isFading) {
		if (gameState != 12 && gameState != 121) {
			previousGameState = gameState;
		}
		nextGameState = targetState;
		isFading = 1;
		fadeDirection = 1;
		fadeAlpha = 0.0f;
	}
}

unsigned int safeLoadImage(const char* path) {
	FILE* file = fopen(path, "rb");
	if (file == NULL) {
		printf("Error: Missing file %s\n", path);
		ExitProcess(1);
	}
	fclose(file);
	return iLoadImage((char*)path);
}

void loadAllImages() {
	imgPokeball1 = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Utils UI\\pokeball1.png");
	imgLoading1 = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\LOADING PAGE\\LAODING 1.bmp");
	imgLoading2 = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\LOADING PAGE\\LOADING 2.bmp");
	imgLoading3 = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\LOADING PAGE\\LOADING 3.bmp");
	imgLoading4 = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\LOADING PAGE\\LOADING 4.bmp");
	imgHeroPage = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\hERO_PAGE\\Hero_page.png");
	imgOak = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\character\\proferrsor oak - Edited.png");
	imgChatbox = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\CHATBOX\\chatbox.bmp");
	prisamonPaths[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\PRISADEX\\DETAIL\\BULBASOUR.bmp");
	prisamonPaths[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\PRISADEX\\DETAIL\\CHARMEDER.bmp");
	prisamonPaths[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\PRISADEX\\DETAIL\\SQUIRTLE.bmp");
	imgFire[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Charmender.png");
	imgFire[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Charmeleon.png");
	imgFire[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Charizard.png");
	imgWater[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Squirtle.png");
	imgWater[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Wartotle.png");
	imgWater[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Blastoise.png");
	imgWater[3] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\magikarp.png");
	imgWater[4] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\gyarados.png");

	imgGrass[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Balbasour.png");
	imgGrass[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Ivysaur.png");
	imgGrass[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Venusaur.png");

	imgFlying[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Artiquno.png");
	imgFlying[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\butterfree.png");
	imgFlying[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Fearow.png");
	imgFlying[3] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\pidgy.png");
	imgFlying[4] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Pidgeotto.png");
	imgFlying[5] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\pidgeot.png");
	imgFlying[6] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\spearow.png");
	imgElectric[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\voltorb.png");
	imgElectric[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\pikachu.png");
	imgElectric[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Electrode.png");
	imgRock[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Geodude.png");
	imgRock[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\golem.png");
	imgRock[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\graveler.png");
	imgRock[3] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\onix.png");
	imgNormal[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\caterpie.png");
	imgNormal[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Metapod.png");
	imgNormal[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\raticate.png");
	imgNormal[3] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\rattata.png");

	prisamonProfilePaths[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Balbasour.png");
	prisamonProfilePaths[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Charmender.png");
	prisamonProfilePaths[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Squirtle.png");

	imgPikachuProfile = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\pikachu.png");
	imgMap1 = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Stage screen\\map-1.bmp");
	imgMap2 = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Stage screen\\map-2.bmp");
	imgMap3 = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Stage screen\\map-3.bmp");
	imgMap4 = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Stage screen\\map-4.bmp");
	imgGrassBattleground = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\grass.png");
	imgPrisamonBack[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\back_pokemon\\Bulbasaur_back.png");
	imgPrisamonBack[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\back_pokemon\\Charmender_Back.png");
	imgPrisamonBack[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\back_pokemon\\squirtle_back.png");
	imgPikachuBack = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\back_pokemon\\Pikachu_back.png");
	imgCaterpieFront = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\front_Pokemon\\Caterpie_front.png");
	imgOpenWorldBG = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Openworld\\BG1.png");
	imgPlayerUp = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\character\\lucas\\lucasB.png");
	imgPlayerDown = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\character\\lucas\\lucasF.png");
	imgPlayerLeft = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\character\\lucas\\lucasL.png");
	imgPlayerRight = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\character\\lucas\\lucasR.png");
	currentImgPlayer = imgPlayerDown;

	imgWildPokeBack[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\back_pokemon\\Duskull_back.png");
	imgWildPokeBack[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\back_pokemon\\rattata_back.png");
	imgWildPokeBack[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\back_pokemon\\sprearow.png");
	imgWildPokeBack[3] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\back_pokemon\\Magicarp_back.png");
	imgWildPokeBack[4] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\back_pokemon\\Pidgeotto_Back.png");
	imgWildPokeBack[5] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\back_pokemon\\Scyther_Back.png");

	imgVillage16 = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Openworld\\BG2.png");
	imgBag = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Utils UI\\bag.png");
	imgItemUI = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Utils UI\\items UI.png");
	imgGrindBattle = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\dystopian.jpg");
	imgGastly = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\gastly.png");
	imgHaunter = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\haunter.png");
	imgGengar = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\gengar.png");
	dystopianEnemyImages[0] = imgGastly;
	dystopianEnemyImages[1] = imgHaunter;
	dystopianEnemyImages[2] = imgGengar;
	imgPrisadex = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Utils UI\\prisadex (2).png");
	imgTraining = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Utils UI\\Training.png");
	imgPartyIndex = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Utils UI\\party index.png");

	imgSmall[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Party\\Bulbasaur_small.png");
	imgSmall[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Party\\Charmender_small.png");
	imgSmall[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Party\\Squirtle_small.png");
	imgSmall[3] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Party\\Pikachu_small.png");
	imgSmall[4] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Party\\Dukskull_small.png");
	imgSmall[5] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Party\\Ratata_small.png");
	imgSmall[6] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Party\\Spearow_small.png");
	imgSmall[7] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Party\\Magicarp_small.png");
	imgSmall[8] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Party\\Pidgeotto_small.png");
	imgSmall[9] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Party\\Scyther_small.png");

	imgWildPoke[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\front_Pokemon\\Duskull.png");
	imgWildPoke[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\front_Pokemon\\Rattata.png");
	imgWildPoke[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\front_Pokemon\\Spearow.png");
	imgWildPoke[3] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\magikarp.png");
	imgWildPoke[4] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Pidgeotto.png");
	imgWildPoke[5] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\Scyther.png");
	
	imgMap2Normal[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\whismur (2).png");
	imgMap2Normal[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\loudred.png");
	imgMap2Normal[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\exploud.png");
	
	imgMap2Psychic[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\abra1.png");
	imgMap2Psychic[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\kadabra.png");
	imgMap2Psychic[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\alakazam (2).png");
	
	imgNode9[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\zubat1.png");
	imgNode9[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\diglett.png");
	imgNode9[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\golbat.png");
	imgNode9[3] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\dugtrio.png");

	imgNode10[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\paras.png");
	imgNode10[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\parasect (2).png");
	imgNode10[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\makuhita (2).png");
	imgNode10[3] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\hariyama (2).png");

	imgNode11[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\deino (2).png");
	imgNode11[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\zweilous (2).png");
	imgNode11[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\hydreigon (2).png");

	imgNode12[0] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\aerodactyl (2).png");
	imgNode12[1] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\aurorus (2).png");
	imgNode12[2] = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\POKEMON\\Prisamon_profile\\tyrantrum (2).png");

	imgDragonBall = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\Utils UI\\pokeball1.png");

	imgCaveBattleground = safeLoadImage("C:\\game_project\\Project_Prisamon\\Project_Prisamon\\img\\battle_background\\cave.png");
}

void updateLoadingScreen() {
	if (gameState == 1) {
		currentFrame++;
		totalLoadingTicks++;
		if (currentFrame > 4) {
			currentFrame = 1;
		}
		if (totalLoadingTicks >= 26) {
			triggerTransition(2);
		}
	}
}

void updateTypewriter() {
	if (gameState == 2 && showDialogue == 1) {
		if (currentCharCount < (int)strlen(dialogueArray[currentDialogueIndex])) {
			currentCharCount++;
		}
	}
	else if (gameState == 4) {
		if (currentCharCount < (int)strlen(endDialogueArray[currentEndDialogueIndex])) {
			currentCharCount++;
		}
	}
	else if (gameState == 6) {
		if (currentCharCount < (int)strlen(pikachuDialogueArray[currentPikachuDialogueIndex])) {
			currentCharCount++;
		}
	}
	else if (gameState == 8 && showOakMapDialogue == 1) {
		if (currentCharCount < (int)strlen(oakMapDialogueArray[currentOakMapDialogueIndex])) {
			currentCharCount++;
		}
	}
	else if ((gameState == 15 || gameState == 16) && showOakWildIntro == 1) {
		if (currentCharCount < (int)strlen(oakWildIntroArray[currentOakWildIntroIndex])) {
			currentCharCount++;
		}
	}
	else if ((gameState == 15 || gameState == 16) && showOakBlockDialogue == 1) {
		if (currentCharCount < (int)strlen(oakBlockArray[currentOakBlockIndex])) {
			currentCharCount++;
		}
	}
	else if (gameState == 7 && showOakGrindIntro == 1) {
		if (currentCharCount < (int)strlen(oakGrindIntroArray[currentOakGrindIntroIndex])) {
			currentCharCount++;
		}
	}
}

void updateFade() {
	if (isFading) {
		fadeAlpha += 0.05f * fadeDirection;
		if (fadeAlpha >= 1.0f && fadeDirection == 1) {
			fadeAlpha = 1.0f;
			gameState = nextGameState;
			fadeDirection = -1;
		}
		else if (fadeAlpha <= 0.0f && fadeDirection == -1) {
			fadeAlpha = 0.0f;
			isFading = 0;
		}
	}
}

void updateAutoPan() {
	if (gameState == 7 && !heroPageVisited && heroPageX > -1024) {
		heroPageX -= 8;
		if (heroPageX < -1024) {
			heroPageX = -1024;
		}
	}
}

void updateLockScreen() {
	if (lockScreenTimer > 0) {
		lockScreenTimer--;
	}
}

void drawLockScreen() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
	iFilledRectangle(0, 0, 1024, 1024);
	glDisable(GL_BLEND);

	iSetColor(60, 60, 60);
	iFilledRectangle(462, 450, 100, 80);
	iSetColor(0, 0, 0);
	iText(365, 410, "complete previous stage to unlock it", GLUT_BITMAP_HELVETICA_18);
}

void updateAutoMapTour() {
	if (isFirstTimeMapTour && !isFading) {
		if (gameState >= 8 && gameState <= 11) {
			mapTourTimer++;
			if (mapTourTimer >= 50) {
				if (gameState == 8) {
					map1Completed = 1;
					triggerTransition(9);
				}
				else if (gameState == 9) {
					map2Completed = 1;
					triggerTransition(10);
				}
				else if (gameState == 10) {
					map3Completed = 1;
					triggerTransition(11);
				}
				else if (gameState == 11) {
					triggerTransition(8);
					isFirstTimeMapTour = 0;
				}
				mapTourTimer = 0;
			}
		}
	}
}

// ================= SAVE & LOAD SYSTEM =================
void saveGameState() {
	FILE *fp = fopen("save_data.txt", "w");
	if (fp != NULL) {
		fprintf(fp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %lld ",
			potionCount, coins, prisaballs, evolutionStones, xpCandies,
			nodesCleared, selectedPrisamon, heroPageVisited,
			map1Completed, map2Completed, map3Completed, isFirstTimeMapTour,
			caughtWild[0], caughtWild[1], caughtWild[2], caughtWild[3], caughtWild[4], caughtWild[5], hasSeenWildIntro, hasSeenGrindIntro, lastGrindTime);

		fprintf(fp, "%d %d ", partySize, currentActivePokemon);
		for (int i = 0; i < 6; i++) {
			fprintf(fp, "%d %d %d %d %d %d ", partyIDs[i], partyHP[i], partyMaxHP[i], partyLevel[i], partyAttack[i], partyEXP[i]);
		}
		for (int i = 0; i < 30; i++) {
			fprintf(fp, "%d %d %d %d %d %d ", pcBoxIDs[i], pcBoxHP[i], pcBoxMaxHP[i], pcBoxLevel[i], pcBoxAttack[i], pcBoxEXP[i]);
		}
		fclose(fp);
		printf("Game Saved Successfully!\n");
	}
	else {
		printf("Error: Could not create save file.\n");
	}
}

void loadGameState() {
	FILE *fp = fopen("save_data.txt", "r");
	if (fp != NULL) {
		fscanf(fp, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %lld",
			&potionCount, &coins, &prisaballs, &evolutionStones, &xpCandies,
			&nodesCleared, &selectedPrisamon, &heroPageVisited,
			&map1Completed, &map2Completed, &map3Completed, &isFirstTimeMapTour,
			&caughtWild[0], &caughtWild[1], &caughtWild[2], &caughtWild[3], &caughtWild[4], &caughtWild[5], &hasSeenWildIntro, &hasSeenGrindIntro, &lastGrindTime);

		// Pre-initialize PC box to handle older saves gracefully
		for (int i = 0; i < 30; i++) {
			pcBoxIDs[i] = -1;
			pcBoxHP[i] = 0;
			pcBoxMaxHP[i] = 0;
			pcBoxLevel[i] = 0;
			pcBoxAttack[i] = 0;
			pcBoxEXP[i] = 0;
		}

		fscanf(fp, "%d %d", &partySize, &currentActivePokemon);
		for (int i = 0; i < 6; i++) {
			fscanf(fp, "%d %d %d %d %d %d", &partyIDs[i], &partyHP[i], &partyMaxHP[i], &partyLevel[i], &partyAttack[i], &partyEXP[i]);
		}
		for (int i = 0; i < 30; i++) {
			if (feof(fp)) break;
			fscanf(fp, "%d %d %d %d %d %d", &pcBoxIDs[i], &pcBoxHP[i], &pcBoxMaxHP[i], &pcBoxLevel[i], &pcBoxAttack[i], &pcBoxEXP[i]);
		}
		fclose(fp);

		loadActivePokemon();

		if (time(NULL) - lastGrindTime >= grindCooldown) {
			canGrind = 1;
		}
		else {
			canGrind = 0;
		}

		// Ensure hero page is fully navigable
		heroPageVisited = 1;
		isFirstTimeMapTour = 0;
		heroPageX = -1024;
		panIndex = 9;
		showDialogue = 0;
		showOakMapDialogue = 0;
		showOakWildIntro = 0;
		showOakBlockDialogue = 0;
		showOakGrindIntro = 0;

		printf("Game Loaded Successfully!\n");

		gameState = 7;
	}
	else {
		printf("No save file found. Start a New Game!\n");
	}
}
