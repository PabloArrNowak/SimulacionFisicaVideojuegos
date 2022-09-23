#pragma once

#include "RenderUtils.hpp"

class Particle
{
	Vector3 vel, acc;
	double damping;
	float mass; // Cambiar a inverso de la masa
	physx::PxTransform pos;
	RenderItem* renderItem;

public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, float Mass);
	~Particle();
	void update(double t);
};

