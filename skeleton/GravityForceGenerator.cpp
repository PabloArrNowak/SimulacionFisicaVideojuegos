#include "GravityForceGenerator.h"
#include "Particle.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g) : ForceGenerator(true)
{
	setGravity(g);
}

GravityForceGenerator::~GravityForceGenerator()
{
}

void GravityForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInvMass()) < 1e-10)
		return;

	particle->addForce(gravity / particle->getInvMass());
}
