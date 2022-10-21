#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping, float Mass, float lifeTime, Vector4 color, float radius) :
	vel(Vel), acc(Acc), invMass(1/Mass), timeLeft(lifeTime), alive(true)
{
	damping = Damping;
	pos = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(radius)), &pos, color);
}

Particle::Particle(Particle* other, Vector3 newPos, Vector3 newVel, Vector3 newAcc, float newLifeTime) : 
	pos(newPos), vel(newVel), acc(newAcc), damping(other->damping), invMass(other->invMass), timeLeft(newLifeTime), alive(true)
{
	renderItem = new RenderItem(other->renderItem->shape, &pos, other->renderItem->color);
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