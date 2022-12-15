#pragma once
#include "RenderUtils.hpp"

class AngryBirdsObject
{

public:
	
	enum blockMat {
		WOOD,
		GLASS,
		STONE
	};

protected:

	int HP; // -1 for indestructible
	bool destroysOthers;

	RenderItem* renderItem;

public:

	AngryBirdsObject();
	AngryBirdsObject(int hp, bool destroysOther, RenderItem* renderIt);
	~AngryBirdsObject();

	virtual bool update(double t);
	virtual void resetForces() {  };
	virtual physx::PxActor* getRB() { return nullptr; };

	virtual void addForce(Vector3 f);

	virtual Vector3 getPos() {
		return Vector3();
	}
};

