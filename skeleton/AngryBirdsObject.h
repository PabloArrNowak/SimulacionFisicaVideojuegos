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

	float HP; // -1 for indestructible
	bool destroysOthers;

	RenderItem* renderItem;

public:

	AngryBirdsObject();
	AngryBirdsObject(float hp, bool destroysOther, RenderItem* renderIt);
	~AngryBirdsObject();

	virtual bool update(double t);
	virtual void resetForces() {  };
	virtual physx::PxActor* getRB() { return nullptr; };

	virtual void addForce(Vector3 f);

	virtual Vector3 getPos() {
		return Vector3();
	}

	bool hurtsOthers() {
		return destroysOthers;
	}

	virtual void hurt(Vector3 f) {
	}

	virtual bool isBird() { return false; };
	virtual bool isBuildingBlock() { return false; };
};

