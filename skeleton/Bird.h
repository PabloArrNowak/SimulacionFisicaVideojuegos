#pragma once

#include "AngryBirdsObject.h"

class Bird : public AngryBirdsObject
{
protected:
	
	std::vector<double> damageMultipliers; // Usar damageMultipliers[WOOD], etc.

	bool flying;
	bool powerAvailable; // Not Fliying, PowerAvailable means in Slingshot if it is Front
	double timeLeft; // Decreases after hit

public:

	Bird();
	~Bird();

	virtual void activatePower() {
		powerAvailable = false;
	}
};

