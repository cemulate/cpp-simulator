#include <iostream>

#include "ScriptGateway.h"
#include "Simulation.h"
#include "DataUtils.h"
#include "Vector.h"

#include "Entity.h"
#include "Ball.h"
#include "Square.h"

#include "ForceConditional.h"
#include "SpringConnection.h"
#include "GravityConditional.h"
#include "FluidDragConditional.h"

#include <SFML/Graphics.hpp>

#include "GUI.h"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

using namespace boost::python;

sf::View createNewView(double left, double top, double width, double height)
{
	return sf::View(sf::Rect<float>(left, top, width, height));
}

void run_simulation(Simulation *s)
{
	GUI g;

	g.setCurrentSim(s);

	g.setSimActive(true);

	g.Run();
}

BOOST_PYTHON_MODULE(pySimulator)
{

	class_<std::vector<Entity *> >("EntityVector")
		.def(vector_indexing_suite<std::vector<Entity *> >());

	class_<cm_sim::Vector>("Vector", init<double, double>());

	class_<Entity>("Entity", init<>())
		.def("setMass", &Entity::setMass)
		.def("setPosition", &Entity::setPosition)
		.def("setVelocity", &Entity::setVelocity)
		.def("setAcceleration", &Entity::setAcceleration)
		.def("setAngularPosition", &Entity::setAngularPosition)
		.def("setAngularVelocity", &Entity::setAngularVelocity)
		.def("setAngularAcceleration", &Entity::setAngularAcceleration)
		.def("getMass", &Entity::getMass)
		.def("getPosition", &Entity::getPosition)
		.def("getVelocity", &Entity::getVelocity)
		.def("getAcceleration", &Entity::getAcceleration)
		.def("getAngularPosition", &Entity::getAngularPosition)
		.def("getAngularVelocity", &Entity::getAngularVelocity)
		.def("getAngularAcceleration", &Entity::getAngularAcceleration);

	class_<Ball, bases<Entity> >("Ball", init<>())
		.def(init<double, double>())
		.def("setRadius", &Ball::setRadius)
		.def("getRadius", &Ball::getRadius);

	class_<Square, bases<Entity> >("Square", init<>())
		.def(init<double, double>())
		.def("setSideLength", &Square::setSideLength)
		.def("getSideLength", &Square::getSideLength)
		.def("getCornerStaticDisplacement", &Square::getCornerStaticDisplacement);

	class_<ForceConditional>("ForceConditional", no_init);

	class_<SpringConnection, bases<ForceConditional> >("SpringConnection", init<double, double, double, Entity*, Entity*, cm_sim::Vector, cm_sim::Vector>())
		.def(self_ns::str(self_ns::self));

	class_<GravityConditional, bases<ForceConditional> >("GravityConditional", init<double, std::vector<Entity *> >());

	class_<FluidDragConditional, bases<ForceConditional> >("FluidDragConditional", init<double, std::vector<Entity *> >());

	class_<sf::View>("View", init<>());

	def("createNewView", createNewView);

	class_<Simulation>("Simulation", init<>())
		.def("addEntity", &Simulation::addEntity)
		.def("removeEntity", &Simulation::removeEntity)
		.def("addConditional", &Simulation::addConditional)
		.def("removeConditional", &Simulation::removeConditional)
		.def("getCoordinateSystem", &Simulation::getCoordinateSystem)
		.def("setCoordinateSystem", &Simulation::setCoordinateSystem);

//    class_<ScriptGateway>("ScriptGateway", init<>())
//		.def("test", &ScriptGateway::test)
//		.def("showWorld", &ScriptGateway::showWorld)
//		.def("destroyWorld", &ScriptGateway::destroyWorld)
//		.def("go", &ScriptGateway::go)
//		.def("getSimulation", &ScriptGateway::getSimulation,
//			return_internal_reference<>());

	def("run_simulation", run_simulation);
}
