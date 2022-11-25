#pragma once

#include "SpringForceGenerator.h"
#include "core.hpp"

class AnchoredSpringForceGenerator : public SpringForceGenerator
{
protected:

	Vector3 anchorPos;

public:

	AnchoredSpringForceGenerator(double K, double restingLength, const Vector3& anchorPos);
	~AnchoredSpringForceGenerator();

};

