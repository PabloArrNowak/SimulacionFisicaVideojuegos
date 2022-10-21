#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(Vector3 pos, Vector3 vel, double iMass)
{
	meanPos = pos;
	meanVel = vel;
}

ParticleGenerator::~ParticleGenerator()
{
}

void ParticleGenerator::setParticle(Particle* model)
{
	// delete modelPart;
	modelPart = model;
}

std::string ParticleGenerator::getName()
{
	return name;
}
