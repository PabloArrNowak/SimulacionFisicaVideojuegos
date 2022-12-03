#include "LevelManager.h"

LevelManager::LevelManager(PxScene* gScene)
{
	this->gScene = gScene;
}

LevelManager::~LevelManager()
{
}

void LevelManager::startLevel(int level)
{
	clearBlocks();

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

}

void LevelManager::setupLevel1()
{

}

void LevelManager::setupLevel2()
{

}

void LevelManager::setupLevel3()
{

}