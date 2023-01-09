#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class WindForceGenerator : public ForceGenerator
{
protected:
    Vector3 windDirection;

public:

    WindForceGenerator(const Vector3& dir);
    ~WindForceGenerator();

    virtual void updateForce(Particle* particle, double t) override;

    inline void setWindDir(Vector3 dir) { windDirection = dir; };

};

