#ifndef _ForceConditional_h
#define _ForceConditional_h

#include <vector>

#include "Entity.h"

namespace sf
{
	class RenderWindow;
}

class ForceConditional
{
	public:

		ForceConditional();
		virtual ~ForceConditional();

		std::vector<Entity *> affectedObjects;

		virtual void apply();

		virtual void drawVisual(sf::RenderWindow *w);

};

#endif /*_ForceConditional_h*/
