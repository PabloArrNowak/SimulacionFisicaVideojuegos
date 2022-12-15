#include "RBSystem.h"
#include "RBForceGenerator.h"
#include "AngryBirdsObject.h"

RBSystem::RBSystem()
{
	objects = std::list<AngryBirdsObject*>();
	rbForceRegistry = RBForceRegistry();
	forceGenerators = std::list<RBForceGenerator*>();
}

void RBSystem::setLevelManager(LevelManager* lvlMngr)
{
	levelM = lvlMngr;
}

void RBSystem::update(double t)
{
	rbForceRegistry.update(t);

	for (auto it = objects.begin(); it != objects.end();) {
		if (!(*it)->update(t)) {
			AngryBirdsObject* del = *it;
			it = objects.erase(it);
			rbForceRegistry.deleteObj(del);
			delete del;
		}
		else it++;
	}

	for (auto obj : objects) {
		obj->resetForces();
	}
}

ParticleGenerator* RBSystem::getParticleGenerator(std::string name)
{
	return nullptr;
}

void RBSystem::setGenerator(ParticleGenerator* gen)
{
}

void RBSystem::resetParticles()
{
}
