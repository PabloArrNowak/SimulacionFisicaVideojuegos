#include "TornadoAreaForceGenerator.h"
#include "Particle.h"

TornadoAreaForceGenerator::TornadoAreaForceGenerator(double forceK, Vector3 areaCubeCenter, Vector3 areaCubeDimensions) : WindAreaForceGenerator(Vector3(forceK, 0, 0), areaCubeCenter, areaCubeDimensions),
	K(forceK)
{
}

TornadoAreaForceGenerator::~TornadoAreaForceGenerator()
{
}

void TornadoAreaForceGenerator::updateForce(Particle* particle, double t)
{
	if (fabs(particle->getInvMass()) < 1e-10)
		return;

	bool insideX = particle->getPos().x < areaCenter.x + areaDimensions.x / 2 && particle->getPos().x > areaCenter.x - areaDimensions.x / 2;
	bool insideY = particle->getPos().y < areaCenter.y + areaDimensions.y / 2 && particle->getPos().y > areaCenter.y - areaDimensions.y / 2;
	bool insideZ = particle->getPos().z < areaCenter.z + areaDimensions.z / 2 && particle->getPos().z > areaCenter.z - areaDimensions.z / 2;

	if (!insideX || !insideY || !insideZ)
		return;

	// Con k1 = 0.4 y k2 = 0.01
	// Vector3 f = 0.4 * (getWindVel(particle) - particle->getVel()) + 0.01 * Vector3(getWindVel(particle) - particle->getVel()).magnitude() * (getWindVel(particle) - particle->getVel());
	
	Vector3 f = K * Vector3(-(particle->getPos().z - areaCenter.z), 20 - (particle->getPos().y - areaCenter.y), particle->getPos().x - areaCenter.x);
	// Vector3 f = K * Vector3(-(particle->getPos().z - areaCenter.z), 0, particle->getPos().x - areaCenter.x);
	
	particle->addForce(f);
}