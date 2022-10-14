#pragma once
#include "ParticleGenerator.h"
#include "RenderUtils.hpp"
#include <list>

using namespace std;

class SimpleParticleGenerator : public ParticleGenerator
{
	Vector3 velWidth, posWidth;
	double lifeTime, lifeTimeWidth;
	Vector3 gravityAcc;

	uniform_real_distribution<double> distribGenProb;
	uniform_real_distribution<double> distribLifeTime;;


	uniform_real_distribution<double> distribPosX;
	uniform_real_distribution<double> distribPosY;
	uniform_real_distribution<double> distribPosZ;

	uniform_real_distribution<double> distribVelX;
	uniform_real_distribution<double> distribVelY;
	uniform_real_distribution<double> distribVelZ;

public:
	SimpleParticleGenerator(Vector3 pos, Vector3 vel, Vector3 gravity, double lifeTimee, Vector3 posWidthh, Vector3 velWidthh, double lifeTimeWidthh, double iMass);
	virtual std::list<Particle*> generateParticles() override;
};

