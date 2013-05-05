This is a (very) basic rigid body engine built in C++ and scritable through python

Running build.bat will compile all the files, and copy the core library dll and the python extension library
to the ./tests directory for convience.

The ./tests directory contains 3 sample python scripts that create simple situations and then run the simulation

* test1: Links an arbitrary chain of spheres together with springs
* test2: Creates a "molecule" by linking each of n balls together with every other ball with a spring
* test3: Attaches two rectangles by different corners with a spring. The rectangles are pinned at their centers but rotate freely