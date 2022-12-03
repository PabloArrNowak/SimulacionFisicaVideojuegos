#pragma once
#include "RenderUtils.hpp"

class AngryBirdsObject
{

protected:
	
	enum blockMat {
		WOOD,
		GLASS,
		STONE
	};

	int HP; // -1 for indestructible
	bool destroysOthers;

	RenderItem* renderItem;

public:

	AngryBirdsObject();
	AngryBirdsObject(int hp, bool destroysOther, RenderItem* renderIt);
	~AngryBirdsObject();

};

