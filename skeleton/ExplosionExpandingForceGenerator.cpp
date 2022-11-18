#include "ExplosionExpandingForceGenerator.h"

ExplosionExpandingForceGenerator::ExplosionExpandingForceGenerator(const Vector3& areaCenter, double areaRadius, double K, double timeK, double radiusVel) : 
	ExplosionForceGenerator(areaCenter, areaRadius, K, timeK),
	radiusVel(radiusVel)
{
}

ExplosionExpandingForceGenerator::~ExplosionExpandingForceGenerator()
{
}

void ExplosionExpandingForceGenerator::updateGenerator(double t)
{
	timeSinceActivation += t;
	areaRadius += radiusVel * t;
}
