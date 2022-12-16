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
	sceneObjects = levelM->getSceneObjects();
}

void RBSystem::update(double t)
{
	rbForceRegistry.update(t);

	sceneObjects = levelM->getSceneObjects();

	for (auto it = sceneObjects.begin(); it != sceneObjects.end();) {
		if (!(*it)->update(t)) {
			AngryBirdsObject* del = *it;
			it = sceneObjects.erase(it);
			rbForceRegistry.deleteObj(del);
			levelM->removeObject(del);
			delete del;
		}
		else it++;
	}

	for (auto obj : sceneObjects) {
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
