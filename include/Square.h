#ifndef _Square_h
#define _Square_h

#include "Entity.h"

namespace sf
{
	class RenderWindow;
}

namespace cm_sim
{
	class Vector;
}

class Square : public Entity
{
	public:

		Square();
		Square(double sideLength, double mass);

		void draw(sf::RenderWindow *w);
		bool pointInside(cm_sim::Vector &v);

		double getSideLength();
		void setSideLength(double);

		cm_sim::Vector getCornerStaticDisplacement(int num);

	private:
		double sideLength;

		void updateMomentOfInertia();

};

#endif /*_Square_h*/
