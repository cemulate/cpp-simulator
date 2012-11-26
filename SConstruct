import os

env = Environment(CXX = "C:/software_lib/MinGW/bin/g++", CCFLAGS = "-g", tools=['mingw'])

def filtered_glob(env, pattern, omit=[], ondisk=True, source=False, strings=False):
    return filter(lambda f: os.path.basename(f.path) not in omit, env.Glob(pattern))

env.AddMethod(filtered_glob, "FilteredGlob");


sourceList = env.FilteredGlob("#/src/*.cpp", ['main.cpp'])

wrapper_sourceList = env.Glob("#/src/boost_python_extension/*.cpp")



# ------------ Headers and Libraries ------------- 

pathList = [
'./include',
'C:/software_lib/boost',
'C:/software_lib/SFML/include',
'C:/Python27/include'
]

libPathList = [
'C:/software_lib/boost/stage/lib',
'C:/software_lib/SFML/lib',
'C:/Python27/libs',
'./bin'
]

libList = [
'boost_thread-mgw45-mt-1_46_1',
'boost_python-mgw45-mt-1_46_1', 
'sfml-system',
'sfml-window',
'sfml-graphics',
'python27',
]


# ------------ Dynamic libraries and executables ------------- 

mainLibrary = env.SharedLibrary(
target='./bin/simulator.dll',
source=sourceList,
CPPPATH=pathList,
LIBPATH=libPathList,
LIBS=libList
)

Default(mainLibrary)


# Clients of the shared library just made will need access to it:

libList_client = libList + ['simulator']
libPathList_client = libPathList + ['./bin']


# A main executable uses the library:

exe = env.Program(
target='./bin/simulator_prog.exe',
source=Glob("#/src/main.cpp"),
CPPPATH=pathList,
LIBS=libList_client,
LIBPATH=libPathList_client
)

Default(exe)


# And tbe python wrapper uses the library:

pywrapper = env.SharedLibrary(
target='./bin/pySimulator.dll',
source=wrapper_sourceList,
CPPPATH=pathList,
LIBS=libList_client,
LIBPATH=libPathList_client
)

Default(pywrapper)
