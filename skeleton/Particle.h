#pragma once

#include "RenderUtils.hpp"

class Particle
{
	Vector3 vel, acc;
	double damping;
	physx::PxTransform pos;
	RenderItem* renderItem;

public:
	// Params: Pos, Vel, Acc, damping
	// vel, acc, damping = params
	// renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0)), &pose, { 0.5, 0, 0.5, 1 });
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping);
	~Particle();
	void update(double t);
};

