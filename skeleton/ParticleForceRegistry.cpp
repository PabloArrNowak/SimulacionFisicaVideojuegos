#include "ParticleForceRegistry.h"
#include "ForceGenerator.h"

ParticleForceRegistry::ParticleForceRegistry() : std::multimap<ForceGenerator*, Particle*>()
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

void ParticleForceRegistry::addRegistry(ForceGenerator* fg, Particle* p)
{
	insert(FRPair(fg, p));
}

void ParticleForceRegistry::deleteForce(ForceGenerator* fg)
{
	for (auto it = begin(); it != end();) {
		if (it->first == fg)
			it = erase(it);
		else it++;
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
