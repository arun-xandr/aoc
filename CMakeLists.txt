cmake_minimum_required(VERSION 3.12)
project(aoc)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

#[[
add_executable(aoc day1/part1.cpp day1/part2.cpp day2/part1.cpp day2/part2.cpp day3/part1.cpp day3/part2.cpp day4/part1.cpp include/date/date.h day4/part2.cpp day5/part1.cpp day5/part2.cpp day6/part1.cpp)]]


add_executable(aoc day6/part1.cpp)