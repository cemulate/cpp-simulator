#include "GravityConditional.h"

GravityConditional::GravityConditional(double gConstant, std::vector<Entity *> objs) :
	ForceConditional(),
	gConstant(gConstant)
{
	for (int i = 0; i < objs.size(); i ++)
	{
		affectedObjects.push_back(objs[i]);
	}
}

void GravityConditional::apply()
{
	for (int i = 0; i < this->affectedObjects.size(); i ++)
	{
		// Gravity: simple enough right?
		Entity *e = this->affectedObjects[i];
		e->incrementAcceleration(cm_sim::Vector(0.0, gConstant));
	}
}

void GravityConditional::drawVisual(sf::RenderWindow *w)
{
	// Nothing
}

std::ostream& operator<<(std::ostream& o, const GravityConditional& sc)
{
	o << "GravityConditional[gConstant = " << sc.gConstant << "]";
	return o;
}
