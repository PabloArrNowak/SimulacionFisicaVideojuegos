#include "WindRBForceGenerator.h"
#include "AngryBirdsObject.h"
#include <iostream>
using namespace physx;

WindRBForceGenerator::WindRBForceGenerator(const Vector3& dir, Vector3 areaCubeCenter, Vector3 areaCubeDimensions) : RBForceGenerator(true), areaCenter(areaCubeCenter), areaDimensions(areaCubeDimensions)
{
    setWindDir(dir);
}

WindRBForceGenerator::~WindRBForceGenerator()
{
}

void WindRBForceGenerator::updateForce(AngryBirdsObject* obj, double t)
{
    if (!obj->getRB()->is<PxRigidDynamic>())
        return;

    Vector3 partVel = static_cast<PxRigidDynamic*>(obj->getRB())->getLinearVelocity();
    Vector3 windVel = getWindVel(obj);

    // Con k1 = 0.4 y k2 = 0.01
    Vector3 f = 0.005 * (windVel - partVel) + 0.0007 * (windVel - partVel).magnitude() * (windVel - partVel);
    if (windVel != Vector3(0, 0, 0))
        obj->addForce(Vector3(0, f.y, 0));
}

Vector3 WindRBForceGenerator::getWindVel(AngryBirdsObject* particle)
{
    Vector3 objPos = static_cast<PxRigidDynamic*>(particle->getRB())->getGlobalPose().p;

    bool insideX = objPos.x < areaCenter.x + areaDimensions.x / 2 && objPos.x > areaCenter.x - areaDimensions.x / 2;
    bool insideY = objPos.y < areaCenter.y + areaDimensions.y / 2 && objPos.y > areaCenter.y - areaDimensions.y / 2;
    bool insideZ = objPos.z < areaCenter.z + areaDimensions.z / 2 && objPos.z > areaCenter.z - areaDimensions.z / 2;

    if (insideX && insideY && insideZ)
        return windDirection;

    return { 0, 0, 0 };
}
