#ifndef _Entity_h
#define _Entity_h

#include <iostream>
#include <cmath>
#include <deque>

#include "DataUtils.h"

namespace sf
{
	class RenderWindow;
}

struct freezeLog
{
	EntityState state;
	double dt;
};

class Entity {
    public:

		Entity();
		Entity(double mass, std::string mode);
		virtual ~Entity();

		static Entity* createNewEntity(std::string subclass);

		/* Acceptable attribute paths exposed in these methods are:
			position, velocity, acceleration, angularPosition, angularVelocity, angularAcceleration
			and subclasses may override to add handling for their own attributes
		*/

		// Kinematic quantities
        EntityState getValues();
        void setValues(EntityState);

        // Basic properties
        double getMass();
        void setMass(double);

        double getMomentOfInertia();

        EntityState getNextTimeDerivative();

		std::string getModeType();
		void setModeType(std::string);

		EntityModeMask getModeMask();

		void freeze();
		void unfreeze();
		bool isFrozen();

        void compileNext();
        void incrementAcceleration(cm_sim::Vector);
        void incrementAngularAcceleration(double);

        EntityState getState();
		void setState(EntityState);

		void stepFinished();

        // Conveninece methods for setting values
        void setPosition(cm_sim::Vector);
        void setVelocity(cm_sim::Vector);
        void setAcceleration(cm_sim::Vector);
        void setAngularPosition(double);
        void setAngularVelocity(double);
        void setAngularAcceleration(double);

        cm_sim::Vector getPosition();
        cm_sim::Vector getVelocity();
        cm_sim::Vector getAcceleration();
        double getAngularPosition();
        double getAngularVelocity();
        double getAngularAcceleration();

		virtual void draw(sf::RenderWindow *);

		virtual bool pointInside(cm_sim::Vector&);

		// From static displacement:
		cm_sim::Vector actualDisplacement(cm_sim::Vector);

	private:

		EntityState values;

		double mass;
        double momentOfInertia;

		EntityState _nextTimeDerivative;

		std::string mode;
		EntityModeMask modeMask;
		void setModeMask(EntityModeMask);

		cm_sim::Vector nextAcceleration;
        double nextAngularAcceleration;

		bool frozenState;
		std::deque<freezeLog> _frozenHistory;

		void _logIfFrozen();

	protected:
		void setMomentOfInertia(double i);
		virtual void updateMomentOfInertia();
};

#endif /*_Entity_h*/
