#include "CMGraphics.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Vector.h"

CMGraphics::CMGraphics()
{

}

void draw_sfml_line(sf::Vector2f a, sf::Vector2f b, sf::RenderWindow *w, sf::Color c)
{
    sf::Vertex line[2] = {sf::Vertex(a, c), sf::Vertex(b, c)};
    w->draw(line, 2, sf::Lines);
}

void CMGraphics::DrawSpring(cm_sim::Vector p1, cm_sim::Vector p2, float jags, float deadzone, float amplitude, float restLength, sf::RenderWindow *w)
{
	using namespace cm_sim;
	// Number of zero-up-zero-down-zero sections along the spring

	// Distance between spring ends
	float absoluteDistance = (p2 - p1).mag();
	float dis = absoluteDistance - (2 * deadzone);
	// Length of one jag section
	float jagLength = dis / jags;

	sf::Color c = sf::Color(0, 0, 0);
	if (absoluteDistance < restLength)
	{
		c = sf::Color(255, 0, 0);
	}

	// Unit vector along the direction of the spring
	Vector dhat = (p2 - p1).normalize();

	Vector jagsStart = p1 + deadzone * dhat;
	Vector jagsEnd = p2 - deadzone * dhat;

//	sf::Shape firstLine = sf::Shape::Line(p1.x, p1.y, jagsStart.x, jagsStart.y, 0.05, c);
//	w->draw(firstLine);
	draw_sfml_line(sf::Vector2f(p1.x, p1.y), sf::Vector2f(jagsStart.x, jagsStart.y), w, c);

	for (int i = 0; i < jags; i ++)
	{
		// Start point for this jag section
		Vector js = jagsStart + jagLength * i * dhat;
		// End point for this jag section
		Vector je = jagsStart + jagLength * (i+1) * dhat;

		// Vector from start to end of this jag section
		Vector jspan = je - js;

		// Final points that will represent horizontal locations of the up, zero, and down points in between the start and end points
		Vector highLoc = js + (jspan / 4);
		Vector zero = js + 2*(jspan / 4);
		Vector lowLoc = js + 3*(jspan / 4);

		Vector high = highLoc + (0.5*amplitude) * dhat.clockwiseOrthagonalVector().normalize();
		Vector low = lowLoc + (0.5*amplitude) * dhat.counterClockwiseOrthagonalVector().normalize();

//		sf::Shape l = sf::Shape::Line(js.x, js.y, high.x, high.y, 0.05, c);
//		sf::Shape l2 = sf::Shape::Line(high.x, high.y, zero.x, zero.y, 0.05, c);
//		sf::Shape l3 = sf::Shape::Line(zero.x, zero.y, low.x, low.y, 0.05, c);
//		sf::Shape l4 = sf::Shape::Line(low.x, low.y, je.x, je.y, 0.05, c);

		draw_sfml_line(sf::Vector2f(js.x, js.y), sf::Vector2f(high.x, high.y), w, c);
		draw_sfml_line(sf::Vector2f(high.x, high.y), sf::Vector2f(zero.x, zero.y), w, c);
		draw_sfml_line(sf::Vector2f(zero.x, zero.y), sf::Vector2f(low.x, low.y), w, c);
		draw_sfml_line(sf::Vector2f(low.x, low.y), sf::Vector2f(je.x, je.y), w, c);

	}

//	sf::Shape lastLine = sf::Shape::Line(jagsEnd.x, jagsEnd.y, p2.x, p2.y, 0.05, c);
	draw_sfml_line(sf::Vector2f(jagsEnd.x, jagsEnd.y), sf::Vector2f(p2.x, p2.y), w, c);
}

void CMGraphics::DrawVector(cm_sim::Vector initial, cm_sim::Vector v, sf::Color color, sf::RenderWindow *w)
{
//	using namespace cm_sim;
//	Vector terminal = initial + v;
//
////	sf::Shape mainLine = sf::Shape::Line(initial.x, initial.y, terminal.x, terminal.y, 0.1, color);
//
//	sf::ConvexShape arrow;
//	arrow.setPointCount(3);
//	arrow.AddPoint(0, 0.05, color, color);
//	arrow.AddPoint(0, -0.05, color, color);
//	arrow.AddPoint(0.1, 0, color, color);
//
//	float a = v.angle();
//
//	arrow.SetOrigin(0.05, 0.0);
//	arrow.SetPosition(terminal.x, terminal.y);
//	//arrow.SetPosition(0, 0);
//	arrow.Rotate((a * 180) / M_PI);
//
//	arrow.SetOutlineThickness(0.1);
//	arrow.EnableOutline(true);
//	arrow.EnableFill(true);
//
//	draw_sfml_line(sf::Vector2f(initial.x, initial.y), sf::Vector2f(terminal.x, terminal.y), w);
//	w->draw(arrow);
}
