#ifndef _SolverDataUtils_h
#define _SolverDataUtils_h

#include "Vector.h"

class Entity;

struct EntityState {

	EntityState() :
		pos(cm_sim::Vector(0, 0)),
		vel(cm_sim::Vector(0, 0)),
		acc(cm_sim::Vector(0, 0)),
		apos(0),
		avel(0),
		aacc(0)
	{

	}

	cm_sim::Vector pos;
	cm_sim::Vector vel;
	cm_sim::Vector acc;

	double apos;
	double avel;
	double aacc;

};

struct EntityModeMask {

	EntityModeMask() :
		posActive(false),
		velActive(false),
		accActive(false),
		aposActive(false),
		avelActive(false),
		aaccActive(false)
	{

	}

	bool posActive;
	bool velActive;
	bool accActive;

	bool aposActive;
	bool avelActive;
	bool aaccActive;

};

struct DragInfo
{
	DragInfo() :
		dragTarget(NULL),
		initialTargetPosition(cm_sim::Vector(0, 0)),
		initialGrabPosition(cm_sim::Vector(0, 0))
	{

	}

	Entity *dragTarget;
	cm_sim::Vector initialTargetPosition;
	cm_sim::Vector initialGrabPosition;

	bool isValid() { return (dragTarget != NULL); }

};

enum EntityModeType
{
	MODE_TRANSLATIONAL,
	MODE_ROTATIONAL,
	MODE_COMPLETE_NEWTONIAN
};


#endif /*_SolverDataUtils_h*/
