#pragma once

#include<PxPhysicsAPI.h>
#include <list>

class AngryBirdsObject;
class RBSystem;

using namespace physx;

class Bird;

class LevelManager
{
	std::list<AngryBirdsObject*> sceneObjects;

	std::list<Bird*> birds; // Front is active / flying
	PxScene* gScene = nullptr;
	RBSystem* rbSystem;

public:

	LevelManager(PxScene* gScene, RBSystem* rbSystem);
	~LevelManager();

	void clearBlocks();
	void startLevel(int level);

	Bird* getActiveBird() { return birds.front(); };
	void nextBird() { birds.pop_front(); };

	void addObject(AngryBirdsObject* obj);

protected:

	void setupLevel1();
	void setupLevel2();
	void setupLevel3();

};

