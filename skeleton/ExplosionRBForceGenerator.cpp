#include "ExplosionRBForceGenerator.h"
#include "AngryBirdsObject.h"

ExplosionRBForceGenerator::ExplosionRBForceGenerator(const Vector3& areaCenter, double areaRadius, double K, double timeK) : RBForceGenerator(true)
{
	this->areaCenter = areaCenter;
	this->areaRadius = areaRadius;
	this->K = K;
	this->timeK = timeK;
	timeSinceActivation = 0;
}

ExplosionRBForceGenerator::~ExplosionRBForceGenerator()
{
}

void ExplosionRBForceGenerator::updateGenerator(double t)
{
	timeSinceActivation += t;
}

void ExplosionRBForceGenerator::updateForce(AngryBirdsObject* obj, double t)
{
	// Usar funcion especifica de e
	Vector3 f = K / (areaRadius * areaRadius) * getExplosionDir(obj) * pow(std::_Exp1, (-timeSinceActivation / timeK));
	obj->addForce(f);
}

Vector3 ExplosionRBForceGenerator::getExplosionDir(AngryBirdsObject* obj)
{
	Vector3 centerToPart = { obj->getPos().x - areaCenter.x, obj->getPos().y - areaCenter.y, obj->getPos().z - areaCenter.z };

	if (centerToPart.magnitude() <= areaRadius)
		return centerToPart;

	return { 0, 0, 0 };
}
