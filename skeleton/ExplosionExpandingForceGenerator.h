#pragma once

#include "ExplosionForceGenerator.h"
#include "core.hpp"

class ExplosionExpandingForceGenerator : public ExplosionForceGenerator
{
protected:
	double radiusVel;

public:

	ExplosionExpandingForceGenerator(const Vector3& areaCenter, double areaRadius, double K, double timeK, double radiusVel);
	~ExplosionExpandingForceGenerator();

	virtual void updateGenerator(double t) override;
};

