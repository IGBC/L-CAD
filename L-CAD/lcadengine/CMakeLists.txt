cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")
set(CMAKE_BUILD_TYPE Debug)

# Set our source file scope for the library
set(LCADENGINE_SRC 
    src/logicGraph.c
    src/dispatcher.c
    src/graphLoader.c
    
    src/utils/fastlist.c
    src/utils/hashmap.c
    src/utils/thpool.c
    src/utils/lcadLogger.c
)

# Define our library in cmake
add_library(lcadengine ${LCADENGINE_SRC})

# Dynamically linked libraries
target_link_libraries(lcadengine)

# Include the subdirectories to search for headers
target_include_directories(lcadengine PUBLIC "include")
target_include_directories(lcadengine PRIVATE "include-private")
target_include_directories(lcadengine PRIVATE "src")

target_link_libraries(lcadengine pthread)

# since the name starts with 'lib' dont add it again
set_target_properties(lcadengine PROPERTIES PREFIX "lib")

add_executable(testmain src/main.c)
target_link_libraries(testmain lcadengine)

# Add tests subdirectory
# add_subdirectory(tests)
