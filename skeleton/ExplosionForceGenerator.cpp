#include "ExplosionForceGenerator.h"
#include "Particle.h"

ExplosionForceGenerator::ExplosionForceGenerator(const Vector3& areaCenter, double areaRadius, double K, double timeK)
{
	this->areaCenter = areaCenter;
	this->areaRadius = areaRadius;
	this->K = K;
	this->timeK = timeK;
	timeSinceActivation = 0;
}

ExplosionForceGenerator::~ExplosionForceGenerator()
{
}

void ExplosionForceGenerator::updateGenerator(double t)
{
	timeSinceActivation += t;
}

void ExplosionForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInvMass()) < 1e-10)
		return;

	Vector3 f = K / (areaRadius * areaRadius) * getExplosionDir(particle) * pow(std::_Exp1, (-timeSinceActivation / timeK));
	particle->addForce(f);
}

Vector3 ExplosionForceGenerator::getExplosionDir(Particle* particle)
{
	Vector3 centerToPart = { particle->getPos().x - areaCenter.x, particle->getPos().y - areaCenter.y, particle->getPos().z - areaCenter.z };

	if (centerToPart.magnitude() <= areaRadius)
		return centerToPart;

	return { 0, 0, 0 };
}
