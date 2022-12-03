cmake_minimum_required(VERSION 3.24)

project(aoc-2022
    VERSION 0.2
    DESCRIPTION "Advent of Code 2022 using C/C++"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_subdirectory(./day1)
add_subdirectory(./day2)
