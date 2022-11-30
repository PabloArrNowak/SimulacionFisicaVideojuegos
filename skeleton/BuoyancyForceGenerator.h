#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class BuoyancyForceGenerator : public ForceGenerator
{
protected:

	double height, volume, liquidDensity; 
	double gravity = 9.8;

	Particle* liquidParticle;

public:

	BuoyancyForceGenerator(double h, double V, double d);
	~BuoyancyForceGenerator();

	virtual void updateForce(Particle* particle, double t) override;


};

