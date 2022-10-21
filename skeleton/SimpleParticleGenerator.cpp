#include "SimpleParticleGenerator.h"
#include "Particle.h"
#include <random>

SimpleParticleGenerator::SimpleParticleGenerator(Vector3 pos, Vector3 vel, Vector3 gravity, double lifeTimee, Vector3 posWidthh, Vector3 velWidthh, double lifeTimeWidthh, double iMass) : ParticleGenerator(pos, vel, iMass)
{
	name = "SimpleGenerator";
	posWidth = posWidthh;
	velWidth = velWidthh;
	gravityAcc = gravity;
	lifeTime = lifeTimee;
	lifeTimeWidth = lifeTimeWidthh;
	generationProb = 1;

	numParticles = 5;

	distribGenProb = uniform_real_distribution<double>(0, 1);
	distribLifeTime = uniform_real_distribution<double>(lifeTime - lifeTimeWidth / 2, lifeTime + lifeTimeWidth / 2);

	distribPosX = uniform_real_distribution<double>(pos.x - posWidth.x / 2, pos.x + posWidth.x / 2);
	distribPosY = uniform_real_distribution<double>(pos.y - posWidth.y / 2, pos.y + posWidth.y / 2);
	distribPosZ = uniform_real_distribution<double>(pos.z - posWidth.z / 2, pos.z + posWidth.z / 2);

	distribVelX = uniform_real_distribution<double>(vel.x - velWidth.x / 2, vel.x + velWidth.x / 2);
	distribVelY = uniform_real_distribution<double>(vel.y - velWidth.y / 2, vel.y + velWidth.y / 2);
	distribVelZ = uniform_real_distribution<double>(vel.z - velWidth.z / 2, vel.z + velWidth.z / 2);
}

list<Particle*> SimpleParticleGenerator::generateParticles()
{
	list<Particle*> parts = std::list<Particle*>();

	for (int i = 0; i < numParticles; i++)
	{
		// Random 0-1, si es menor que generationProb, genera
		if (distribGenProb(generator) < generationProb) {

			Vector3 rndPos = Vector3(distribPosX(generator), distribPosY(generator), distribPosZ(generator));
			Vector3 rndVel = Vector3(distribVelX(generator), distribVelY(generator), distribVelZ(generator));

			parts.push_back(new Particle(modelPart, rndPos, rndVel, gravityAcc, distribLifeTime(generator)));
		}
	}

	// Devuelve lista de particulas generadas este frame
	return parts;
}
