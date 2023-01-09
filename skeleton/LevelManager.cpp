#include "LevelManager.h"
#include "AngryBirdsObject.h"
#include "RBForceGenerator.h"
#include "RBSystem.h"
#include "BuildingBlock.h"
#include "GroundBlock.h"
#include "Red.h"
#include "Chuck.h"
#include "Blues.h"
#include "WindRBForceGenerator.h"

LevelManager::LevelManager(PxScene* gScene, RBSystem* rbSystem)
{
	this->gScene = gScene;
	this->rbSystem = rbSystem;

	sceneObjects = std::list<AngryBirdsObject*>();

	slingshotPos = { -1000, 200, 0 };
}

LevelManager::~LevelManager()
{
}

void LevelManager::startLevel(int level)
{
	clearBlocks();
	clearForceGens();
	birds.clear();
	addObject(new GroundBlock({ 0, -0.3, 0 }, { 8000, 0.5, 8000 }));

	currentLevel = level;
	switch (level)
	{
	case 1:
		setupLevel1();
		break;
	case 2:
		setupLevel2();
		break;
	case 3:
		setupLevel3();
		break;
	default:
		break;
	}


}

void LevelManager::clearBlocks()
{
	// sceneObjects
	for (auto it = sceneObjects.begin(); it != sceneObjects.end();) {
		auto e = *it;
		it = sceneObjects.erase(it);
		gScene->removeActor(*e->getRB());
		rbSystem->removeObj(e);
		delete e;
	}
}

void LevelManager::addObject(AngryBirdsObject* obj)
{
	PxActor* rb = obj->getRB();
	gScene->addActor(*rb);

	for (RBForceGenerator* force : rbSystem->getForceGenerators()) {
		if (force->getAffectsAll() && rb->is<PxRigidDynamic>()) {
			rbSystem->addToRegistry(obj, force);
			obj->resetForces();
		}
	}

	sceneObjects.push_back(obj);
}



void LevelManager::addBird(Bird* bird, bool addToQueue)
{
	PxActor* rb = bird->getRB();
	gScene->addActor(*rb);

	for (RBForceGenerator* force : rbSystem->getForceGenerators()) {
		if (force->getAffectsAll()) {
			rbSystem->addToRegistry(bird, force);
			bird->resetForces();
		}
	}

	if (addToQueue)
		birds.push_back(bird);
	sceneObjects.push_back(bird);
}

void LevelManager::removeObject(AngryBirdsObject* obj) { sceneObjects.remove(obj); gScene->removeActor(*obj->getRB()); }

void LevelManager::birdInteract()
{
	if (birds.empty())
		return;

	Bird* activeBird = birds.front();
	if (activeBird == nullptr)
		return;

	if (activeBird->airborn() && activeBird->hasPowerAvilable()) {
		activeBird->activatePower();
	}
	else if (!activeBird->airborn() && activeBird->hasPowerAvilable()) {
		activeBird->autoLaunch();
	}
}

void LevelManager::setupLevel1()
{
	// Primero Fuerzas
	

	// Luego Objetos, con AddObject

	addObject(new BuildingBlock({ 250, 51, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 50));
	addObject(new BuildingBlock({ 400, 51, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 50));
	addObject(new BuildingBlock({ 550, 51, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 50));

	addObject(new BuildingBlock({ 325, 121, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::GLASS, 30));
	addObject(new BuildingBlock({ 475, 121, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::GLASS, 30));

	addObject(new BuildingBlock({ 400, 182, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::STONE, 100));

	addObject(new BuildingBlock({ 325, 252, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::GLASS, 30));
	addObject(new BuildingBlock({ 475, 252, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::GLASS, 30));


	// Birds
	addBird(new Red(this, slingshotPos), true);
	addBird(new Chuck(this, Vector3(slingshotPos.x - 100, 31, 0)), true);
	addBird(new Blues(this, Vector3(slingshotPos.x - 200, 31, 0)), true);

}

void LevelManager::setupLevel2()
{
	// Primero Fuerzas
	addForceGen(new WindRBForceGenerator(Vector3(500, 500, 0), Vector3(-350, 300, 0), Vector3(200, 800, 50)));

	// Luego Objetos, con AddObject

	addObject(new BuildingBlock({ 500, 250, 0 }, { 500, 500, 50 }, AngryBirdsObject::blockMat::STONE, 1000));

	addObject(new BuildingBlock({ 350, 551, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 50));
	addObject(new BuildingBlock({ 500, 551, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 50));
	addObject(new BuildingBlock({ 650, 551, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 50));

	addObject(new BuildingBlock({ 425, 621, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::WOOD, 30));
	addObject(new BuildingBlock({ 575, 621, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::WOOD, 30));

	addObject(new BuildingBlock({ 500, 682, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 100));

	addObject(new BuildingBlock({ 425, 752, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::WOOD, 30));
	addObject(new BuildingBlock({ 575, 752, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::WOOD, 30));


	// Birds
	addBird(new Blues(this, slingshotPos), true);
	addBird(new Chuck(this, Vector3(slingshotPos.x - 100, 31, 0)), true);
	addBird(new Chuck(this, Vector3(slingshotPos.x - 200, 31, 0)), true);
}

void LevelManager::setupLevel3()
{
	// Primero Fuerzas
	addForceGen(new WindRBForceGenerator(Vector3(500, 500, 0), Vector3(-350, 300, 0), Vector3(200, 800, 50)));

	// Luego Objetos, con AddObject

	addObject(new BuildingBlock({ 500, 250, 0 }, { 500, 500, 50 }, AngryBirdsObject::blockMat::STONE, 1000));

	addObject(new BuildingBlock({ 350, 551, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 50));
	addObject(new BuildingBlock({ 500, 551, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 50));
	addObject(new BuildingBlock({ 650, 551, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 50));

	addObject(new BuildingBlock({ 425, 621, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::WOOD, 30));
	addObject(new BuildingBlock({ 575, 621, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::WOOD, 30));

	addObject(new BuildingBlock({ 500, 682, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 100));

	addObject(new BuildingBlock({ 425, 752, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::WOOD, 30));
	addObject(new BuildingBlock({ 575, 752, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::WOOD, 30));


	// Birds
	addBird(new Red(this, slingshotPos), true);
	addBird(new Chuck(this, Vector3(slingshotPos.x - 100, 31, 0)), true);
	addBird(new Chuck(this, Vector3(slingshotPos.x - 200, 31, 0)), true);
}

AngryBirdsObject* LevelManager::getObjFromActor(PxActor* actor)
{
	for (AngryBirdsObject* obj : sceneObjects) {
		if (obj->getRB() == actor)
			return obj;
	}

	return nullptr;
}

void LevelManager::nextBird()
{
	birds.pop_front();

	if (!birds.empty()) {
		birds.front()->setPos(slingshotPos);
		birds.front()->resetBird();
	}
	// else
		// startLevel(currentLevel);
}

void LevelManager::addForceGen(RBForceGenerator* gen)
{
	// sceneForces.push_back(gen);

	//for (AngryBirdsObject* obj : sceneObjects) {
	//	if (gen->getAffectsAll() && obj->getRB()->is<PxRigidDynamic>()) {
	//		rbSystem->addToRegistry(obj, gen);
	//	}
	//}

	rbSystem->addForceGen(gen);
}

void LevelManager::clearForceGens()
{
	for (auto it = sceneForces.begin(); it != sceneForces.end();) {
		auto e = *it;
		it = sceneForces.erase(it);
		rbSystem->removeForceGen(e);
		delete e;
	}
}