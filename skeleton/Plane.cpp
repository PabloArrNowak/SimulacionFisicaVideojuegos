#include "Plane.h"

Plane::Plane(Vector3 Pos)
{
	pos = physx::PxTransform(Pos.x, Pos.y, Pos.z);
	renderItem = new RenderItem(CreateShape(physx::PxBoxGeometry(1000, 0.1, 1000)), &pos, { 0.1, 0.1, 0.3, 1 });
}

Plane::~Plane()
{
	DeregisterRenderItem(renderItem);
}

void Plane::update(double t)
{
}
