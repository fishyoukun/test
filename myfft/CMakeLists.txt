cmake_minimum_required(VERSION 3.5)
project(myfft)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    myfft.cpp
    myfft.h)

add_executable(myfft ${SOURCE_FILES})