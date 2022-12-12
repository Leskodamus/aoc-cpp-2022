configure_file(input input COPYONLY)
add_executable(day12_part1 part1.cpp)
add_executable(day12_part2 part2.cpp)

include_directories("${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/utils")

target_link_libraries(day12_part1 PUBLIC aoc2022_utils)
target_link_libraries(day12_part2 PUBLIC aoc2022_utils)
