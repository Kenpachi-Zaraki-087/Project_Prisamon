#include "pokemon.h"
#include <string.h>

const BattleMove gBattleMoves[] = {
	[MOVE_TACKLE] = { "Tackle", 40, TYPE_NORMAL, 100, 0 },
	[MOVE_EMBER] = { "Ember", 40, TYPE_FIRE, 100, 0 },
	[MOVE_WATER_GUN] = { "Water Gun", 40, TYPE_WATER, 100, 0 },
	[MOVE_VINE_WHIP] = { "Vine Whip", 45, TYPE_GRASS, 100, 0 },
	[MOVE_CONFUSION] = { "Confusion", 50, TYPE_PSYCHIC, 100, 0 },
	[MOVE_ROCK_THROW] = { "Rock Throw", 50, TYPE_ROCK, 90, 0 },
	[MOVE_THUNDER_SHOCK] = { "Thunder Shock", 40, TYPE_THUNDER, 100, 0 },
	[MOVE_SHADOW_BALL] = { "Shadow Ball", 80, TYPE_GHOST, 100, 0 },
	[MOVE_ICE_BEAM] = { "Ice Beam", 90, TYPE_ICE, 100, 0 },
	[MOVE_QUICK_ATTACK] = { "Quick Attack", 40, TYPE_NORMAL, 100, 1 } // +1 Priority
};

void InitPokemon(BattlePokemon* p, Species species, u8 level) {
	p->level = level;
	p->status1 = 0;

	// Base stats scaling (Simplified math for Visual Studio prototype)
	p->maxHp = 10 + (level * 3);
	p->hp = p->maxHp;
	p->attack = 5 + (level * 2);
	p->defense = 5 + (level * 2);
	p->speed = 5 + (level * 2);

	switch (species) {
	case SPECIES_CHARMANDER:
		strcpy(p->name, "Charmander");
		p->type1 = TYPE_FIRE; p->type2 = TYPE_FLYING;
		p->moves[0] = MOVE_EMBER; p->moves[1] = MOVE_TACKLE;
		break;
	case SPECIES_RATTATA: // Custom type from your list
		strcpy(p->name, "Rattata");
		p->type1 = TYPE_PSYCHIC; p->type2 = TYPE_NONE;
		p->moves[0] = MOVE_CONFUSION; p->moves[1] = MOVE_QUICK_ATTACK;
		p->speed += 10; // Extra speed
		break;
	case SPECIES_ARTICUNO:
		strcpy(p->name, "Articuno");
		p->type1 = TYPE_ICE; p->type2 = TYPE_FLYING;
		p->moves[0] = MOVE_ICE_BEAM; p->moves[1] = MOVE_GUST;
		p->maxHp += 20; p->hp = p->maxHp; // Legendary bump
		break;
		// Add the rest of your 26 Pokemon here following this pattern...
	default:
		strcpy(p->name, "MissingNo");
		p->type1 = TYPE_NORMAL; p->type2 = TYPE_NONE;
		p->moves[0] = MOVE_TACKLE;
		break;
	}
}