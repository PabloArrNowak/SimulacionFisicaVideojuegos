#include "Chuck.h"
#include "LevelManager.h"

Chuck::Chuck(LevelManager* lvlMngr, Vector3 pos) : Bird(lvlMngr, pos, 30, 2, { 1, 1, 0, 1 })
{
	damageMultipliers[WOOD] = 1.5;
	damageMultipliers[GLASS] = 1;
	damageMultipliers[STONE] = 1;
}

Chuck::~Chuck()
{
}


void Chuck::activatePower()
{
	powerAvailable = false;
	addForce(rb->getLinearVelocity() / 1.5);
}
