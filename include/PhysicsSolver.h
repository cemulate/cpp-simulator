#ifndef _PhysicsSolver_h
#define _PhysicsSolver_h

#include <vector>
#include <boost/ptr_container/ptr_vector.hpp>

#include "DataUtils.h"
#include "Entity.h"

class Evaluate;

class PhysicsSolver
{
	public:

		PhysicsSolver();

		std::vector<Entity *> objects;

		Evaluate *myEval;

		void addNewObject(Entity *n);
		void clear();

		void step(double dt);

	private:

		std::vector<EntityState> k0, k1, k2, k3, k4;
		std::vector<EntityModeMask> modes;

};

#endif /*_PhysicsSolver_h*/
