#include "Bird.h"
#include "LevelManager.h"

Bird::Bird(LevelManager* lvlMngr, Vector3 pos, float radius, float mass, Vector4 color) : AngryBirdsObject()
{
	destroysOthers = true;
	flying = false;
	damageMultipliers = std::vector<double>(3);
	this->lvlMngr = lvlMngr;
	timeLeft = 2;

	physx::PxTransform posPxT(pos);
	rb = PxGetPhysics().createRigidDynamic(posPxT);
	physx::PxSphereGeometry geom(radius);
	physx::PxShape* shape = CreateShape(geom);
	rb->attachShape(*shape);

	rb->setLinearVelocity({ 0, 0, 0 });
	rb->setAngularVelocity({ 0, 0, 0 });

	Vector3 inertia = { radius * radius + radius * radius,
						radius * radius + radius * radius,
						radius * radius + radius * radius };

	rb->setMass(mass);
	rb->setMassSpaceInertiaTensor(inertia * rb->getMass() / 12.0);

	renderItem = new RenderItem(shape, rb, color);
}

Bird::~Bird()
{

}

bool Bird::update(double t)
{
	if (timeLeft <= 0) {
		if (furthersQueue)
			lvlMngr->nextBird();
		return false;
	}

	if (!flying && powerAvailable && lvlMngr->getActiveBird() == this) {
		addForce(Vector3(0, 0.3005, 0));
	}

	if (timeLeft <= 1) {
		powerAvailable = false;
	}

	if (!flying && !powerAvailable) {
		timeLeft -= t;
	}

	return true;
}

void Bird::hurt(Vector3 f)
{
	if (flying)
		flying = false;
}

void Bird::autoLaunch()
{
	addForce(Vector3(40, 30, 0));
	flying = true;
}

void Bird::addForce(Vector3 f)
{
	rb->addForce(f * 1000);

	//if (HP != -1)
	//	hurt(f);
}

void Bird::setPos(Vector3 newPos)
{
	rb->setGlobalPose(PxTransform(newPos));
}

void Bird::activatePower()
{
	powerAvailable = false;
	// lvlMngr->nextBird();
}

void Bird::resetBird()
{
	powerAvailable = true;
	flying = false;
	// lvlMngr->nextBird();
}