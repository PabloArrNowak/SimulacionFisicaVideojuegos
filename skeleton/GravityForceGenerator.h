#pragma once

#include "ForceGenerator.h"
#include "core.hpp"

class GravityForceGenerator : public ForceGenerator
{
protected:
	Vector3 gravity;

public:

	GravityForceGenerator(const Vector3& g);
	~GravityForceGenerator();

	virtual void updateForce(Particle* particle, double t) override;

	inline void setGravity(Vector3 g) { gravity = g; };

};

