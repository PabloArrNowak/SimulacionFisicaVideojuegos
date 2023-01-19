#pragma once

#include "RBForceGenerator.h"
#include "core.hpp"

class Particle;

class BuoyancyRBForceGenerator : public RBForceGenerator
{
protected:

	double height, volume, liquidDensity;
	double gravity = 10.0;

	Vector3 areaCenter, areaDimensions;

	Particle* liquidParticle;

public:

    BuoyancyRBForceGenerator(double h, double V, double d, Vector3 center, double width, double depth);
    ~BuoyancyRBForceGenerator();

    virtual void updateForce(AngryBirdsObject* obj, double t) override;
};

