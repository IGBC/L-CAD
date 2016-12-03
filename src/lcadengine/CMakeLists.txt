##
# Build file for lcadengine
# This file builds the core library that all lcad functionality is built on
#
# Currently this library has no dependancies other than -pthread.
# This build script outputs a statically linkable library and a debug test
# program; however this can easily be updated to produce a .so
# 

cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_BUILD_TYPE Debug)

# Set our source file scope for the library
set(LCADENGINE_SRC 
    base/logicGraph.c
    base/genericlogic.c
      
    sim/dispatcher.c
	sim/logicSolver.c

    graphLoader.c
    
    
    utils/fastlist.c
    utils/hashmap.c
    utils/lcadLogger.c
)

# Define our library in cmake
add_library(lcadengine ${LCADENGINE_SRC})

# Include the subdirectories to search for headers
target_include_directories(lcadengine PUBLIC "include")
target_include_directories(lcadengine PRIVATE "include-private")
target_include_directories(lcadengine PRIVATE ".")

# Link engine to other stuff it needs
target_link_libraries(lcadengine pthread)

# Add Lib to the name of the library
set_target_properties(lcadengine PROPERTIES PREFIX "lib")

# Debug test mainfile
add_executable(debug tests/main.c)
target_link_libraries(debug lcadengine)

# Debug test mainfile
add_executable(tests tests/tests.c)
target_link_libraries(tests lcadengine)
