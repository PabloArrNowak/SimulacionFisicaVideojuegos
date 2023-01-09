#pragma once

#include "Particle.h"
#include <random>


struct Payload {

	unsigned type;
	unsigned count;

	Payload(unsigned _type, unsigned _count) {
		type = _type;
		count = _count;
	}

	void set(unsigned _type, unsigned _count) {
		type = _type;
		count = _count;
	}
};


struct FireworkRule {

	unsigned _type;
	float _meanAge;
	float _stdDevAge;

	Vector3 _meanVelocity;
	Vector3 _stdDevVelocity;
	float _damping;

	std::vector<Payload*> _payloads;

	Vector3 _color;

	void set(int type, float meanAge, float stdDevAge, Vector3 meanVelocity, Vector3 stdDevVelocity, float damping, std::vector<Payload*> payloads, Vector3 color) {

		_type = type;
		_meanAge = meanAge;
		_stdDevAge = stdDevAge;
		_meanVelocity = meanVelocity;
		_stdDevVelocity = stdDevVelocity;
		_damping = damping;
		_payloads = payloads;
		_color = color;

	}

};


class Firework : public Particle
{
	FireworkRule* rule;

	std::normal_distribution<double> distribLifeTime;

	std::normal_distribution<double> distribVelX;
	std::normal_distribution<double> distribVelY;
	std::normal_distribution<double> distribVelZ;

	std::random_device rnd;
	std::default_random_engine generator = std::default_random_engine(rnd());

public:
	Firework(Vector3 Pos, Vector3 Vel, Vector3 Acc, Vector3 color, FireworkRule* rule);
	~Firework();

	unsigned getType() { return rule->_type; };

	Vector3 getPos() { return pos.p; };
	Vector3 getVel() { return vel; };
	// virtual void update(double t) override;
};

