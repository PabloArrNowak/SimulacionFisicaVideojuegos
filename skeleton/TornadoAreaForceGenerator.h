#pragma once

#include "WindAreaForceGenerator.h"
#include "core.hpp"

class TornadoAreaForceGenerator : public WindAreaForceGenerator
{
protected:
	double K;

public:

	TornadoAreaForceGenerator(double forceK, Vector3 areaCubeCenter, Vector3 areaCubeDimensions);
	~TornadoAreaForceGenerator();

	virtual void updateForce(Particle* particle, double t) override;

};

