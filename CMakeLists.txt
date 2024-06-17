cmake_minimum_required(VERSION 3.23)
project(dsa)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(DSA_IS_ROOT TRUE)
else()
    set(DSA_IS_ROOT FALSE)
endif()

option(DSA_BUILD_TESTS "Include unit test targets" ${DSA_IS_ROOT})

add_subdirectory(dsa)

if (DSA_BUILD_TESTS)
    add_subdirectory(tests)
endif()
