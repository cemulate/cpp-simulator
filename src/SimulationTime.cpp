#include "SimulationTime.h"

bool SimulationTime::instanceFlag = false;
SimulationTime* SimulationTime::constInstance = NULL;

SimulationTime::SimulationTime()
{

}

double SimulationTime::getCurrentTimeStep()
{
	return timeStepHistory[timeStepHistory.back()];
}

void SimulationTime::newTimeStep(double dt)
{
	timeStepHistory.push_back(dt);
	if (timeStepHistory.size() > 10)
	{
		timeStepHistory.pop_front();
	}
}

SimulationTime * SimulationTime::getInstance()
{
	if (!instanceFlag)
	{
		constInstance = new SimulationTime();
		instanceFlag = true;
	}

	return constInstance;
}
