#pragma once
#include <string>
#include <map>

using namespace std;

class Particle;
class ForceGenerator;

typedef std::pair<ForceGenerator*, Particle*> FRPair;


class ParticleForceRegistry : public std::multimap<ForceGenerator*, Particle*>
{
protected:
	string name;

	//random_device rnd;
	//default_random_engine generator = std::default_random_engine(rnd());

public:

	ParticleForceRegistry();
	~ParticleForceRegistry();

	void update(double duration);
	void addRegistry(ForceGenerator* fg, Particle* p);
	void deleteForce(ForceGenerator* fg);
	void deleteParticle(Particle* p);

};

