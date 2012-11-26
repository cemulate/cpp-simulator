#ifndef _SimulationTime_h
#define _SimulationTime_h

#include <deque>

class SimulationTime
{
	public:

		static SimulationTime * getInstance();

		std::deque<double> timeStepHistory;
		double getCurrentTimeStep();
		void newTimeStep(double dt);



	private:

		SimulationTime();

		static bool instanceFlag;
		static SimulationTime *constInstance;
};

#endif /*_SimulationTime_h*/
