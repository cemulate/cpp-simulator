#ifndef _Ball_h
#define _Ball_h

#include "Entity.h"

namespace sf
{
	class RenderWindow;
}

namespace cm_sim
{
	class Vector;
}

class Ball : public Entity
{
	public:

		Ball();
		Ball(double radius, double mass);

		void draw(sf::RenderWindow *w);
		bool pointInside(cm_sim::Vector &v);

		double getRadius();
		void setRadius(double);

	private:
		double radius;

		void updateMomentOfInertia();
};

#endif /*_Ball_h*/
