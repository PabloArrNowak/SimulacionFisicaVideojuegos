#include "ParticleForceRegistry.h"
#include "ForceGenerator.h"

ParticleForceRegistry::ParticleForceRegistry()
{
}

ParticleForceRegistry::~ParticleForceRegistry()
{
}

void ParticleForceRegistry::update(double duration)
{
	for (auto it = begin(); it != end(); it++) {
		it->first->updateForce(it->second, duration);
	}
}

void ParticleForceRegistry::deleteParticle(Particle* p)
{
	for (auto it = begin(); it != end();) {
		if (it->second == p)
			it = erase(it);
		else it++;
	}
}
