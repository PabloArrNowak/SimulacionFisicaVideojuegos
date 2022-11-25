#pragma once
#include <string>
#include "RenderUtils.hpp"
#include <list>
#include <random>

using namespace std;

class Particle;

class ForceGenerator
{
protected:
	string name;
	bool affectsAll = true;

	//random_device rnd;
	//default_random_engine generator = std::default_random_engine(rnd());

public:

	ForceGenerator(bool affectsAll);
	~ForceGenerator();

	virtual void updateForce(Particle* p, double t) = 0;
	bool getAffectsAll() { return affectsAll; };
};

