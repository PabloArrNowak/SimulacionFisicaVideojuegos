#pragma once

#include "Bird.h"

class Bomb : public Bird
{
protected:

public:

	Bomb(LevelManager* lvlMngr, Vector3 pos);
	~Bomb();

	void activatePower() override;
};

