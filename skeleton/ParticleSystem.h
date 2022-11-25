#pragma once

#include "RenderUtils.hpp"
#include "ParticleForceRegistry.h"
#include <list>
#include <string>

class Particle;
class ParticleGenerator;
class Firework;
class FireworkRule;
class ForceGenerator;

class ParticleSystem
{
protected:
	std::list<Particle*> particles;
	std::list<ParticleGenerator*> particleGenerators;
	Vector3 gravity;

	std::vector<FireworkRule*> _firework_rules;
	std::list<Firework*> fireworks;
	unsigned _curr_t;

	ParticleForceRegistry partForceRegistry;
	std::list<ForceGenerator*> forceGenerators;

public:

	ParticleSystem();

	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);

	void generateFireworkSystem();
	void generateFirework(unsigned type, const Vector3& pos, const Vector3& vel);
	FireworkRule* getFireworkRule(unsigned type) { return _firework_rules[type]; };

	void fireworksUpdate(double t);

	void setGenerator(ParticleGenerator* gen);
	void resetParticles();

	void addForceGen(ForceGenerator* gen) { forceGenerators.push_back(gen); };
	void removeForceGen(ForceGenerator* gen) { forceGenerators.remove(gen); };

	void addToPartFRegistry(Particle* part, ForceGenerator* f) { partForceRegistry.addRegistry(f, part); };

	void createSpring(Particle* p1, Particle* p2, double restingLength, double springK);
	void createAnchoredSpring(Particle* p1, const Vector3& anchorPos, double restingLength, double springK);
	void createSlinky(int joints, double springK, double restingTotalLength, Particle* partTemplate, Vector3 anchorPos);

};

