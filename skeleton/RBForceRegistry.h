#pragma once
#include <string>
#include <map>

using namespace std;

class AngryBirdsObject;
class RBForceGenerator;

typedef std::pair<RBForceGenerator*, AngryBirdsObject*> FObjPair;


class RBForceRegistry : public std::multimap<RBForceGenerator*, AngryBirdsObject*>
{

protected:

	string name;

public:

	RBForceRegistry();
	~RBForceRegistry();

	void update(double duration);
	void addRegistry(RBForceGenerator* fg, AngryBirdsObject* obj);
	void deleteForce(RBForceGenerator* fg);
	void deleteObj(AngryBirdsObject* obj);

};

