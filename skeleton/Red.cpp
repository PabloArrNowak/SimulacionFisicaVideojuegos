#include "Red.h"
#include "LevelManager.h"

Red::Red(LevelManager* lvlMngr, Vector3 pos) : Bird(lvlMngr, pos, 30, 2, {1, 0, 0, 1})
{
	damageMultipliers[WOOD] = 1.3;
	damageMultipliers[GLASS] = 1;
	damageMultipliers[STONE] = 1;
}

Red::~Red()
{
}


void Red::activatePower()
{
	powerAvailable = false;
}
