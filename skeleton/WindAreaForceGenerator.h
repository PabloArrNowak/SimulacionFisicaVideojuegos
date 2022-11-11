#pragma once

#include "WindForceGenerator.h"
#include "core.hpp"

class WindAreaForceGenerator : public WindForceGenerator
{
protected:
	Vector3 areaCenter;
	Vector3 areaDimensions;

public:

	WindAreaForceGenerator(const Vector3& dir, Vector3 areaCubeCenter, Vector3 areaCubeDimensions);
	~WindAreaForceGenerator();

	virtual void updateForce(Particle* particle, double t) override;
	virtual Vector3 getWindVel(Particle* particle);

};

