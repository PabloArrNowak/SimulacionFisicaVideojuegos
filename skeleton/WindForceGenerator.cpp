#include "WindForceGenerator.h"
#include "Particle.h"

WindForceGenerator::WindForceGenerator(const Vector3& dir)
{
	setWindDir(dir);
}

WindForceGenerator::~WindForceGenerator()
{
}

void WindForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInvMass()) < 1e-10)
		return;

	// k1 & k2 ??
	// Vector3 f = k1 * (windDirection - particle->getVel()) + k2 * Vector3(windDirection - particle->getVel()).magnitude() * (windDirection - particle->getVel());
	// particle->addForce(f);
}
