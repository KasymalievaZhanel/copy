cmake_minimum_required(VERSION 3.16)
project(contest1_1 C)

set(CMAKE_C_FLAGS "-std=gnu11 -fPIC")
set(CMAKE_CXX_FLAGS "-std=gnu14")

find_package(PythonLibs 3.6 REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

set(SOURCES
        main.c
        )

add_library(matrix SHARED ${SOURCES})