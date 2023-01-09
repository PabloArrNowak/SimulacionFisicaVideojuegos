#pragma once

#include "Bird.h"

class Blues : public Bird
{
protected:

	float velMultiplier = 0.1;

public:

	Blues(LevelManager* lvlMngr, Vector3 pos);
	~Blues();

	void activatePower() override;
};

