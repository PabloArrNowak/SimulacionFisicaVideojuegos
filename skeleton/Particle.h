#pragma once

#include "RenderUtils.hpp"
#include <list>

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

	Vector3 totalForce;


public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping, float Mass, float lifeTime, Vector4 color, float radius);
	Particle(Particle* other, Vector3 newPos, Vector3 newVel, Vector3 newAcc, float newLifeTime);
	~Particle();
	virtual bool update(double t);
	virtual std::list<Particle*> onDeath() { return std::list<Particle*>(); };

	bool getAlive() {
		return alive;
	}
	double getInvMass() {
		return invMass;
	}

	Vector3 getVel() {
		return vel;
	}

	Vector3 getPos() {
		return pos.p;
	}

	void resetForces();
	void addForce(const Vector3& force);
};

