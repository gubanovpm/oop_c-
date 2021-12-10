cmake_minimum_required(VERSION 2.6)
project(slider)

set (SOURCES main.cpp slider.cpp)
set (HEADERS slider.hpp)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -lsfml-system -lsfml-window -lsfml-graphics")

add_executable(slider ${SOURCES})