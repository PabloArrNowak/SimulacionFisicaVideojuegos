#include "AnchoredSpringForceGenerator.h"
#include "Particle.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double K, double restingLength, const Vector3& anchorPos) : SpringForceGenerator(K, restingLength, new Particle(anchorPos, {0, 0, 0}, {0, 0, 0}, 0, 1e6, -1, {1, 0, 0, 1}, 1))
{
}

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator()
{
	delete other;
}
