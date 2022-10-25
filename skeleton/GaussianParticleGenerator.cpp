#include "GaussianParticleGenerator.h"
#include "Particle.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 mean_pos, Vector3 mean_vel, double mean_t, Vector3 std_dev_pos, Vector3 std_dev_vel, double std_dev_t) : ParticleGenerator(mean_pos, mean_vel, 0)
{
	name = "GaussianGenerator";
	this->mean_pos = mean_pos;
	this->mean_vel = mean_vel;
	this->mean_t = mean_t;
	this->std_dev_pos = std_dev_pos;
	this->std_dev_vel = std_dev_vel;
	this->std_dev_t = std_dev_t;
	generationProb = 1;

	numParticles = 5;

	distribLifeTime = normal_distribution<double>(mean_t, std_dev_t);

	distribPosX = normal_distribution<double>(mean_pos.x, std_dev_pos.x);
	distribPosY = normal_distribution<double>(mean_pos.y, std_dev_pos.y);
	distribPosZ = normal_distribution<double>(mean_pos.z, std_dev_pos.z);

	distribVelX = normal_distribution<double>(mean_vel.x, std_dev_vel.x);
	distribVelY = normal_distribution<double>(mean_vel.y, std_dev_vel.y);
	distribVelZ = normal_distribution<double>(mean_vel.z, std_dev_vel.z);
}

std::list<Particle*> GaussianParticleGenerator::generateParticles()
{
	list<Particle*> parts = std::list<Particle*>();

	for (int i = 0; i < numParticles; i++)
	{
		// Random 0-1, si es menor que generationProb, genera
		if (d(generator) < generationProb) {

			Vector3 rndPos = Vector3(distribPosX(generator), distribPosY(generator), distribPosZ(generator));
			Vector3 rndVel = Vector3(distribVelX(generator), distribVelY(generator), distribVelZ(generator));

			parts.push_back(new Particle(modelPart, rndPos, rndVel, Vector3(0, -10, 0), distribLifeTime(generator)));
		}
	}

	// Devuelve lista de particulas generadas este frame
	return parts;
}
