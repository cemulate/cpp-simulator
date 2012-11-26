from __future__ import division

from pySimulator import *
import itertools, math

nBalls = int(raw_input("Number of balls? "))
k = 100.0
nl = 3.5
width = 0.3

sim = Simulation()

balls = []
for i in range(nBalls):
	b = Ball(0.3, 1.0)
	x = 3.0 * math.cos(2*math.pi*(i / nBalls))
	y = 3.0 * math.sin(2*math.pi*(i / nBalls))
	print i, x, y
	b.setPosition(Vector(x, y))
	balls.append(b)
	
conns = []
for (i, j) in itertools.combinations(range(nBalls), 2):
	conns.append(SpringConnection(k, nl, width, balls[i], balls[j], Vector(0, 0), Vector(0, 0)))
	pass

for b in balls:
	sim.addEntity(b)
	
for c in conns:
	sim.addConditional(c)

ev = EntityVector()
for b in balls:
	ev.append(b)

# gc = GravityConditional(-9.8, ev)
# sim.addConditional(gc)

dc = FluidDragConditional(5.0, ev)
sim.addConditional(dc)

run_simulation(sim)

exit()