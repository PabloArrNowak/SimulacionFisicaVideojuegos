#pragma once

#include "AngryBirdsObject.h"

class LevelManager;

class Bird : public AngryBirdsObject
{
protected:
	
	std::vector<double> damageMultipliers; // Usar damageMultipliers[WOOD], etc.
	LevelManager* lvlMngr;

	bool flying;
	bool powerAvailable; // Not Fliying, PowerAvailable means in Slingshot if it is Front
	double timeLeft; // Decreases after hit

	physx::PxRigidDynamic* rb;

	bool furthersQueue = true;

public:

	Bird(LevelManager* lvlMngr, Vector3 pos, float radius, float mass, Vector4 color);
	~Bird();

	virtual void activatePower();

	virtual void hurt(Vector3 f) override;

	virtual bool update(double t) override;
	void resetForces() override { rb->clearForce(); };
	void setPos(Vector3 newPos);

	physx::PxActor* getRB() override { return rb; };
	bool hasPowerAvilable() { return powerAvailable; };
	bool airborn() { return flying; };

	void autoLaunch();
	virtual void addForce(Vector3 f) override;
	virtual void resetBird();
	void setFlying(bool newFlying) { flying = newFlying; };
	void setPowerAvailable(bool newPowerA) { powerAvailable = newPowerA; };
	void setFurthersQueue(bool newFQ) { furthersQueue = newFQ; };

	float getDamageMultiplier(blockMat type) { return damageMultipliers[type]; };
	bool isBird() override { return true; };
};

