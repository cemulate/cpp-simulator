#ifndef GravityConditional_h
#define GravityConditional_h

#include "ForceConditional.h"
#include <vector>

namespace sf
{
	class RenderWindow;
}

class GravityConditional : public ForceConditional
{
	public:

		GravityConditional(double gConstant, std::vector<Entity *> objs);

		double gConstant;

		void apply();
		void drawVisual(sf::RenderWindow *);

	private:

};

std::ostream& operator<<(std::ostream&, const GravityConditional&);


#endif // GravityConditional_h

