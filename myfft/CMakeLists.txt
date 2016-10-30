cmake_minimum_required(VERSION 3.5)
project(myfft C)

set(CMAKE_C_FLAGS "${CMAKE__FLAGS}")
#set extern libraries
SET(LIBRARIES
        libm.so
        )

set(SOURCE_FILES
    myfft.c
    )

include_directories(.)

add_executable(myfft ${SOURCE_FILES})
#add link library
TARGET_LINK_LIBRARIES(${LIBRARIES})