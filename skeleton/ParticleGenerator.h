#pragma once
#include <string>
#include "RenderUtils.hpp"
#include <list>

class Particle;

class ParticleGenerator
{
	std::string name;
	Vector3 meanPos, meanVel;
	double generationProb;
	int numParticles;
	Particle* modelPart;

public:

	ParticleGenerator();
	~ParticleGenerator();

	void setParticle(Particle* model);
	virtual std::list<Particle*> generateParticles() = 0;
};

