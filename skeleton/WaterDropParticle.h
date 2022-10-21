#pragma once

#include "Particle.h"


class WaterDropParticle : public Particle
{

public:
	WaterDropParticle(float radius, float Mass) : Particle(Vector3(), Vector3(), Vector3(), 0.998, Mass, 1.0, {0, 0.5, 0.5, 1}, radius) {

	}
	~WaterDropParticle() {

	}
	// virtual void update(double t) override;
};

