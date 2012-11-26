from __future__ import division

from pySimulator import *

sim = Simulation()
	
s1 = Square(4.0, 4.0)
s2 = Square(4.0, 4.0)

s1.setPosition(Vector(-5.0, 0.0))
s2.setPosition(Vector(5.0, 0.0))

c = SpringConnection(8.0, 8.0, 1.0, s1, s2, s1.getCornerStaticDisplacement(1), s2.getCornerStaticDisplacement(3))

sim.addEntity(s1)
sim.addEntity(s2)
sim.addConditional(c)

run_simulation(sim)

exit()