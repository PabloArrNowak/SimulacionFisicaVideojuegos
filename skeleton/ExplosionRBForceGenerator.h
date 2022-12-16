#pragma once

#include "RBForceGenerator.h"
#include "core.hpp"

class ExplosionRBForceGenerator : public RBForceGenerator
{
protected:
	Vector3 areaCenter;
	double areaRadius;
	double K;
	double timeK;
	double timeSinceActivation;

public:

	ExplosionRBForceGenerator(const Vector3& areaCenter, double areaRadius, double K, double timeK);
	~ExplosionRBForceGenerator();

	virtual void updateGenerator(double t);
	virtual void updateForce(AngryBirdsObject* particle, double t) override;
	virtual Vector3 getExplosionDir(AngryBirdsObject* particle, float& mod);

	double getTimeSinceActivation() { return timeSinceActivation; };

};

