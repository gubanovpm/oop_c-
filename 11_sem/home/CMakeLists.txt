cmake_minimum_required(VERSION 3.10)
project (ARKANOID)

set (SOURCES 
             "./sources/main.cpp"
             "./sources/common.cpp"
             "./sources/ball.cpp"
             "./sources/brick.cpp"
             "./sources/paddle.cpp"
             "./sources/bonus.cpp"
             "./sources/brick_grid.cpp"
             "./sources/arkanoid.cpp"
    )

set (HEADERS 
             "./include/common.hpp"
             "./include/ball.hpp"
             "./include/brick.hpp"
             "./include/paddle.hpp"
             "./include/bonus.hpp"
             "./include/brick_grid.hpp"
             "./include/arkanoid.hpp"
    )

include_directories(./include)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra --std=c++2a -lsfml-system -lsfml-window -lsfml-graphics")

add_executable(ARKANOID ${SOURCES})