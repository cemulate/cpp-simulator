#include <iostream>
#include <cstring>

#include "Entity.h"
#include "DataUtils.h"
#include "SimulationTime.h"

#include "Ball.h"
#include "Square.h"

using namespace cm_sim;

Entity::Entity() :
	values(EntityState()),
	mass(1.0),
	momentOfInertia(1.0),
	_nextTimeDerivative(EntityState()),
	mode("MODE_COMPLETE_NEWTONIAN"),
	modeMask(EntityModeMask()),
	nextAcceleration(cm_sim::Vector(0, 0)),
	nextAngularAcceleration(0),
	frozenState(false),
	_frozenHistory(std::deque<freezeLog>())
{
	this->setModeType(this->getModeType());
}

Entity::~Entity()
{

}

Entity::Entity(double mass, std::string mode) :
	values(EntityState()),
	mass(mass),
	momentOfInertia(1.0),
	_nextTimeDerivative(EntityState()),
	mode(mode),
	modeMask(EntityModeMask()),
	nextAcceleration(cm_sim::Vector(0, 0)),
	nextAngularAcceleration(0),
	frozenState(false),
	_frozenHistory(std::deque<freezeLog>())
{
	this->setModeType(this->getModeType());
}
Entity* Entity::createNewEntity(std::string subclass)
{
	if (subclass == "Ball") { return new Ball(); }
	if (subclass == "Square") { return new Square(); }
}

EntityState Entity::getValues()
{
	return values;
}

void Entity::setValues(EntityState es)
{
	values = es;
}

double Entity::getMass()
{
	return mass;
}

void Entity::setMass(double m)
{
	mass = m;
	this->updateMomentOfInertia();
}

double Entity::getMomentOfInertia()
{
	return momentOfInertia;
}

void Entity::setMomentOfInertia(double i)
{
	momentOfInertia = i;
}

void Entity::updateMomentOfInertia()
{
	this->setMomentOfInertia(0);
}

EntityState Entity::getNextTimeDerivative()
{
	return _nextTimeDerivative;
}

std::string Entity::getModeType()
{
	return mode;
}

void Entity::setModeType(std::string t)
{
	mode = t;

	EntityModeMask newMask;

	if (isFrozen())
	{
		newMask.posActive = false;
		newMask.velActive = false;
		newMask.accActive = false;
		newMask.aposActive = false;
		newMask.avelActive = false;
		newMask.aaccActive = false;
		return;
	}
	if (t == "MODE_TRANSLATIONAL" || t == "MODE_COMPLETE_NEWTONIAN")
	{
		newMask.posActive = true;
		newMask.velActive = true;
		newMask.accActive = false;
	}

	if (t == "MODE_ROTATIONAL" || t == "MODE_COMPLETE_NEWTONIAN")
	{
		newMask.aposActive = true;
		newMask.avelActive = true;
		newMask.aaccActive = false;
	}

	this->setModeMask(newMask);
}

EntityModeMask Entity::getModeMask()
{
	return modeMask;
}

void Entity::setModeMask(EntityModeMask e)
{
	modeMask = e;
}

EntityState Entity::getState()
{
	return values;
}

void Entity::setState(EntityState e)
{
	values = e;
}

void Entity::stepFinished()
{
	_logIfFrozen();
}

void Entity::freeze()
{
	frozenState = true;

	// Apply our current mode so the mode mask can respond to the fact that we're frozen
	this->setModeType(this->getModeType());
}

void Entity::unfreeze()
{
	frozenState = false;

	this->setModeType(this->getModeType());

	int i = 0;

	// Average timestep

	double avgDt = 0.0;
	for (i = 0; i < 5; i ++)
	{
		avgDt += _frozenHistory[i].dt;
	}

	avgDt = avgDt / 5;

	// Translation

	Vector vPoints[4];
	for (i = 1; i < 5; i ++)
	{
		vPoints[i-1] = (_frozenHistory[i].state.pos - _frozenHistory[i-1].state.pos) / avgDt;
	}

	Vector aPoints[3];
	for (i = 1; i < 4; i ++)
	{
		aPoints[i-1] = (vPoints[i] - vPoints[i-1]) / avgDt;
	}

	Vector avgVel(0, 0);
	for (i = 0; i < 4; i ++)
	{
		avgVel = avgVel + vPoints[i];
	}

	avgVel = avgVel / 4;

	Vector avgAcc(0, 0);
	for (i = 0; i < 3; i ++)
	{
		avgAcc = avgAcc + aPoints[i];
	}

	avgAcc = avgAcc / 3;

	// Angular

	double avPoints[4];
	for (i = 1; i < 5; i ++)
	{
		avPoints[i-1] = (_frozenHistory[i].state.apos - _frozenHistory[i-1].state.apos) / avgDt;
	}

	double aaPoints[3];
	for (i = 1; i < 4; i ++)
	{
		aaPoints[i-1] = (avPoints[i] - avPoints[i-1]) / avgDt;
	}

	double avgAVel = 0.0;
	for (i = 0; i < 4; i ++)
	{
		avgAVel = avgAVel + avPoints[i];
	}

	avgAVel = avgAVel / 4;

	double avgAAcc = 0.0;
	for (i = 0; i < 3; i ++)
	{
		avgAAcc = avgAAcc + aaPoints[i];
	}

	avgAAcc = avgAAcc / 3;

	EntityState newState;
	newState.pos = values.pos;
	newState.vel = avgVel;
	newState.acc = avgAcc;
	newState.apos = values.apos;
	newState.avel = avgAVel;
	newState.aacc = avgAAcc;

	setState(newState);
}

