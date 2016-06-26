cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)

project(l-cad)
add_subdirectory(lcadengine)

set(UI_SOURCE lcadui/src/main.cpp)
add_executable(lcad ${UI_SOURCE})
target_include_directories(lcad PRIVATE "lcadui/include-private")

target_link_libraries(lcad lcadengine
					SDL2 GL GLU GLEW)

