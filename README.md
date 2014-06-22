Simulator
==================

This is a basic rigid body engine built as a hobby in C++ and scriptable through python

The build environment uses Scons and is currently very badly designed and relies on the file structure of my local Windows machine with MinGW. However, if you have the requisite libraries (Boost, SFML, and Python), you shouldn't have *too* much trouble convincing it to compile. 

The `/tests` directory contains 3 sample python scripts that create simple situations and then run the simulation

* test1: Links an arbitrary chain of spheres together with springs
* test2: Creates a "molecule" by linking each of n balls together with every other ball with a spring
* test3: Attaches two rectangles by different corners with a spring. The rectangles are pinned at their centers but rotate freely