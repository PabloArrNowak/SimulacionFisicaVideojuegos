#include "LevelManager.h"
#include "AngryBirdsObject.h"
#include "RBForceGenerator.h"
#include "RBSystem.h"
#include "BuildingBlock.h"
#include "GroundBlock.h"

LevelManager::LevelManager(PxScene* gScene, RBSystem* rbSystem)
{
	this->gScene = gScene;
	this->rbSystem = rbSystem;
}

LevelManager::~LevelManager()
{
}

void LevelManager::startLevel(int level)
{
	clearBlocks();
	addObject(new GroundBlock({ 0, -0.3, 0 }, { 8000, 0.5, 8000 }));

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
}

void LevelManager::addObject(AngryBirdsObject* obj)
{
	PxActor* rb = obj->getRB();
	gScene->addActor(*rb);

	for (RBForceGenerator* force : rbSystem->getForceGenerators()) {
		if (force->getAffectsAll() && dynamic_cast<GroundBlock*>(obj) != obj) {
			rbSystem->addToRegistry(obj, force);
			obj->resetForces();
		}
	}

	sceneObjects.push_back(obj);
}

void LevelManager::setupLevel1()
{
	// Primero Fuerzas
	

	// Luego Objetos, con AddObject
	addObject(new BuildingBlock({ 250, 1, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 10));
	addObject(new BuildingBlock({ 400, 1, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 10));
	addObject(new BuildingBlock({ 550, 1, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::WOOD, 10));

	addObject(new BuildingBlock({ 325, 121, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::GLASS, 10));
	addObject(new BuildingBlock({ 475, 121, 0 }, { 155, 20, 20 }, AngryBirdsObject::blockMat::GLASS, 10));

	addObject(new BuildingBlock({ 400, 182, 0 }, { 20, 100, 20 }, AngryBirdsObject::blockMat::STONE, 10));

}

void LevelManager::setupLevel2()
{

}

void LevelManager::setupLevel3()
{

}