#include "Particle.h"

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acc, double Damping, float Mass) :
	vel(Vel), acc(Acc), damping(Damping), mass(Mass)
{
	pos = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(0.9)), &pos, { 0.5, 0, 0.5, 1 });
}

Particle::~Particle()
{
	DeregisterRenderItem(renderItem);
}

void Particle::update(double t)
{
	vel = Vector3(vel.x + acc.x * t, vel.y + acc.y * t, vel.z + acc.z * t);
	vel *= pow(damping, t);
	// pos = physx::PxTransform(pos.p.x + vel.x * t + acc.x * exp2(t)/2, pos.p.y + vel.y * t + acc.y * exp2(t) / 2, pos.p.z + vel.z * t + acc.z * exp2(t) / 2);
	pos = physx::PxTransform(pos.p.x + vel.x * t, pos.p.y + vel.y * t, pos.p.z + vel.z * t);

}

Particle* Particle::clone() const
{
	return nullptr;
}
