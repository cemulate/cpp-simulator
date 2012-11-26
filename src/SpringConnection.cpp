#include "SpringConnection.h"

#include "CMGraphics.h"

#include "SimulationTime.h"

using namespace cm_sim;

SpringConnection::SpringConnection(double springConstant,
								double naturalLength,
								double visualSpringWidth,
								Entity *affectedObject1,
								Entity *affectedObject2,
								cm_sim::Vector staticDisplacement1,
								cm_sim::Vector staticDisplacement2) :
	ForceConditional(),
	springConstant(springConstant),
	naturalLength(naturalLength),
	visualSpringWidth(visualSpringWidth),
	staticDisplacement1(staticDisplacement1),
	staticDisplacement2(staticDisplacement2)
{
	this->affectedObjects.push_back(affectedObject1);
	this->affectedObjects.push_back(affectedObject2);
}

void SpringConnection::apply()
{
	Entity *b1 = affectedObjects[0];
	Entity *b2 = affectedObjects[1];

	Vector r1 = b1->actualDisplacement(staticDisplacement1);
	Vector r2 = b2->actualDisplacement(staticDisplacement2);

	Vector p1 = b1->getPosition() + r1;
	Vector p2 = b2->getPosition() + r2;

	double dis = (p2 - p1).mag();

	double stretch = dis - naturalLength;

	Vector dir1 = (p2 - p1).normalize();
	Vector dir2 = -dir1;

//	if (_firstTime)
//	{
//		_firstTime = false;
//		lastStretch = stretch;
//	}
//
//	double dStretch = (stretch - lastStretch) / SimulationTime::getInstance()->getCurrentTimeStep();
//	std::cout << "dStretch " << dStretch << " stretch " << stretch << std::endl;
//	lastStretch = stretch;
//  ------------
//	double s = (stretch >= 0) - (stretch <= 0);
//
//	Vector damp1 = (-1) * dir1 *
//  ---------
//	Vector velProj1 = b1->getVelocity().projectionOn(dir1);
//	Vector velProj2 = b2->getVelocity().projectionOn(dir2);
//
//	// AHA! Initial velocity state of (0, 0) produces a NaN vector when normalize is called, which
//	// then proceed to corrupt EVERYTHING into NaN. So catch that here:
//	Vector velDir1(0, 0);
//	Vector velDir2(0, 0);
//	if (velProj1.x != 0 && velProj1.y != 0)
//	{
//		velDir1 = velProj1.normalize();
//	}
//
//	if (velProj2.x != 0 && velProj2.y != 0)
//	{
//		velDir2 = velProj2.normalize();
//	}
//
//	double velMag1 = velProj1.mag();
//	double velMag2 = velProj2.mag();
//
//	Vector damp1 = (velMag1 * damping) * (-1) * velDir1;
//	Vector damp2 = (velMag2 * damping) * (-1) * velDir2;

//	Vector damp1 = -damping * b1->getVelocity();
//	Vector damp2  = -damping * b2->getVelocity(); // ORIGINAL

//	Vector f1 = (springConstant * stretch * dir1) + damp1;
//	Vector f2 = (springConstant * stretch * dir2) + damp2;

	Vector f1 = (springConstant * stretch * dir1);
	Vector f2 = (springConstant * stretch * dir2);

	Vector a1 = f1 / b1->getMass();
	Vector a2 = f2 / b2->getMass();

	//std::cout << a1 << " | " << a2 << std::endl;

	b1->incrementAcceleration(a1);
	b2->incrementAcceleration(a2);

	double aa1 = r1.scalarCross(f1);
	double aa2 = r2.scalarCross(f2);

	b1->incrementAngularAcceleration(aa1 / b1->getMomentOfInertia());
	b2->incrementAngularAcceleration(aa2 / b2->getMomentOfInertia());
}

void SpringConnection::drawVisual(sf::RenderWindow *w)
{
	Vector p1 = affectedObjects[0]->getPosition() + affectedObjects[0]->actualDisplacement(staticDisplacement1);
	Vector p2 = affectedObjects[1]->getPosition() + affectedObjects[1]->actualDisplacement(staticDisplacement2);
	CMGraphics::DrawSpring(p1, p2, 5, 0.5, visualSpringWidth, naturalLength, w);
}

//void SpringConnection::stepFinished()
//{
//	if (_firstTime)
//	{
//		_firstTime = false;
//		lastStretch = cStretch;
//	}
//
//	std::cout << "cStretch " << cStretch << " lastStretch " << lastStretch << " timeStep " << SimulationTime::getInstance()->getCurrentTimeStep() << std::endl;
//
//	dStretch = (cStretch - lastStretch) / SimulationTime::getInstance()->getCurrentTimeStep();
//	lastStretch = cStretch;
//}

std::ostream& operator<<(std::ostream& o, const SpringConnection& sc)
{
	o << "SpringConnection[" << sc.affectedObjects[0] << ", " << sc.affectedObjects[1] << "] ";
	return o;
}
