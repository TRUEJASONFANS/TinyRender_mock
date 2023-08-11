cmake_minimum_required(VERSION 3.21)
project(tinyrender_mock)

set(CMAKE_CXX_STANDARD 17)

add_executable(tinyrender_mock main.cpp tgaimage.cpp model.cpp myopengl.cpp geometry.cpp)
add_custom_command(TARGET tinyrender_mock PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/obj/ $<TARGET_FILE_DIR:tinyrender_mock>)