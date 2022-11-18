#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class ExplosionForceGenerator : public ForceGenerator
{
protected:
	Vector3 areaCenter;
	double areaRadius;
	double K;
	double timeK;
	double timeSinceActivation;

public:

	ExplosionForceGenerator(const Vector3& areaCenter, double areaRadius, double K, double timeK);
	~ExplosionForceGenerator();

	virtual void updateGenerator(double t);
	virtual void updateForce(Particle* particle, double t) override;
	virtual Vector3 getExplosionDir(Particle* particle);

	double getTimeSinceActivation() { return timeSinceActivation; };

};

