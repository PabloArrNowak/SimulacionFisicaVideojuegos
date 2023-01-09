#include "GroundBlock.h"

GroundBlock::GroundBlock(Vector3 pos, Vector3 size) : AngryBirdsObject()
{
	HP = -1;
	dimensions = size;
	destroysOthers = true;

	Vector4 color(97.0 / 255, 49.0 / 255, 47.0 / 255, 1);

	physx::PxTransform posPxT(pos);
	rb = PxGetPhysics().createRigidStatic(posPxT);
	physx::PxBoxGeometry geom(size / 2);
	physx::PxShape* shape = CreateShape(geom);
	rb->attachShape(*shape);

	renderItem = new RenderItem(shape, rb, color);
}

GroundBlock::~GroundBlock()
{
}
