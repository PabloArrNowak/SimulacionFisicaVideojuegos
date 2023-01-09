#pragma once

#include "Bird.h"

class Bomb : public Bird	// No implementado, habría que cambiar como se gestionan todas las explosiones y no da tiempo rn
{
protected:

public:

	Bomb(LevelManager* lvlMngr, Vector3 pos);
	~Bomb();

	void activatePower() override;
};

