#pragma once

#include "RenderUtils.hpp"

class Plane
{
	physx::PxTransform pos;
	RenderItem* renderItem;

public:
	Plane(Vector3 Pos);
	~Plane();
	void update(double t);
};

