#include "BuildingBlock.h"
#include "RenderUtils.hpp"
#include <PxRigidDynamic.h>

BuildingBlock::BuildingBlock(Vector3 pos, Vector3 size, blockMat bMaterial, int hp) : AngryBirdsObject()
{
	material = bMaterial;
	HP = hp;
	dimensions = size;

	Vector4 color;
	double mass;
	switch (material)
	{
	case BuildingBlock::WOOD:
		color = { 1, 0.5, 0, 1 };
		mass = size.x * size.y * 0.001;
		break;

	case BuildingBlock::GLASS:
		color = { 0, 1, 1, 0.7 };
		mass = size.x * size.y * 0.0005;
		break;

	case BuildingBlock::STONE:
		color = { 0.5, 0.3, 0.5, 1 };
		mass = size.x * size.y * 0.003;
		break;

	default:
		break;
	}

	physx::PxTransform posPxT(pos);
	rb = PxGetPhysics().createRigidDynamic(posPxT);
	physx::PxBoxGeometry geom(size / 2);
	physx::PxShape* shape = CreateShape(geom);
	rb->attachShape(*shape);

	rb->setLinearVelocity({ 0, 0, 0 });
	rb->setAngularVelocity({ 0, 0, 0 });

	Vector3 inertia = { size.y * size.y + size.z * size.z,
						size.x * size.x + size.z * size.z,
						size.y * size.y + size.x * size.x };

	rb->setMass(mass);
	rb->setMassSpaceInertiaTensor(inertia * rb->getMass() / 12.0);

	renderItem = new RenderItem(shape, rb, color);
}

void BuildingBlock::addForce(Vector3 f)
{
	rb->addForce(f * 1000);
	// Deal Damage
	// HP -= f.magnitudeSquared() / 100.0;
}
