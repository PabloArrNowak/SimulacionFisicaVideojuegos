#pragma once

#include "AngryBirdsObject.h"

class Bird : public AngryBirdsObject
{
protected:
	
	std::vector<double> damageMultipliers; // Usar damageMultipliers[WOOD], etc.

	bool flying;
	bool powerAvailable; // Not Fliying, PowerAvailable means in Slingshot if it is Front
	double timeLeft; // Decreases after hit

	physx::PxRigidDynamic* rb;

public:

	Bird();
	~Bird();

	virtual void activatePower() {
		powerAvailable = false;
	}

	virtual bool update(double t) override;
	void resetForces() override { rb->clearForce(); };
	physx::PxActor* getRB() override { return rb; };
};

