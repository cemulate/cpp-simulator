#include "FluidDragConditional.h"

#include <vector>

FluidDragConditional::FluidDragConditional(double dampingConstant, std::vector<Entity *> objs) :
	ForceConditional(),
	dampingConstant(dampingConstant)
{
	for (int i = 0; i < objs.size(); i ++)
	{
		this->affectedObjects.push_back(objs[i]);
	}
}

void FluidDragConditional::apply()
{
	for (int i = 0; i < this->affectedObjects.size(); i ++)
	{
		Entity *e = this->affectedObjects[i];

		e->incrementAcceleration((e->getVelocity() * -dampingConstant) / e->getMass());
	}
}

void FluidDragConditional::drawVisual(sf::RenderWindow *w)
{
	// Nothing...
}
