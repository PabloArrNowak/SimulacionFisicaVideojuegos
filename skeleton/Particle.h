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
	~Particle();
	virtual void update(double t);
	virtual Particle* clone() const;

	bool getAlive() {
		return alive;
	}
};

