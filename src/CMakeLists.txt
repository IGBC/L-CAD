cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c11")
set(CMAKE_BUILD_TYPE Debug)

project(l-cad)
# Build modules
add_subdirectory(lcadengine)

