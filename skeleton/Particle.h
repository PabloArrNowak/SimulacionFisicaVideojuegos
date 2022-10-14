#pragma once

#include "RenderUtils.hpp"

class Particle
{
protected:
	Vector3 vel, acc;
	double damping;
	float invMass;
	physx::PxTransform pos;
	RenderItem* renderItem;

	float timeLeft;
	bool alive;
	// ParticleType type;

public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping, float Mass, float lifeTime);
	Particle(Particle* other, Vector3 newPos, Vector3 newVel, Vector3 newAcc, float newLifeTime);
	~Particle();
	virtual bool update(double t);

	bool getAlive() {
		return alive;
	}
};

