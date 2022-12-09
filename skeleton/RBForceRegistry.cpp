#include "RBForceRegistry.h"
#include "RBForceGenerator.h"

RBForceRegistry::RBForceRegistry()
{
}

RBForceRegistry::~RBForceRegistry()
{
}

void RBForceRegistry::update(double duration)
{
	for (auto it = begin(); it != end(); it++) {
		it->first->updateForce(it->second, duration);
	}
}

void RBForceRegistry::addRegistry(RBForceGenerator* fg, AngryBirdsObject* obj)
{
	insert(FObjPair(fg, obj));
}

void RBForceRegistry::deleteForce(RBForceGenerator* fg)
{
	for (auto it = begin(); it != end();) {
		if (it->first == fg)
			it = erase(it);
		else it++;
	}
}

void RBForceRegistry::deleteObj(AngryBirdsObject* obj)
{
	for (auto it = begin(); it != end();) {
		if (it->second == obj)
			it = erase(it);
		else it++;
	}
}
