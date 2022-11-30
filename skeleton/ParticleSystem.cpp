#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "ForceGenerator.h"
#include "Firework.h"
#include "SpringForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"

ParticleSystem::ParticleSystem()
{
	particles = list<Particle*>();
	particleGenerators = list<ParticleGenerator*>();
	partForceRegistry = ParticleForceRegistry();
	gravity = { 0, -10, 0 };
}

void ParticleSystem::update(double t)
{
	for (ParticleGenerator* gen : particleGenerators) {
	
		auto parts = gen->generateParticles();
		for (Particle* part : parts) {
			particles.push_back(part);
			// Add to partForceRegistry
			for (ForceGenerator* force : forceGenerators) {
				if (force->getAffectsAll()) {
					partForceRegistry.addRegistry(force, part);
					part->resetForces();
				}
			}
		}
	}

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

	for (auto part : particles) {
		part->resetForces();
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

	// Firework* fw = new Firework(pos, vel, gravity * 0.99f, _firework_rules[type]);
	Firework* fw = new Firework(pos, vel, { 0, 0, 0 }, _firework_rules[type]);
	// Masa...

	fireworks.push_back(fw);
	for (ForceGenerator* force : forceGenerators) {
		if (force->getAffectsAll()) {
			partForceRegistry.addRegistry(force, fw);
			fw->resetForces();
		}
	}
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
			partForceRegistry.deleteParticle(firework);
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
			if (del->getResets()) {
				it = particles.erase(it);
				partForceRegistry.deleteParticle(del);
				delete del;
			}
			else it++;
	}
}

void ParticleSystem::createSpring(Particle* p1, Particle* p2, double restingLength, double springK)
{
	SpringForceGenerator* f1 = new SpringForceGenerator(springK, restingLength, p2);
	SpringForceGenerator* f2 = new SpringForceGenerator(springK, restingLength, p1);

	partForceRegistry.addRegistry(f1, p1);
	partForceRegistry.addRegistry(f2, p2);

	forceGenerators.push_back(f1);
	forceGenerators.push_back(f2);

	particles.push_back(p1);
	particles.push_back(p2);
}

void ParticleSystem::createAnchoredSpring(Particle* p1, const Vector3& anchorPos, double restingLength, double springK)
{
	AnchoredSpringForceGenerator* f = new AnchoredSpringForceGenerator(springK, restingLength, anchorPos);

	partForceRegistry.addRegistry(f, p1);
	forceGenerators.push_back(f);

	particles.push_back(p1);
}

void ParticleSystem::createSlinky(int joints, double springK, double restingTotalLength, Particle* partTemplate, Vector3 anchorPos)
{
	Particle* p1 = new Particle(partTemplate, Vector3(anchorPos.x, anchorPos.y - (restingTotalLength / joints), anchorPos.z), { 0, 0, 0 }, { 0, 0, 0 }, -1);
	p1->resetForces();

	AnchoredSpringForceGenerator* f = new AnchoredSpringForceGenerator(springK, restingTotalLength / joints, anchorPos);

	partForceRegistry.addRegistry(f, p1);
	forceGenerators.push_back(f);

	particles.push_back(p1);


	for (int i = 1; i < joints; i++)
	{
		Particle* p2 = new Particle(partTemplate, Vector3(anchorPos.x, anchorPos.y - (restingTotalLength / joints * i) - 1, anchorPos.z), { 0, 0, 0 }, { 0, 0, 0 }, -1);
		p2->resetForces();

		SpringForceGenerator* f1 = new SpringForceGenerator(springK, restingTotalLength / joints, p2);
		SpringForceGenerator* f2 = new SpringForceGenerator(springK, restingTotalLength / joints, p1);

		partForceRegistry.addRegistry(f1, p1);
		partForceRegistry.addRegistry(f2, p2);

		forceGenerators.push_back(f1);
		forceGenerators.push_back(f2);

		particles.push_back(p2);

		p1 = p2;
	}

}
