#pragma once

#include "RenderUtils.hpp"
#include <list>
#include <string>

class Particle;
class ParticleGenerator;

class ParticleSystem
{
protected:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGenerators;
	Vector3 gravity;

public:

	ParticleSystem();

	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void generateFireworkSystem();

	void setGenerator(ParticleGenerator* gen);

};

