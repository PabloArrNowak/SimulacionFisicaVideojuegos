#pragma once
#include "ParticleGenerator.h"
#include <list>
#include "core.hpp"
#include <random>

class GaussianParticleGenerator : public ParticleGenerator
{
protected:

	Vector3 mean_pos, mean_vel, std_dev_pos, std_dev_vel;
	double mean_t, std_dev_t;

	std::normal_distribution<double> d{ 0, 1 };

	std::normal_distribution<double> distribLifeTime;

	std::normal_distribution<double> distribPosX;
	std::normal_distribution<double> distribPosY;
	std::normal_distribution<double> distribPosZ;

	std::normal_distribution<double> distribVelX;
	std::normal_distribution<double> distribVelY;
	std::normal_distribution<double> distribVelZ;

public: 
	GaussianParticleGenerator(Vector3 mean_pos, Vector3 mean_vel, double mean_t, Vector3 std_dev_pos, Vector3 std_dev_vel, double std_dev_t);
	virtual std::list<Particle*> generateParticles();

};

