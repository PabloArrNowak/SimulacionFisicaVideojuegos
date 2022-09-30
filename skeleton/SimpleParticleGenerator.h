#pragma once
#include "ParticleGenerator.h"
#include <list>
class Particle;
class Vector3;

class SimpleParticleGenerator : public ParticleGenerator
{
public:
	SimpleParticleGenerator(Vector3 pos, Vector3 vel, double iMass);
	virtual std::list<Particle*> generateParticles();
};

