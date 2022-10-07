#pragma once

#include "RenderUtils.hpp"

class Particle
{
protected:
	Vector3 vel, acc;
	double damping;
	float mass; // Cambiar a inverso de la masa
	physx::PxTransform pos;
	RenderItem* renderItem;

	float timeLeft;
	ParticleType type;

public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, float Mass);
	~Particle();
	virtual void update(double t);
	virtual Particle* clone() const;
};

