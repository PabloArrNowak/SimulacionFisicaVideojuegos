#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class SpringForceGenerator : public ForceGenerator
{
protected:

	double springK;
	double restingSpringLength;
	Particle* other;

public:

	SpringForceGenerator(double K, double restingLength, Particle* other);
	~SpringForceGenerator();

	virtual void updateForce(Particle* particle, double t) override;


};

