#include "Firework.h"


Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 Acc, FireworkRule* rule) : Particle(Pos, Vel, Acc, 0.998, 2.0f, 2.0f, { 0.8, 0.1, 0.1, 1 }, 2.0)
{
	this->rule = rule;

	distribLifeTime = std::normal_distribution<double>(rule->_meanAge, rule->_stdDevAge);

	distribVelX = std::normal_distribution<double>(rule->_meanVelocity.x, rule->_stdDevVelocity.x);
	distribVelY = std::normal_distribution<double>(rule->_meanVelocity.y, rule->_stdDevVelocity.y);
	distribVelZ = std::normal_distribution<double>(rule->_meanVelocity.z, rule->_stdDevVelocity.z);


	timeLeft = distribLifeTime(generator);

	vel.x += distribVelX(generator);
	vel.y += distribVelY(generator);
	vel.z += distribVelZ(generator);
}


Firework::~Firework()
{
}
