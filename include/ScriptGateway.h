#ifndef _ScriptGateway_h
#define _ScriptGateway_h

//testing
#include "Vector.h"
#include "DataUtils.h"
#include "Simulation.h"

class GUI;

namespace sf
{
	class Thread;
}

class ScriptGateway
{
	public:

		ScriptGateway();
		~ScriptGateway();

		void test(cm_sim::Vector v, EntityState e);

		void showWorld();
		void destroyWorld();

		Simulation& getSimulation();


	private:

		bool _showing;

		sf::Thread *thread;
		GUI *gui;
		Simulation simulation;

};


#endif // _ScriptGateway_h

