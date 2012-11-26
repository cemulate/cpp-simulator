#include "GUI.h"

#include "Simulation.h"
#include "SimulationTime.h"

GUI::GUI()
{
	currentSim = NULL;
	simActive = false;
	_shouldEnd = false;

	//simThread = new sf::Thread(&GUI::Run, this);
	//simThread->Launch();
}

GUI::~GUI()
{

}

void GUI::Run()
{
	sf::RenderWindow mainWindow(sf::VideoMode(800, 600, 32), "SFML Test");

	mainWindow.clear(sf::Color(255, 255, 255));

	sf::Clock c;

	SimulationTime *timeState = SimulationTime::getInstance();

	while (mainWindow.isOpen())
	{
		if (_shouldEnd)
		{
			std::cout << "Telling main window to close..." << std::endl;
			mainWindow.close();
		}

		double dt = (double)c.getElapsedTime().asSeconds();

		timeState->newTimeStep(dt);

		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
			{
				mainWindow.close();
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2f v = mainWindow.convertCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				cm_sim::Vector cv(v.x, v.y);

				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left: getCurrentSim()->leftClick(cv); break;
					case sf::Mouse::Right: getCurrentSim()->rightClick(cv); break;
				}
			}
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				sf::Vector2f v = mainWindow.convertCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
				cm_sim::Vector cv(v.x, v.y);

				switch (event.mouseButton.button)
				{
					case sf::Mouse::Left: getCurrentSim()->leftClickUp(cv); break;
					case sf::Mouse::Right: getCurrentSim()->rightClickUp(cv); break;
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2f v = mainWindow.convertCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
				cm_sim::Vector cv(v.x, v.y);

				getCurrentSim()->mouseState = cv;
			}

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			c.restart();
			continue;
		}

		// Top level "wipe" - before any simulation custom code
		mainWindow.clear(sf::Color(255, 255, 255));

		if (simActive && (currentSim != NULL))
		{
			currentSim->simStep(dt, &mainWindow);
		}

		mainWindow.display();

		c.restart();
		sf::sleep(sf::milliseconds(10));
	}

	std::cout << "Exiting GUI background thread" << std::endl;
}

bool GUI::getSimActive()
{
	return simActive;
}

void GUI::setSimActive(bool b)
{
	simActive = b;
}

void GUI::closeSimulation()
{
	this->setSimActive(false);
	_shouldEnd = true;
}


Simulation* GUI::getCurrentSim()
{
	return currentSim;
}

void GUI::setCurrentSim(Simulation *s)
{
	currentSim = s;
}
