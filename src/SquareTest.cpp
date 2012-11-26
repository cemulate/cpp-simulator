#include "SquareTest.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "CMGraphics.h"
#include "SpringConnection.h"
#include "Vector.h"
#include "Square.h"
#include "Ball.h"

using namespace cm_sim;

SquareTest::SquareTest() : Simulation()
{

	Square *s1 = new Square(4.0, 4.0);
	Square *s2 = new Square(4.0, 4.0);
	Square *s3 = new Square(4.0, 4.0);
	Square *s4 = new Square(4.0, 4.0);

//	s1->setModeType("MODE_COMPLETE_NEWTONIAN");
//	s2->setModeType("MODE_COMPLETE_NEWTONIAN");
//	s3->setModeType("MODE_COMPLETE_NEWTONIAN");
//	s4->setModeType("MODE_COMPLETE_NEWTONIAN");

	mySolver.addNewObject(s1);
	mySolver.addNewObject(s2);
	mySolver.addNewObject(s3);
	mySolver.addNewObject(s4);

	mySolver.objects[0]->setPosition(Vector(5.0, 5.0));
	mySolver.objects[1]->setPosition(Vector(5.0, -5.0));
	mySolver.objects[2]->setPosition(Vector(-5.0, -5.0));
	mySolver.objects[3]->setPosition(Vector(-5.0, 5.0));

	conditionals.push_back(new SpringConnection(8,
												8,
												1.0,
												(Entity *)(&mySolver.objects[0]),
												(Entity *)(&mySolver.objects[1]),
												s1->getCornerStaticDisplacement(0),
												s2->getCornerStaticDisplacement(3)));

	conditionals.push_back(new SpringConnection(8,
												8,
												1.0,
												(Entity *)(&mySolver.objects[1]),
												(Entity *)(&mySolver.objects[2]),
												s1->getCornerStaticDisplacement(3),
												s2->getCornerStaticDisplacement(2)));

//	conditionals.push_back(new SpringConnection(8,
//												8,
//												1.0,
//												(Entity *)(&mySolver.objects[2]),
//												(Entity *)(&mySolver.objects[3]),
//												s1->getCornerStaticDisplacement(2),
//												s2->getCornerStaticDisplacement(1)));
//
//	conditionals.push_back(new SpringConnection(8,
//												8,
//												1.0,
//												(Entity *)(&mySolver.objects[3]),
//												(Entity *)(&mySolver.objects[0]),
//												s1->getCornerStaticDisplacement(1),
//												s2->getCornerStaticDisplacement(0)));
}
