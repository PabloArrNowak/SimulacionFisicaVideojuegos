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

	//random_device rnd;
	//default_random_engine generator = std::default_random_engine(rnd());

public:

	ForceGenerator();
	~ForceGenerator();

	virtual void updateForce(Particle* p, float t) = 0;
};

