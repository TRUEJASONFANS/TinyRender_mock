cmake_minimum_required(VERSION 3.21)
project(tinyrender_mock)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(tinyrender)

add_executable(tinyrender_mock main.cpp tinyrender/tgaimage.cpp model.cpp)

target_link_directories(tinyrender_mock PUBLIC ${PROJECT_SOURCE_DIR}/tinyrender)
target_link_libraries(tinyrender_mock PUBLIC tiny_render)