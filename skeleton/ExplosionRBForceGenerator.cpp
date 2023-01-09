#include "ExplosionRBForceGenerator.h"
#include "AngryBirdsObject.h"
#include <iostream>

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
    float dirMod;
    Vector3 f = K / (areaRadius * areaRadius) * getExplosionDir(obj, dirMod) * exp(-timeSinceActivation / timeK);
    if (dirMod * dirMod < 1e-7) {
        dirMod = 10e5;
    }
    else {
        dirMod = 1 / (dirMod * dirMod);
        std::cout << f.x << " " << f.y << " " << f.z << endl;
    }
    std::cout << dirMod << endl;
    obj->addForce(f * dirMod);

    // obj->addForce({ 10e5, 0, 0 });
}

Vector3 ExplosionRBForceGenerator::getExplosionDir(AngryBirdsObject* obj, float& mod)
{
    Vector3 centerToPart = { obj->getPos().x - areaCenter.x, obj->getPos().y - areaCenter.y, obj->getPos().z - areaCenter.z };

    if (centerToPart.magnitude() <= areaRadius) {

        if (centerToPart.magnitudeSquared() < 1) {
            mod = 999999;
            return { 9999, 9999, 9999 };
        }

        mod = centerToPart.normalize();
        return centerToPart;
    }

    mod = 0;
    return { 0, 0, 0 };
}
