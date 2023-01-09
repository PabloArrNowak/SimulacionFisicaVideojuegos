#include "Bomb.h"
#include "LevelManager.h"

Bomb::Bomb(LevelManager* lvlMngr, Vector3 pos) : Bird(lvlMngr, pos, 30, 2, { 0.3, 0.3, 0.3, 1 })
{
	damageMultipliers[WOOD] = 1.5;
	damageMultipliers[GLASS] = 1;
	damageMultipliers[STONE] = 1;
}

Bomb::~Bomb()
{
}


void Bomb::activatePower()
{
	powerAvailable = false;
	// lvlMngr
	lvlMngr->nextBird();
}
