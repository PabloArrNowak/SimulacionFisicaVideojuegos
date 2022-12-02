#include "GroundBlock.h"

GroundBlock::GroundBlock(Vector3 pos, Vector3 size)
{
	HP = -1;

	Vector4 color(0.2, 0.1, 0.2, 1);

	physx::PxTransform posPxT(pos);
	rb = PxGetPhysics().createRigidStatic(posPxT);
	physx::PxBoxGeometry geom(size / 2);
	physx::PxShape* shape = CreateShape(geom);
	rb->attachShape(*shape);

	renderItem = new RenderItem(shape, &posPxT, color);
}

GroundBlock::~GroundBlock()
{
}
