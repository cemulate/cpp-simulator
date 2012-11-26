#ifndef _BallTestSimulation_h
#define _BallTestSimulation_h

#include "Simulation.h"
#include <vector>

namespace sf
{
	class RenderWindow;
}

class BallTestSimulation : public Simulation
{
	public:

		BallTestSimulation();
		~BallTestSimulation();

		int getNumberBalls();
		void setNumberBalls(int n);

		void drawEnvironment(sf::RenderWindow *w);

	private:

		int numberBalls;
		double tE;

		void _setupSpringPairs();
};

#endif /*_BallTestSimulation_h*/
