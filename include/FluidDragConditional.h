#ifndef _FluidDragConditional_h
#define _FluidDragConditional_h

#include "ForceConditional.h"

#include <vector>

#include "Entity.h"

namespace sf
{
	class RenderWindow;
}

class FluidDragConditional : public ForceConditional
{
	public:

		FluidDragConditional(double dampingConstant, std::vector<Entity *> objs);

		double dampingConstant;

		void apply();

		void drawVisual(sf::RenderWindow *);

	private:

};


#endif // _FluidDragConditional_h

