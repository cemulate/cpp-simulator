@echo off
call scons
mv ./bin/pySimulator.dll ./bin/pySimulator.pyd
cp ./bin/pySimulator.pyd ./tests/pySimulator.pyd
cp ./bin/simulator.dll ./tests/simulator.dll