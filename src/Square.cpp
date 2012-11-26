#include "Square.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "CMGraphics.h"
#include "Vector.h"

using namespace cm_sim;

Square::Square() :
	Entity(1.0, "MODE_ROTATIONAL"),
	sideLength(1.0)
{
	this->updateMomentOfInertia();
}

Square::Square(double sideLength, double mass) :
	Entity(mass, "MODE_ROTATIONAL"),
	sideLength(sideLength)
{
	this->updateMomentOfInertia();
}

double Square::getSideLength()
{
	return sideLength;
}

void Square::setSideLength(double d)
{
	sideLength = d;
	this->updateMomentOfInertia();
}

void Square::updateMomentOfInertia()
{
	this->setMomentOfInertia((this->getMass() * (2 * this->getSideLength() * this->getSideLength())) / 12);
}

void Square::draw(sf::RenderWindow *w)
{
	Vector p = this->getPosition();
	float a = this->getAngularPosition();
	a = (a * 180) / M_PI;
	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(sideLength, sideLength));
	rect.setOrigin(sideLength/2, sideLength/2);
	rect.setPosition(p.x, p.y);
	rect.rotate(a);
	rect.setOutlineThickness(0.1);
	rect.setOutlineColor(sf::Color::Black);
	w->draw(rect);

	Vector dotCoords = p + (this->actualDisplacement(getCornerStaticDisplacement(0)) * 0.8);
	sf::CircleShape dot = sf::CircleShape(0.1);
	dot.setFillColor(sf::Color(255, 0, 0));
	dot.setPosition(sf::Vector2f(dotCoords.x, dotCoords.y));
	w->draw(dot);
	//CM_DrawVector(p, getCornerStaticDisplacement(0) - p, sf::Color(0, 0, 0), w);
}

bool Square::pointInside(cm_sim::Vector &v)
{
	return false;
}

Vector Square::getCornerStaticDisplacement(int num)
{
	double r = sqrtf(2 * (0.5 * this->getSideLength()) * (0.5 * this->getSideLength()));
	float angle = ((num * M_PI_2) + M_PI_4);
	return Vector(r*cosf(angle), r*sinf(angle));
}
