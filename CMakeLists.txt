cmake_minimum_required(VERSION 3.21)
project(tinyrender_mock)

set(CMAKE_CXX_STANDARD 20)

add_executable(tinyrender_mock main.cpp tgaimage.cpp model.cpp myopengl.cpp geometry.cpp)
