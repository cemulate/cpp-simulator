from pySimulator import *
import sys

s = Simulation()

nBalls = 3
if len(sys.argv) > 1:
	nBalls = int(sys.argv[1])
else:
	nBalls = int(raw_input("Number of balls? "))

balls = []
conns = []
for i in range(nBalls):
	b = Ball(0.3, 0.4)
	b.setPosition(Vector(-5 + i, 5))
	balls.append(b)
	if (i > 0):
		conns.append(SpringConnection(100.0, 1, 0.3, balls[i-1], balls[i], Vector(0, 0), Vector(0, 0)))
	
for b in balls:
	s.addEntity(b)
	
for c in conns:
	s.addConditional(c)
	print c


ev = EntityVector()
for b in balls:
	ev.append(b)

gc = GravityConditional(-9.8, ev)
s.addConditional(gc)

dc = FluidDragConditional(0.5, ev)
s.addConditional(dc)
	
run_simulation(s)

exit()