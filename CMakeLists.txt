cmake_minimum_required(VERSION 2.8.4)
project(raytracing)
project(raygtest)

set(GTEST /Users/mats/Documents/Code/gtest-1.7.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES shape/sphere.cpp imagewriter.cpp camera.cpp pointlight.cpp color.cpp shape/plane.cpp lodepng.cpp)
add_executable(raytracing main.cpp ${SOURCE_FILES})
add_executable(raygtest gtest.cpp ${SOURCE_FILES})

target_include_directories(raygtest PRIVATE ${GTEST}/include/)
target_link_libraries(raygtest ${GTEST}/mybuild/libgtest.a)