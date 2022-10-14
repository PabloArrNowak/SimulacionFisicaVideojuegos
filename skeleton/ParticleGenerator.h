#pragma once
#include <string>
#include "RenderUtils.hpp"
#include <list>
#include <random>

using namespace std;

class Particle;

class ParticleGenerator
{
protected:
	string name;
	Vector3 meanPos, meanVel;
	double generationProb;
	int numParticles;
	Particle* modelPart;

	random_device rnd;
	default_random_engine generator = std::default_random_engine(rnd());

public:

	ParticleGenerator(Vector3 pos, Vector3 vel, double iMass);
	~ParticleGenerator();

	void setParticle(Particle* model);
	virtual std::list<Particle*> generateParticles() = 0;

	string getName();
	void setOrigin(const Vector3& o) { meanPos = o; };
	void setMeanVel(const Vector3& v) { meanVel = v; };
	Vector3 getMeanVel() { return meanVel; };
};

