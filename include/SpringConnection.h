#ifndef _SpringConnection_h
#define _SpringConnection_h

#include "ForceConditional.h"
#include "Vector.h"

#include <deque>

class SpringConnection : public ForceConditional
{
	public:

		SpringConnection(double springConstant,
						double naturalLength,
						double visualSpringWidth,
						Entity *affectedObject1,
						Entity *affectedObject2,
						cm_sim::Vector staticDisplacement1,
						cm_sim::Vector staticDisplacement2);

		double springConstant;
		double naturalLength;
		double visualSpringWidth;

		cm_sim::Vector staticDisplacement1;
		cm_sim::Vector staticDisplacement2;

		void apply();

		void drawVisual(sf::RenderWindow *w);
};

std::ostream& operator<<(std::ostream&, const SpringConnection&);

#endif /*_SpringConnection_h*/
