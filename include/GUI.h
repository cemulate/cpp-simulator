#ifndef _GUI_h
#define _GUI_h

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Simulation;

class GUI
{
	public:

		GUI();
		~GUI();

		Simulation *currentSim;

		void Run();
		void startSimulation();
		void stopSimulation();

		Simulation* getCurrentSim();
		void setCurrentSim(Simulation *s);

		bool getSimActive();
		void setSimActive(bool b);

		void closeSimulation();

	private:

		bool _shouldEnd;

		bool simActive;
};

#endif /*_GUI_h*/
