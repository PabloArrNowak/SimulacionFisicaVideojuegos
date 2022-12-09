#pragma once
#include <string>
#include "RenderUtils.hpp"
#include <list>
#include <random>

using namespace std;

class AngryBirdsObject;

class RBForceGenerator
{
protected:
	string name;
	bool affectsAll = true;

	//random_device rnd;
	//default_random_engine generator = std::default_random_engine(rnd());

public:

	RBForceGenerator(bool affectsAll);
	~RBForceGenerator();

	virtual void updateForce(AngryBirdsObject* obj, double t) = 0;
	bool getAffectsAll() { return affectsAll; };
};

