#pragma once
#include "ParticleGenerator.h"
#include "RenderUtils.hpp"
#include <list>

class SimpleParticleGenerator : public ParticleGenerator
{
	Vector3 velWidth, posWidth;

public:
	SimpleParticleGenerator(Vector3 pos, Vector3 vel, double iMass);
	virtual std::list<Particle*> generateParticles();
};

