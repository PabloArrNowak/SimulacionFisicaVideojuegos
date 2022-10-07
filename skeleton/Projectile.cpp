#include "Projectile.h"

Projectile::Projectile(Vector3 Pos, Vector3 Vel, Vector3 Acc, double damping, float Mass) : Particle (Pos, Vel, Acc, damping, Mass, 1.5)
{
}

Projectile::~Projectile()
{
}
