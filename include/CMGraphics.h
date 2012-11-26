#ifndef _CMGraphics_h
#define _CMGraphics_h

namespace sf
{
	class RenderWindow;
	class Color;
}

namespace cm_sim
{
	class Vector;
}

class CMGraphics
{
	public:

		static void DrawSpring(cm_sim::Vector p1, cm_sim::Vector p2, float jags, float deadzone, float amplitude, float restLength, sf::RenderWindow *w);
		static void DrawVector(cm_sim::Vector initial, cm_sim::Vector v, sf::Color color, sf::RenderWindow *w);

	private:

		CMGraphics();

};


#endif /*_CMGraphics_h*/
