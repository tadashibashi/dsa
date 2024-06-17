
include(FetchContent)

if (NOT EXISTS Catch2::Catch2)
    FetchContent_Declare(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        4e8d92bf02f7d1c8006a0e7a5ecabd8e62d98502
    )
    FetchContent_MakeAvailable(Catch2)
endif()

add_executable(dsa_tests hash_map.test.cpp
    test_main.cpp
    dsa_tests.h
    vector.test.cpp)
target_link_libraries(dsa_tests PRIVATE Catch2::Catch2 dsa)
