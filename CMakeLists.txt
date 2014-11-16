cmake_minimum_required(VERSION 2.8.4)
project(raytracing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp sphere.cpp)

add_executable(raytracing ${SOURCE_FILES})
