#pragma once

#include<PxPhysicsAPI.h>
#include <list>
using namespace physx;

class Bird;

class LevelManager
{
	std::list<Bird*> birds; // Front is active / flying
	PxScene* gScene = nullptr;

public:

	LevelManager(PxScene* gScene);
	~LevelManager();

	void clearBlocks();
	void startLevel(int level);

	Bird* getActiveBird() { return birds.front(); };
	void nextBird() { birds.pop_front(); };

protected:

	void setupLevel1();
	void setupLevel2();
	void setupLevel3();

};

