#include "pokemon.h"
#include <time.h>
#include <stdlib.h>

void StartBattle(BattlePokemon* player, BattlePokemon* enemy);

int main() {
	// Seed the RNG for the speed ties
	srand((unsigned int)time(NULL));

	BattlePokemon myRattata;
	BattlePokemon wildCharmander;

	// Initialize using your custom specs
	InitPokemon(&myRattata, SPECIES_RATTATA, 10);
	InitPokemon(&wildCharmander, SPECIES_CHARMANDER, 10);

	// Run the state machine
	StartBattle(&myRattata, &wildCharmander);

	return 0;
}