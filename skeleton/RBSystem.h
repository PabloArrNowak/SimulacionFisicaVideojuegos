#pragma once

#include "RenderUtils.hpp"
#include "RBForceRegistry.h"
#include <list>
#include <string>
#include "RBForceGenerator.h"
#include "LevelManager.h"

class Particle;
class ParticleGenerator;
class Firework;
class FireworkRule;
class ForceGenerator;
class AngryBirdsObject;

class RBSystem
{
protected:
	std::list<AngryBirdsObject*> sceneObjects;
	std::list<ParticleGenerator*> rbGenerators;

	unsigned _curr_t;

	RBForceRegistry rbForceRegistry;
	std::list<RBForceGenerator*> forceGenerators;

	LevelManager* levelM;

public:

	RBSystem();
	void setLevelManager(LevelManager* lvlMngr);

	void update(double t);
	ParticleGenerator* getParticleGenerator(std::string name);

	void setGenerator(ParticleGenerator* gen);
	void resetParticles();

	std::list<RBForceGenerator*> getForceGenerators() { return forceGenerators; };

	void addForceGen(RBForceGenerator* gen) {
		forceGenerators.push_back(gen);
		if (gen->getAffectsAll()) {
			for (auto obj : levelM->getSceneObjects()) {
				addToRegistry(obj, gen);
			}
		}
	};

	void removeForceGen(RBForceGenerator* gen) { forceGenerators.remove(gen); };

	void addToRegistry(AngryBirdsObject* obj, RBForceGenerator* f) { rbForceRegistry.addRegistry(f, obj); };

	void createSpring(AngryBirdsObject* p1, AngryBirdsObject* p2, double restingLength, double springK);
	void createAnchoredSpring(AngryBirdsObject* p1, const Vector3& anchorPos, double restingLength, double springK);
	void createSlinky(int joints, double springK, double restingTotalLength, AngryBirdsObject* partTemplate, Vector3 anchorPos);

};
