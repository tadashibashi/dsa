cmake_minimum_required(VERSION 3.26)
project(dsa CXX)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE dsa-srcs ${CMAKE_SOURCE_DIR}/dsa/*.cpp ${CMAKE_SOURCE_DIR}/dsa/*.inl)
add_library(dsa ${dsa-srcs})
set_target_properties(dsa PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
