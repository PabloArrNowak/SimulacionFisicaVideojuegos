#include "Blues.h"
#include "LevelManager.h"

Blues::Blues(LevelManager* lvlMngr, Vector3 pos) : Bird(lvlMngr, pos, 25, 2, { 0, 1, 1, 1 })
{
	damageMultipliers[WOOD] = 1;
	damageMultipliers[GLASS] = 1.5;
	damageMultipliers[STONE] = 1;
}

Blues::~Blues()
{
}


void Blues::activatePower()
{
	powerAvailable = false;

	Blues* blu1 = new Blues(lvlMngr, Vector3(rb->getGlobalPose().p.x, rb->getGlobalPose().p.y + 60, rb->getGlobalPose().p.z));
	lvlMngr->addBird(blu1, false);
	blu1->addForce(Vector3(rb->getLinearVelocity().x * velMultiplier, rb->getLinearVelocity().y * velMultiplier + 5, rb->getLinearVelocity().z * velMultiplier));
	blu1->setFlying(true);
	blu1->setPowerAvailable(false);
	blu1->setFurthersQueue(false);

	Blues* blu2 = new Blues(lvlMngr, Vector3(rb->getGlobalPose().p.x, rb->getGlobalPose().p.y - 60, rb->getGlobalPose().p.z));
	lvlMngr->addBird(blu2, false);
	blu2->addForce(Vector3(rb->getLinearVelocity().x * velMultiplier, rb->getLinearVelocity().y * velMultiplier - 5, rb->getLinearVelocity().z * velMultiplier));
	blu2->setFlying(true);
	blu2->setPowerAvailable(false);
	blu2->setFurthersQueue(false);
}
