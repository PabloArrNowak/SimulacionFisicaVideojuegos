#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel) : ParticleGenerator(std_dev_pos, std_dev_vel, 0)
{
	name = "GaussianGenerator";
	this->std_dev_pos = std_dev_pos;
	this->std_dev_vel = std_dev_vel;
	generationProb = 1;

	numParticles = 5;

	distribLifeTime = normal_distribution<double>(lifeTime - lifeTimeWidth / 2, lifeTime + lifeTimeWidth / 2);

	distribPosX = normal_distribution<double>(pos.x - posWidth.x / 2, pos.x + posWidth.x / 2);
	distribPosY = normal_distribution<double>(pos.y - posWidth.y / 2, pos.y + posWidth.y / 2);
	distribPosZ = normal_distribution<double>(pos.z - posWidth.z / 2, pos.z + posWidth.z / 2);

	distribVelX = normal_distribution<double>(vel.x - velWidth.x / 2, vel.x + velWidth.x / 2);
	distribVelY = normal_distribution<double>(vel.y - velWidth.y / 2, vel.y + velWidth.y / 2);
	distribVelZ = normal_distribution<double>(vel.z - velWidth.z / 2, vel.z + velWidth.z / 2);
}

std::list<Particle*> GaussianParticleGenerator::generateParticles()
{
	return std::list<Particle*>();
}
