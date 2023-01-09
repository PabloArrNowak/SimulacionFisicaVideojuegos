#pragma once

#include "Bird.h"

class Red : public Bird
{
protected:

public:

	Red(LevelManager* lvlMngr, Vector3 pos);
	~Red();

	void activatePower() override;
};

