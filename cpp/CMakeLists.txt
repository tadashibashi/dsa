cmake_minimum_required(VERSION 3.26)
project(dsa)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE dsa-srcs dsa/*.cpp)
add_library(dsa ${dsa-srcs})

add_subdirectory(cpp/tests)