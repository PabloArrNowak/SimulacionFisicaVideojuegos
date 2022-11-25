#include "SpringForceGenerator.h"
#include "Particle.h"

SpringForceGenerator::SpringForceGenerator(double K, double restingLength, Particle* other) : ForceGenerator(false),
	springK(K), restingSpringLength(restingLength), other(other)
{
}

SpringForceGenerator::~SpringForceGenerator()
{
	delete other;
}

void SpringForceGenerator::updateForce(Particle* particle, double t)
{
	Vector3 fDir = particle->getPos() - other->getPos();
	double length = fDir.normalize();
	double lengthDiff = length - restingSpringLength;

	fDir *= lengthDiff * springK;

	Vector3 f = -springK * (fDir.magnitude() - restingSpringLength) * (fDir / fDir.magnitude());
	particle->addForce(f);
}
