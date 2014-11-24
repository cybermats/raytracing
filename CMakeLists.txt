cmake_minimum_required(VERSION 2.8.4)
project(raytracing)
project(raygtest)

set(GTEST /Users/mats/Documents/Code/gtest-1.7.0)

set(CMAKE_ERROR_FLAGS "-Wno-c++98-compat -Wno-float-equal -Wno-sign-conversion -Wno-old-style-cast -Wno-shorten-64-to-32 -Wno-padded -Wno-global-constructors")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror")
# -Weverything ${CMAKE_ERROR_FLAGS}

set(SOURCE_FILES
    shape/sphere.cpp
    shape/plane.cpp
    shader/lambertshader.cpp
    shader/mirrorshader.cpp
    shader/phongshader.cpp
    shader/blinnshader.cpp
    shader/filematerial.cpp
    imagewriter.cpp
    imagereader.cpp
    camera.cpp
    pointlight.cpp
    color.cpp
    supersampler.cpp
    scene.cpp
    interfacehelper.cpp
    lodepng.cpp
)
add_executable(raytracing main.cpp ${SOURCE_FILES})
#add_executable(raygtest gtest.cpp ${SOURCE_FILES})

#target_include_directories(raygtest PRIVATE ${GTEST}/include/)
#target_link_libraries(raygtest ${GTEST}/mybuild/libgtest.a)