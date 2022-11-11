#pragma once

#include "Particle.h"


class BallParticle : public Particle
{

public:
	BallParticle(float radius, float Mass) : Particle(Vector3(), Vector3(), Vector3(), 0.998, Mass, 8.0, { 0, 0.8, 0.2, 1 }, radius) {

	}
	~BallParticle() {

	}
	// virtual void update(double t) override;
};

