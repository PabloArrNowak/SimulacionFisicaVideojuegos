#pragma once

#include<PxPhysicsAPI.h>
#include <list>
#include "core.hpp"

class AngryBirdsObject;
class RBSystem;
class RBForceGenerator;

using namespace physx;

class Bird;

class LevelManager
{
	std::list<AngryBirdsObject*> sceneObjects;
	std::list<RBForceGenerator*> sceneForces;

	std::list<Bird*> birds; // Front is active / flying
	PxScene* gScene = nullptr;
	RBSystem* rbSystem;

	Vector3 slingshotPos;
	int currentLevel;

public:

	LevelManager(PxScene* gScene, RBSystem* rbSystem);
	~LevelManager();

	void clearBlocks();
	void startLevel(int level);

	Bird* getActiveBird() { return birds.front(); };
	void nextBird();
	void addBird(Bird* bird, bool addToQueue);

	void addObject(AngryBirdsObject* obj);
	void addForceGen(RBForceGenerator* gen);
	void clearForceGens();

	std::list<AngryBirdsObject*> getSceneObjects() { return sceneObjects; };
	std::list<RBForceGenerator*> getSceneForces() { return sceneForces; };
	void removeObject(AngryBirdsObject* obj);

	void birdInteract();

	AngryBirdsObject* getObjFromActor(PxActor* actor);

protected:

	void setupLevel1();
	void setupLevel2();
	void setupLevel3();
};

