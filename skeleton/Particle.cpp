#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping, float Mass, float lifeTime) :
	vel(Vel), acc(Acc), damping(Damping), invMass(1/Mass), timeLeft(lifeTime), alive(true)
{
	pos = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(0.9)), &pos, { 0.5, 0, 0.5, 1 });
}

Particle::Particle(Particle* other, Vector3 newPos, Vector3 newVel, Vector3 newAcc, float newLifeTime) : 
	pos(newPos), vel(newVel), acc(newAcc), damping(other->damping), invMass(other->invMass), timeLeft(newLifeTime), alive(true)
{

}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

bool Particle::update(double t)
{
	vel = Vector3(vel.x + acc.x * t, vel.y + acc.y * t, vel.z + acc.z * t);
	vel *= pow(damping, t);

	pos = physx::PxTransform(pos.p.x + vel.x * t, pos.p.y + vel.y * t, pos.p.z + vel.z * t);

	timeLeft -= t;

	if (pos.p.y < 0 || timeLeft < 0) return false;
	return true;
}