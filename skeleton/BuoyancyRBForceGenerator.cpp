#include "BuoyancyRBForceGenerator.h"
#include "AngryBirdsObject.h"
#include "Particle.h"

BuoyancyRBForceGenerator::BuoyancyRBForceGenerator(double h, double V, double d, Vector3 center, double width, double depth) : RBForceGenerator(true),
height(h), volume(V), liquidDensity(d), areaCenter(center), areaDimensions(Vector3(width, h, depth)),
liquidParticle(new Particle({ 0, (float)h, 0 }, { 0, 0, 0 }, { 0, 0, 0 }, 0.998, 999999, -1, { 0, 0, 1, 1 }, 0.5))
{
}

BuoyancyRBForceGenerator::~BuoyancyRBForceGenerator()
{
}

void BuoyancyRBForceGenerator::updateForce(AngryBirdsObject* obj, double t)
{
	if (obj->getPos().x > areaCenter.x + areaDimensions.x / 2 || obj->getPos().x < areaCenter.x - areaDimensions.x / 2 ||
		obj->getPos().z > areaCenter.z + areaDimensions.z / 2 || obj->getPos().z < areaCenter.z - areaDimensions.z / 2)
		return;

	double h = obj->getPos().y;
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

	obj->addForce(f / 1000);
}
