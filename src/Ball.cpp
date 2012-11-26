#include "Ball.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace cm_sim;

Ball::Ball() :
	Entity(1.0, "MODE_TRANSLATIONAL"),
	radius(1.0)
{
	this->updateMomentOfInertia();
}

Ball::Ball(double radius, double mass) :
	Entity(mass, "MODE_TRANSLATIONAL"),
	radius(radius)
{
	this->updateMomentOfInertia();
}

double Ball::getRadius()
{
	return radius;
}

void Ball::setRadius(double d)
{
	radius = d;
	this->updateMomentOfInertia();
}

void Ball::updateMomentOfInertia()
{
	this->setMomentOfInertia((this->getMass() * (this->getRadius() * this->getRadius())) / 2);
}

void Ball::draw(sf::RenderWindow *w)
{
	//cout << "Drawing!" << endl;
	//cout << w->GetView().GetRect().GetWidth() << endl;
	//cout << w->GetView().GetRect().GetHeight() << endl;
	sf::CircleShape s = sf::CircleShape(radius);
	s.setOrigin(sf::Vector2f(radius, radius));
	s.setPosition(sf::Vector2f(this->getPosition().x, this->getPosition().y));
	s.setFillColor(sf::Color(0, 0, 0));
	w->draw(s);
}

bool Ball::pointInside(cm_sim::Vector &v)
{
	double m = (v - this->getPosition()).mag();
	return (m <= radius);
}
