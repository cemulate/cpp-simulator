#ifndef _Simulation_h
#define _Simulation_h

#include <vector>

#include "DataUtils.h"
#include "Evaluate.h"
#include "ForceConditional.h"
#include "PhysicsSolver.h"

#include <SFML/Graphics.hpp>

class Entity;

namespace sf
{
	class RenderWindow;
}

namespace cm_sim
{
	class Vector;
}

class Simulation : public Evaluate {

	public:

		PhysicsSolver mySolver;
		std::vector<ForceConditional *> conditionals;

		Simulation();
		~Simulation();

		void addEntity(Entity *);
		void removeEntity(Entity *);
		void addConditional(ForceConditional *);
		void removeConditional(ForceConditional *);

		sf::View getCoordinateSystem();
		void setCoordinateSystem(sf::View v);

		void simStep(double dt, sf::RenderWindow *window);

		void evaluate();
		virtual void drawEnvironment(sf::RenderWindow *w);

		void leftClick(cm_sim::Vector);
		void rightClick(cm_sim::Vector);

		void leftClickUp(cm_sim::Vector);
		void rightClickUp(cm_sim::Vector);

		cm_sim::Vector mouseState;

	private:

		sf::View coordinateSystem;

		DragInfo dragInfo;
		bool _dragging;
};

#endif /*_Simulation_h*/
