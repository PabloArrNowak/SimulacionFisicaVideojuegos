#include "BuoyancyForceGenerator.h"
#include "Particle.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(double h, double V, double d) : ForceGenerator(true),
height(h), volume(V), liquidDensity(d),
liquidParticle(new Particle({ 0, (float)h, -10 }, { 0, 0, 0 }, { 0, 0, 0 }, 0.998, 999999, -1, { 0, 0, 1, 1}, 0.5))
{
}

BuoyancyForceGenerator::~BuoyancyForceGenerator()
{
}

void BuoyancyForceGenerator::updateForce(Particle* particle, double t)
{
	double h = particle->getPos().y;
	double h0 = liquidParticle->getPos().y;

	Vector3 f(0, 0, 0);
	double immersed = 0.0;

	if (h - h0 > height * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h > height * 0.5) {
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / height + 0.5;
	}

	f.y = liquidDensity * volume * immersed * gravity;

	particle->addForce(f);
}
