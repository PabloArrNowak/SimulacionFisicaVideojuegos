#include "WindForceGenerator.h"
#include "Particle.h"

WindForceGenerator::WindForceGenerator(const Vector3& dir) : ForceGenerator(true)
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

	// Con k1 = 1 y k2 = 0
	 Vector3 f = 0.4 * (windDirection - particle->getVel()) + 0.01 * Vector3(windDirection - particle->getVel()).magnitude() * (windDirection - particle->getVel());
	 particle->addForce(f);
}
