#include "Simulation.h"
#include "Ball.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "PhysicsSolver.h"
#include "Entity.h"
#include "ForceConditional.h"
#include "GravityConditional.h"

Simulation::Simulation() :
	coordinateSystem(sf::Rect<float>(-10, 7.5, 20, -15)),
	dragInfo(DragInfo()),
	_dragging(false)
{
	mySolver.myEval = this;
}

Simulation::~Simulation()
{

}

void Simulation::addEntity(Entity *e)
{
	mySolver.addNewObject(e);
}

void Simulation::removeEntity(Entity *e)
{
	// Nothing...
}

void Simulation::addConditional(ForceConditional *f)
{
	std::cout << "addConditional.. adding " << f << std::endl;
	conditionals.push_back(f);
}

void Simulation::removeConditional(ForceConditional *f)
{
	// Nothing
}

sf::View Simulation::getCoordinateSystem()
{
	return coordinateSystem;
}

void Simulation::setCoordinateSystem(sf::View v)
{
	coordinateSystem = v;
}

void Simulation::simStep(double dt, sf::RenderWindow *window)
{
	window->clear(sf::Color(255, 255, 255));

	window->setView(coordinateSystem);

	drawEnvironment(window);

	mySolver.step(dt);

	for (int i = 0; i < mySolver.objects.size(); i ++)
	{
		mySolver.objects[i]->draw(window);
	}
}

void Simulation::evaluate()
{

	int i = 0;
	int n = mySolver.objects.size();

	for (i = 0; i < conditionals.size(); i ++)
	{
		conditionals[i]->apply();
	}

	for (i = 0; i < n; i ++)
	{
		mySolver.objects[i]->compileNext();
	}

	if (_dragging && dragInfo.isValid())
	{
		Entity *b = dragInfo.dragTarget;
		b->setPosition(dragInfo.initialTargetPosition + (mouseState - dragInfo.initialGrabPosition));
	}

}

void Simulation::leftClick(cm_sim::Vector v)
{
	for (int i = 0; i < mySolver.objects.size(); i ++)
	{
		Entity *b = mySolver.objects[i];
		if (b->pointInside(v))
		{
			dragInfo.dragTarget = b;
			dragInfo.initialGrabPosition = v;
			dragInfo.initialTargetPosition = b->getPosition();
			_dragging = true;

			b->freeze();
		}
	}
}
void Simulation::rightClick(cm_sim::Vector v)
{

}
void Simulation::leftClickUp(cm_sim::Vector v)
{
	if (_dragging)
	{
		dragInfo.dragTarget->unfreeze();

		_dragging = false;
	}
}

void Simulation::rightClickUp(cm_sim::Vector v)
{

}

void Simulation::drawEnvironment(sf::RenderWindow *w)
{
	for (int i = 0; i < conditionals.size(); i ++)
	{
		conditionals[i]->drawVisual(w);
	}
}
