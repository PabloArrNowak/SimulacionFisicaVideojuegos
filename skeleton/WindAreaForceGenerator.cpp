#include "WindAreaForceGenerator.h"
#include "Particle.h"

WindAreaForceGenerator::WindAreaForceGenerator(const Vector3& dir, Vector3 areaCubeCenter, Vector3 areaCubeDimensions) : WindForceGenerator(dir), areaCenter(areaCubeCenter), areaDimensions(areaCubeDimensions)
{
}

WindAreaForceGenerator::~WindAreaForceGenerator()
{
}

void WindAreaForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInvMass()) < 1e-10)
		return;

	// Con k1 = 0.4 y k2 = 0.01
	Vector3 f = 0.4 * (getWindVel(particle) - particle->getVel()) + 0.01 * Vector3(getWindVel(particle) - particle->getVel()).magnitude() * (getWindVel(particle) - particle->getVel());
	particle->addForce(f);
}

Vector3 WindAreaForceGenerator::getWindVel(Particle* particle)
{
	bool insideX = particle->getPos().x < areaCenter.x + areaDimensions.x / 2 && particle->getPos().x > areaCenter.x - areaDimensions.x / 2;
	bool insideY = particle->getPos().y < areaCenter.y + areaDimensions.y / 2 && particle->getPos().y > areaCenter.y - areaDimensions.y / 2;
	bool insideZ = particle->getPos().z < areaCenter.z + areaDimensions.z / 2 && particle->getPos().z > areaCenter.z - areaDimensions.z / 2;

	if (insideX && insideY && insideZ)
		return windDirection;

	return { 0, 0, 0 };
}
