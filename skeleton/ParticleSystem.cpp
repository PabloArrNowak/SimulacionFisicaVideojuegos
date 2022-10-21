#include "ParticleSystem.h"
#include "Particle.h"
#include "ParticleGenerator.h"

ParticleSystem::ParticleSystem()
{
	particles = list<Particle*>();
	particleGenerators = list<ParticleGenerator*>();
}

void ParticleSystem::update(double t)
{
	for (auto it = particles.begin(); it != particles.end();) {
		if (!(*it)->update(t)) {
			Particle* del = *it;
			it = particles.erase(it);
			delete del;
		}
		else it++;
	}

	for (ParticleGenerator* gen : particleGenerators) {
	
		auto parts = gen->generateParticles();
		for (Particle* part : parts) {
			particles.push_back(part);
		}

	}
}

ParticleGenerator* ParticleSystem::getParticleGenerator(std::string name)
{
	ParticleGenerator* ret = nullptr;
	for (ParticleGenerator* gen : particleGenerators) {
		if (gen->getName() == name) {
			ret = gen;
			break;
		}
	}

	return ret;
}

void ParticleSystem::generateFireworkSystem()
{
}

void ParticleSystem::setGenerator(ParticleGenerator* gen)
{
	if (!particleGenerators.empty())
		particleGenerators.erase(particleGenerators.begin());

	particleGenerators.push_back(gen);
}
