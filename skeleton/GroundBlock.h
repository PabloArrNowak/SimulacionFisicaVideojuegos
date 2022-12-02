#pragma once

#include "core.hpp"
#include "AngryBirdsObject.h"

class GroundBlock : AngryBirdsObject
{
protected:

	Vector3 dimensions;
	physx::PxRigidStatic* rb;

public:

	GroundBlock(Vector3 pos, Vector3 size);
	~GroundBlock();

};

