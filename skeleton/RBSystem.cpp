#include "RBSystem.h"
#include "RBForceGenerator.h"
#include "AngryBirdsObject.h"

RBSystem::RBSystem()
{
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

	for (auto it = levelM->getSceneObjects().begin(); it != levelM->getSceneObjects().end();) {
		if (!(*it)->update(t)) {
			AngryBirdsObject* del = *it;
			it = levelM->getSceneObjects().erase(it);
			rbForceRegistry.deleteObj(del);
			delete del;
		}
		else it++;
	}

	for (auto obj : levelM->getSceneObjects()) {
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
