cmake_minimum_required(VERSION 3.24)

project(aoc-2022
    VERSION 0.13
    DESCRIPTION "Advent of Code 2022 using C/C++"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD_REQUIRED on)

add_subdirectory(./utils)
add_subdirectory(./day1)
add_subdirectory(./day2)
add_subdirectory(./day3)
add_subdirectory(./day4)
add_subdirectory(./day5)
add_subdirectory(./day6)
add_subdirectory(./day7)
add_subdirectory(./day8)
add_subdirectory(./day9)
add_subdirectory(./day10)
add_subdirectory(./day11)
add_subdirectory(./day12)
add_subdirectory(./day13)
