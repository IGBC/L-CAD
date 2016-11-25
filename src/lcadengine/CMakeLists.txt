cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")
set(CMAKE_BUILD_TYPE Debug)

# Set our source file scope for the library
set(LCADENGINE_SRC 
    logicGraph.c
    dispatcher.c
    graphLoader.c
    logicSolver.c
    genericlogic.c
    
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
add_executable(testmain src/main.c)
target_link_libraries(testmain lcadengine)

# Add tests subdirectory
# add_subdirectory(tests)
