#pragma once

#include "Particle.h"


class Projectile : public Particle
{

public:
	Projectile(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, float Mass);
	~Projectile();
	// virtual void update(double t) override;
};

