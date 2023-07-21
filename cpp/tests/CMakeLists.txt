project(dsa-tests)

add_subdirectory(lib/Catch2)

file(GLOB_RECURSE test-srcs *.test.cpp)

add_executable(dsa-tests ${test-srcs} main.cpp)
target_link_libraries(dsa-tests PRIVATE dsa Catch2::Catch2)
target_include_directories(dsa-tests PRIVATE
        ../../cpp
        lib/Catch2/src)