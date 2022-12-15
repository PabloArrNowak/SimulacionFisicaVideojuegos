#pragma once

#include "core.hpp"
#include "AngryBirdsObject.h"

class GroundBlock : public AngryBirdsObject
{
protected:

	Vector3 dimensions;
	physx::PxRigidStatic* rb;

public:

	GroundBlock(Vector3 pos, Vector3 size);
	~GroundBlock();

	physx::PxActor* getRB() override { return rb; };

	Vector3 getPos() override {
		return Vector3(rb->getGlobalPose().p);
	}
};

