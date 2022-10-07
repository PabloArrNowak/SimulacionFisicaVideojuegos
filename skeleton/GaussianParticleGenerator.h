#pragma once
#include "ParticleGenerator.h"
#include <list>
#include "core.hpp"
#include <random>

class GaussianParticleGenerator : public ParticleGenerator
{
protected:
	Vector3 std_dev_pos, std_dev_vel;
	double std_fev_t;
	std::normal_distribution<double> d{ 0, 1 };

public: 
	GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel);
	virtual std::list<Particle*> generateParticles();

};

