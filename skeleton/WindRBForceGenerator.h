#pragma once

#include "RBForceGenerator.h"
#include "core.hpp"

class WindRBForceGenerator : public RBForceGenerator
{
protected:
    Vector3 windDirection;
    Vector3 areaCenter;
    Vector3 areaDimensions;

public:

    WindRBForceGenerator(const Vector3& dir, Vector3 areaCubeCenter, Vector3 areaCubeDimensions);
    ~WindRBForceGenerator();

    virtual void updateForce(AngryBirdsObject* particle, double t) override;
    virtual Vector3 getWindVel(AngryBirdsObject* particle);

    inline void setWindDir(Vector3 dir) { windDirection = dir; };
};

