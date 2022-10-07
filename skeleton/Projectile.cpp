#include "Projectile.h"

Projectile::Projectile(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, float Mass) : Particle (Pos, Vel, Acc, damping, Mass),
age(1), alive(true)
{
}

Projectile::~Projectile()
{
}

void Projectile::update(double t)
{
	vel = Vector3(vel.x + acc.x * t, vel.y + acc.y * t, vel.z + acc.z * t);
	vel *= pow(damping, t);

	pos = physx::PxTransform(pos.p.x + vel.x * t, pos.p.y + vel.y * t, pos.p.z + vel.z * t);

	age -= t;

	if (pos.p.y < 0) alive = false;
	else if (age < 0) alive = false;
}
