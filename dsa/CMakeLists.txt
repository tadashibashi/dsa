
add_library(dsa INTERFACE hash_map.h
    vector.h)
target_include_directories(dsa INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../)
