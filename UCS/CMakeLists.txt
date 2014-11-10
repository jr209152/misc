cmake_minimum_required(VERSION 2.6)

project(ucs_test)

SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_CXX_FLAGS "-Wall -O3")

SET(ALL_SRC )

SET(ALL_INC src/)

INCLUDE_DIRECTORIES(${ALL_INC})

#add_library(UCS SHARED ${ALL_SRC})

add_executable(ucs_test src/main.cpp ${ALL_SRC})
