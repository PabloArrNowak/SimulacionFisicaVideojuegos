#include "BuildingBlock.h"
#include "RenderUtils.hpp"
#include <PxRigidDynamic.h>

BuildingBlock::BuildingBlock(Vector3 pos, Vector3 size, blockMat bMaterial, int hp) : AngryBirdsObject()
{
	material = bMaterial;
	HP = hp;
	dimensions = size;

	Vector4 color;
	switch (material)
	{
	case BuildingBlock::WOOD:
		color = { 1, 0.5, 0, 1 };
		break;

	case BuildingBlock::GLASS:
		color = { 0, 1, 1, 0.7 };
		break;

	case BuildingBlock::STONE:
		color = { 0.5, 0.3, 0.5, 1 };
		break;

	default:
		break;
	}

	physx::PxTransform posPxT(pos);
	rb = PxGetPhysics().createRigidDynamic(posPxT);
	physx::PxBoxGeometry geom(size / 2);
	physx::PxShape* shape = CreateShape(geom);
	rb->attachShape(*shape);

	renderItem = new RenderItem(shape, &posPxT, color);
}
