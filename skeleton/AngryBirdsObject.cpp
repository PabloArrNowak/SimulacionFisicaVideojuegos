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

bool AngryBirdsObject::update(double t)
{
	return true;
}

void AngryBirdsObject::addForce(Vector3 f)
{
}
