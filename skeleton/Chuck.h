#pragma once

#include "Bird.h"

class Chuck : public Bird
{
protected:

public:

	Chuck(LevelManager* lvlMngr, Vector3 pos);
	~Chuck();

	void activatePower() override;
};