bool Entity::isFrozen()
{
	return frozenState;
}

void Entity::compileNext()
{
	_nextTimeDerivative.pos = values.vel;
	_nextTimeDerivative.vel = nextAcceleration;
	_nextTimeDerivative.apos = values.avel;
	_nextTimeDerivative.avel = nextAngularAcceleration;

	nextAcceleration = Vector(0, 0);
	nextAngularAcceleration = 0.0;
}

void Entity::incrementAcceleration(Vector v)
{
	nextAcceleration += v;
}

void Entity::incrementAngularAcceleration(double d)
{
	nextAngularAcceleration += d;
}

void Entity::draw(sf::RenderWindow *w)
{
	// Nothing
}

bool Entity::pointInside(Vector &v)
{
	return false;
}

void Entity::setAcceleration(Vector v)
{
	values.acc = v;
}

void Entity::setVelocity(Vector v)
{
	values.vel = v;
}

void Entity::setPosition(Vector v)
{
	values.pos = v;
}

void Entity::setAngularPosition(double a)
{
	values.apos = a;
}

void Entity::setAngularVelocity(double a)
{
	values.avel = a;
}

void Entity::setAngularAcceleration(double a)
{
	values.aacc = a;
}

cm_sim::Vector Entity::getPosition()
{
	return values.pos;
}

cm_sim::Vector Entity::getVelocity()
{
	return values.vel;
}

cm_sim::Vector Entity::getAcceleration()
{
	return values.acc;
}

double Entity::getAngularPosition()
{
	return values.apos;
}

double Entity::getAngularVelocity()
{
	return values.avel;
}

double Entity::getAngularAcceleration()
{
	return values.aacc;
}

void Entity::_logIfFrozen()
{
	if (isFrozen())
	{
		_frozenHistory.push_back( {values, SimulationTime::getInstance()->getCurrentTimeStep()} );
		if (_frozenHistory.size() > 5)
		{
			_frozenHistory.pop_front();
		}
	}
}

Vector Entity::actualDisplacement(cm_sim::Vector staticDisplacement)
{

	return staticDisplacement.rotate(values.apos);

}

//void Entity::step(double dt) {
//    if (mode == ACC) {
//
//        tValues[0][0] = values[POS];
//        tValues[0][1] = values[VEL];
//        tValues[0][2] = SIM_CALLBACK(0, time);
//
//        tValues[1][0] = tValues[0][0] + 0.500*tValues[0][1]*dt;
//        tValues[1][1] = tValues[0][1] + 0.500*tValues[0][2]*dt;
//        tValues[1][2] = SIM_CALLBACK(1, time + dt/2.000);
//
//        tValues[2][0] = tValues[0][0] + 0.500*tValues[1][1]*dt;
//        tValues[2][1] = tValues[0][1] + 0.500*tValues[1][2]*dt;
//        tValues[2][2] = SIM_CALLBACK(2, time + dt/2.000);
//
//        tValues[3][0] = tValues[0][0] + tValues[2][1]*dt;
//        tValues[3][1] = tValues[0][1] + tValues[2][2]*dt;
//        tValues[3][2] = SIM_CALLBACK(3, time + dt);
//
//        values[POS] = tValues[0][0] + (dt/6.000)*(tValues[0][1] + 2.000*tValues[1][1] + 2.000*tValues[2][1] + tValues[3][1]);
//        values[VEL] = tValues[0][1] + (dt/6.000)*(tValues[0][2] + 2.000*tValues[1][2] + 2.000*tValues[3][2] + tValues[3][2]);
//
//        values[ACC] = tValues[3][2];
//
//    }
//    else if (mode == MODE_NO_CALCULATION)
//    {
//    	// Do aboslutely nothing
//    }
//
//    if (angularMode == ACC)
//    {
//    	atValues[0][0] = angleValues[POS];
//        atValues[0][1] = angleValues[VEL];
//        atValues[0][2] = SIM_CALLBACK_ANGLE(0, time);
//
//        atValues[1][0] = atValues[0][0] + 0.500*atValues[0][1]*dt;
//        atValues[1][1] = atValues[0][1] + 0.500*atValues[0][2]*dt;
//        atValues[1][2] = SIM_CALLBACK_ANGLE(1, time + dt/2.000);
//
//        atValues[2][0] = atValues[0][0] + 0.500*atValues[1][1]*dt;
//        atValues[2][1] = atValues[0][1] + 0.500*atValues[1][2]*dt;
//        atValues[2][2] = SIM_CALLBACK_ANGLE(2, time + dt/2.000);
//
//        atValues[3][0] = atValues[0][0] + atValues[2][1]*dt;
//        atValues[3][1] = atValues[0][1] + atValues[2][2]*dt;
//        atValues[3][2] = SIM_CALLBACK_ANGLE(3, time + dt);
//
//        angleValues[POS] = atValues[0][0] + (dt/6.000)*(atValues[0][1] + 2.000*atValues[1][1] + 2.000*atValues[2][1] + atValues[3][1]);
//        angleValues[VEL] = atValues[0][1] + (dt/6.000)*(atValues[0][2] + 2.000*atValues[1][2] + 2.000*atValues[3][2] + atValues[3][2]);
//
//        angleValues[ACC] = atValues[3][2];
//    }
//    else if (angularMode == MODE_NO_CALCULATION)
//    {
//    	// Do nothing
//    }
//
//    time += dt;
//}
