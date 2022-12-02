#pragma once

#include "core.hpp"
#include "AngryBirdsObject.h"

class BuildingBlock : AngryBirdsObject
{

protected:

	blockMat material;
	Vector3 dimensions;
	physx::PxRigidDynamic* rb;

public:

	BuildingBlock(Vector3 pos, Vector3 size, blockMat bMaterial, int hp);
	~BuildingBlock();

};

