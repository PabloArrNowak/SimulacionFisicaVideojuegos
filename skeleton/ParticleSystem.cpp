#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "Firework.h"

ParticleSystem::ParticleSystem()
{
	particles = list<Particle*>();
	particleGenerators = list<ParticleGenerator*>();
	partForceRegistry = ParticleForceRegistry();
	gravity = { 0, -10, 0 };
}

void ParticleSystem::update(double t)
{
	partForceRegistry.update(t);

	for (auto it = particles.begin(); it != particles.end();) {
		if (!(*it)->update(t)) {
			Particle* del = *it;
			it = particles.erase(it);
			partForceRegistry.deleteParticle(del);
			delete del;
		}
		else it++;
	}
	
	fireworksUpdate(t);

	for (ParticleGenerator* gen : particleGenerators) {
	
		auto parts = gen->generateParticles();
		for (Particle* part : parts) {
			particles.push_back(part);
			// Add to partForceRegistry
		}

	}
}

ParticleGenerator* ParticleSystem::getParticleGenerator(std::string name)
{
	ParticleGenerator* ret = nullptr;
	for (ParticleGenerator* gen : particleGenerators) {
		if (gen->getName() == name) {
			ret = gen;
			break;
		}
	}

	return ret;
}

void ParticleSystem::generateFireworkSystem()
{

	_firework_rules = std::vector<FireworkRule*>(3, nullptr);
	for (int i = 0; i < _firework_rules.size(); i++) _firework_rules[i] = new FireworkRule();

	_firework_rules[0]->set(0, 1, 0.5, { -1, -2, -1 }, { 20, 10, 20 }, 0.999, {});

	_firework_rules[1]->set(1, 1, 0.5, { 0, 0, 0 }, { 20, 20, 20 }, 0.999, std::vector<Payload*>(1, new Payload(0, 5)));

	std::vector<Payload*> rules2Payload;
	rules2Payload.push_back(new Payload(1, 5));
	rules2Payload.push_back(new Payload(0, 3));
	_firework_rules[2]->set(2, 2, 0.5, { -7, 0, -10 }, { 5, 5, 5 }, 0.999, rules2Payload);

}

void ParticleSystem::generateFirework(unsigned type, const Vector3& pos, const Vector3& vel)
{

	if (type >= _firework_rules.size()) {
		return;
	}

	Firework* fw = new Firework(pos, vel, gravity * 0.99f, _firework_rules[type]);
	// Masa...

	fireworks.push_back(fw);

}

void ParticleSystem::fireworksUpdate(double t)
{
	if (fireworks.empty())
		return;

	for (auto it = fireworks.begin(); it != fireworks.end();) {
		Firework* firework = *it;
		if (!firework->update(t)) {
			FireworkRule* rule = getFireworkRule(firework->getType());
			Vector3 pos = firework->getPos();
			Vector3 vel = firework->getVel();
			it = fireworks.erase(it);
			delete firework;

			for (auto itPayload = rule->_payloads.begin(); itPayload != rule->_payloads.end(); itPayload++) {
				Payload* payload = *itPayload;
				for (int i = 0; i < payload->count; i++) {
					generateFirework(payload->type, pos, vel);
				}
			}
		}
		else it++;
	}

}

void ParticleSystem::setGenerator(ParticleGenerator* gen)
{
	if (!particleGenerators.empty())
		particleGenerators.erase(particleGenerators.begin());

	if (gen != nullptr)
		particleGenerators.push_back(gen);
}

void ParticleSystem::resetParticles()
{
	for (auto it = particles.begin(); it != particles.end();) {
			Particle* del = *it;
			it = particles.erase(it);
			delete del;
	}
}
