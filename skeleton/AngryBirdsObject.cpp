#include "AngryBirdsObject.h"

AngryBirdsObject::AngryBirdsObject() {

}

AngryBirdsObject::AngryBirdsObject(int hp, bool destroysOther, RenderItem* renderIt) {

	HP = hp;
	destroysOthers = destroysOther;
	renderItem = renderIt;

}


AngryBirdsObject::~AngryBirdsObject()
{
	DeregisterRenderItem(renderItem);
}
