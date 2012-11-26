#include "PhysicsSolver.h"

#include <iostream>

#include "Evaluate.h"

PhysicsSolver::PhysicsSolver()
{

}

void PhysicsSolver::step(double dt)
{

	int i = 0;
	EntityState next;

	for (i = 0; i < objects.size(); i ++)
	{
		k0[i] = objects[i]->getState();
		modes[i] = objects[i]->getModeMask();
	}

	myEval->evaluate();

	for (i = 0; i < objects.size(); i ++)
	{
		Entity *e = objects[i];

		k1[i] = e->getNextTimeDerivative();

		next = e->getState();

		if (!e->isFrozen())
		{
			if (modes[i].posActive) { next.pos = k0[i].pos + k1[i].pos * (dt / 2); }
			if (modes[i].velActive) { next.vel = k0[i].vel + k1[i].vel * (dt / 2); }
			if (modes[i].accActive) { next.acc = k0[i].acc + k1[i].acc * (dt / 2); }
			if (modes[i].aposActive) { next.apos = k0[i].apos + k1[i].apos * (dt / 2); }
			if (modes[i].avelActive) { next.avel = k0[i].avel + k1[i].avel * (dt / 2); }
			if (modes[i].aaccActive) { next.aacc = k0[i].aacc + k1[i].aacc * (dt / 2); }
		}

		e->setState(next);
	}

	myEval->evaluate();

	for (i = 0; i < objects.size(); i ++)
	{
		Entity *e = objects[i];
		k2[i] = e->getNextTimeDerivative();

		next = e->getState();

		if (!e->isFrozen())
		{
			if (modes[i].posActive) { next.pos = k0[i].pos + k2[i].pos * (dt / 2); }
			if (modes[i].velActive) { next.vel = k0[i].vel + k2[i].vel * (dt / 2); }
			if (modes[i].accActive) { next.acc = k0[i].acc + k2[i].acc * (dt / 2); }
			if (modes[i].aposActive) { next.apos = k0[i].apos + k2[i].apos * (dt / 2); }
			if (modes[i].avelActive) { next.avel = k0[i].avel + k2[i].avel * (dt / 2); }
			if (modes[i].aaccActive) { next.aacc = k0[i].aacc + k2[i].aacc * (dt / 2); }
		}

		e->setState(next);
	}

	myEval->evaluate();

	for (i = 0; i < objects.size(); i ++)
	{
		Entity *e = objects[i];
		k3[i] = e->getNextTimeDerivative();

		next = e->getState();

		if (!e->isFrozen())
		{
			if (modes[i].posActive) { next.pos = k0[i].pos + k3[i].pos * dt; }
			if (modes[i].velActive) { next.vel = k0[i].vel + k3[i].vel * dt; }
			if (modes[i].accActive) { next.acc = k0[i].acc + k3[i].acc * dt; }
			if (modes[i].aposActive) { next.apos = k0[i].apos + k3[i].apos * dt; }
			if (modes[i].avelActive) { next.avel = k0[i].avel + k3[i].avel * dt; }
			if (modes[i].aaccActive) { next.aacc = k0[i].aacc + k3[i].aacc * dt; }
		}

		e->setState(next);
	}

	myEval->evaluate();

	for (i = 0; i < objects.size(); i ++)
	{
		Entity *e = objects[i];
		k4[i] = e->getNextTimeDerivative();

		next = e->getState();

		if (!e->isFrozen())
		{
			if (modes[i].posActive) { next.pos = k0[i].pos + (k1[i].pos + 2*k2[i].pos + 2*k3[i].pos + k4[i].pos) * (dt / 6); }
			if (modes[i].velActive) { next.vel = k0[i].vel + (k1[i].vel + 2*k2[i].vel + 2*k3[i].vel + k4[i].vel) * (dt / 6); }
			if (modes[i].accActive) { next.acc = k0[i].acc + (k1[i].acc + 2*k2[i].acc + 2*k3[i].acc + k4[i].acc) * (dt / 6); }
			if (modes[i].aposActive) { next.apos = k0[i].apos + (k1[i].apos + 2*k2[i].apos + 2*k3[i].apos + k4[i].apos) * (dt / 6); }
			if (modes[i].avelActive) { next.avel = k0[i].avel + (k1[i].avel + 2*k2[i].avel + 2*k3[i].avel + k4[i].avel) * (dt / 6); }
			if (modes[i].aaccActive) { next.aacc = k0[i].aacc + (k1[i].aacc + 2*k2[i].aacc + 2*k3[i].aacc + k4[i].aacc) * (dt / 6); }
		}

		e->setState(next);
	}

	for (i = 0; i < objects.size(); i ++)
	{
		objects[i]->stepFinished();
	}

}

void PhysicsSolver::addNewObject(Entity *n)
{
	objects.push_back(n);
	k0.resize(objects.size());
	k1.resize(objects.size());
	k2.resize(objects.size());
	k3.resize(objects.size());
	k4.resize(objects.size());
	modes.resize(objects.size());
}

void PhysicsSolver::clear()
{
	objects.clear();
	k0.resize(1);
	k1.resize(1);
	k2.resize(1);
	k3.resize(1);
	k4.resize(1);
	modes.resize(1);
}
