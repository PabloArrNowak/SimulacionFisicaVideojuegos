#pragma once

#include "AngryBirdsObject.h"

class Bird : public AngryBirdsObject
{
protected:
	
	std::vector<double> damageMultipliers; // Usar damageMultipliers[WOOD], etc.

	double timeLeft; // Decreases after hit

public:

	Bird();
	~Bird();
};

