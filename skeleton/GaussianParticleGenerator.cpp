#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel) : ParticleGenerator(std_dev_pos, std_dev_vel, 0)
{
}

std::list<Particle*> GaussianParticleGenerator::generateParticles()
{
	return std::list<Particle*>();
}
