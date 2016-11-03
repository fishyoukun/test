cmake_minimum_required(VERSION 3.5)
project(cordic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        cordic.cpp)

add_executable(cordic ${SOURCE_FILES})