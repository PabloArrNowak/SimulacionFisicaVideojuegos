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
	forceGenerators = levelM->getSceneForces();
}

void RBSystem::update(double t)
{
	rbForceRegistry.update(t);

	sceneObjects = levelM->getSceneObjects();
	forceGenerators = levelM->getSceneForces();

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

	/*for (auto obj : sceneObjects) {
		obj->resetForces();
	}*/
}